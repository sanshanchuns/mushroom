#include "HelloWorldScene.h"
#include "VisibleRect.h"

USING_NS_CC;

#define kMushroomTop 1
#define kMushroomLeft 2
#define kMushroomRight 3
#define kMushroomBottom 4
#define kPerson 5

#define kNumberTop 1
#define kNumberLeft 2
#define kNumberRight 3
#define kNumberBottom 4

#define kMask 5   //蘑菇外面的罩层

#define kSwitch 30
#define NormalColor Color3B(100, 100, 100)
#define HightlightedColor Color3B(255, 255, 255)

#define kMushroomWidth 190
#define kMushroomHeight 190

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    addMushroom();
    addPerson();
    
    //添加背景
//    auto background = Sprite::create("background.png");
//    background->setPosition(visibleSize.width/2, visibleSize.height/2);
//    background->setScale(visibleSize.width/background->getContentSize().width, visibleSize.height/background->getContentSize().height);
//    addChild(background);
    
    return true;
}

void HelloWorld::addMushroom(){
    
    Vec2 point = Vec2(visibleSize.width/2, visibleSize.height/2); //屏幕中心点
    
    mushroomTop = addMushroomLogic("blue_190_highlighted.png", 1, point.x, point.y + visibleSize.width/3);
    mushroomLeft = addMushroomLogic("yellow_190_highlighted.png", 4, point.x - visibleSize.width/3, point.y);
    mushroomRight = addMushroomLogic("red_190_highlighted.png", 5, point.x + visibleSize.width/3, point.y);
    mushroomBottom = addMushroomLogic("green_190_highlighted.png", 8, point.x, point.y - visibleSize.width/3);
    
}

Mushroom* HelloWorld::addMushroomLogic(const std::string& filename, int number, float x, float y){
    
    auto mushroom = Mushroom::create(filename);
    mushroom->setPosition(x, y);
    mushroom->setColor(NormalColor);
    addChild(mushroom);
    
    char numberPath[28];
    sprintf(numberPath, "number/%d_120_highlighted.png", number);
    
    auto numberSprite = Sprite::create(numberPath);
    numberSprite->setPosition(kMushroomWidth/2, kMushroomHeight/2);
    numberSprite->setColor(NormalColor);
    mushroom->addChild(numberSprite);
    
    auto mask = Sprite::create("mask.png");
    mask->setPosition(kMushroomWidth/2, kMushroomHeight/2);
    mask->setVisible(false);
    mushroom->addChild(mask, 0, kMask);
    
    return mushroom;
}

void HelloWorld::crashMushroomLogic(Mushroom* mushroom, int tag, bool highlighted){
    
    person->runAction(this->getCrashAction(tag, 40, 0.3));  //人的动画始终要执行, 蘑菇的动画加入延迟
    mushroom->runAction(this->getShakeAction(tag, 100, 0.3, highlighted));
    
    if (!highlighted) {
        auto mask = mushroom->getChildByTag(kMask);
        mask->setVisible(true);
        mushroom->highlighted = true;
        //这里要执行一段由中心点放大至整个的动画
        
    }else{
        
        auto mask = mushroom->getChildByTag(kMask);
        mask->setVisible(false);
        mushroom->highlighted = false;
        //如果需要的话,也可以渐进动画然后消失
        
    }
    
}

void HelloWorld::crashMushroom(Mushroom* mushroom, int tag){
    
    if (!mushroom->crashed) { //没有撞过
        crashMushroomLogic(mushroom, tag, mushroom->highlighted);
        mushroom->crashed = true;
    }

}

Action* HelloWorld::getShakeAction(int tag, int distance, float duration, bool highlighted){
    
    float distanceX = 0;
    float distanceY = 0;
    
    switch (tag) {
        case kMushroomTop:
            distanceX = 0;
            distanceY = distance;
            break;
        case kMushroomLeft:
            distanceX = -distance;
            distanceY = 0;
            break;
        case kMushroomRight:
            distanceX = distance;
            distanceY = 0;
            break;
        case kMushroomBottom:
            distanceX = 0;
            distanceY = -distance;
            break;
        default:
            break;
    }
    
    
    auto delay = DelayTime::create(0.3);
    auto move = MoveBy::create(duration, Vec2(distanceX, distanceY));
    auto move_ease_in = EaseElasticIn::create(move->clone() );
    auto move_ease_in_back = move_ease_in->reverse();
    TintTo* tint = nullptr;
    if (highlighted) {
        tint = TintTo::create(duration, 100, 100, 100);
    }else{
        tint = TintTo::create(duration, 255, 255, 255);
    }
    auto seq = Sequence::create(delay, move_ease_in, move_ease_in_back, tint, nullptr);
    return seq;
    
}

Action* HelloWorld::getCrashAction(int tag, int distance, float duration){
    
    float distanceX = 0;
    float distanceY = 0;
    
    switch (tag) {
        case kMushroomTop:
            distanceX = 0;
            distanceY = distance;
            break;
        case kMushroomLeft:
            distanceX = -distance;
            distanceY = 0;
            break;
        case kMushroomRight:
            distanceX = distance;
            distanceY = 0;
            break;
        case kMushroomBottom:
            distanceX = 0;
            distanceY = -distance;
            break;
        default:
            break;
    }
    
    auto move = MoveBy::create(duration, Vec2(distanceX, distanceY));
    auto move_ease_in = EaseBackIn::create(move->clone() );
    auto move_ease_in_back = move_ease_in->reverse();
    auto seq = Sequence::create(move_ease_in, move_ease_in_back, nullptr);
    return seq;
    
}


void HelloWorld::addPerson(){
    
    person = Sprite::create("person.png");
    person->setPosition(visibleSize.width/2, visibleSize.height/2);
    person->setScale(0.7, 0.7);
    addChild(person);

    Device::setAccelerometerEnabled(true);
    Device::setAccelerometerInterval(0.1);
    
    auto listener = EventListenerAcceleration::create([=](Acceleration *acc, Event *event){
        
        //手机水平放置 (0, 0, -100)
        //手机背面竖直放置 (0, 100, 0)
        //手机正面竖直放置 (0, -100, 0)
        //手机左侧面放置 (-100, 0, 0)
        //手机右侧面放置 (100, 0, 0)
        int x = int(acc->x * 100);
        int y = int(acc->y * 100);
        
        if (x < -kSwitch) {
            log("left");
            this->crashMushroom(mushroomLeft, kMushroomLeft);
            
        } else if (x > kSwitch){
            log("right");
            this->crashMushroom(mushroomRight, kMushroomRight);
            
        } else if (y < -kSwitch){
            log("bottom");
            this->crashMushroom(mushroomBottom, kMushroomBottom);
            
        } else if (y > kSwitch) {
            log("top");
            this->crashMushroom(mushroomTop, kMushroomTop);
            
        } else if (x < 10 && x > -10 && y < 10 && y > -10){
            mushroomTop->crashed = false;
            mushroomLeft->crashed = false;
            mushroomRight->crashed = false;
            mushroomBottom->crashed = false;
        }
        
    });
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
}


//void HelloWorld::menuCloseCallback(Ref* pSender)
//{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//    return;
//#endif
//
//    Director::getInstance()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
//}
