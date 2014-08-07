#include "HelloWorldScene.h"
#include "VisibleRect.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

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
#define kNumber 6

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
    
    //播放背景音乐
//    SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3");
    
    return true;
}

void HelloWorld::addMushroom(){
    
    Vec2 point = Vec2(visibleSize.width/2, visibleSize.height/2); //屏幕中心点
    
//    addMushroomLogic("blue_190_highlighted.png", 1, point.x, point.y + visibleSize.width/3, mushroomTop);
//    addMushroomLogic("yellow_190_highlighted.png", 4, point.x - visibleSize.width/3, point.y, mushroomLeft);
//    addMushroomLogic("red_190_highlighted.png", 5, point.x + visibleSize.width/3, point.y, mushroomRight);
//    addMushroomLogic("green_190_highlighted.png", 8, point.x, point.y - visibleSize.width/3, mushroomBottom);
    
    //添加top蘑菇
    mushroomTop = Sprite::create("top_190_highlighted.png");
    mushroomTop->setPosition(point.x, point.y + visibleSize.width/3);
    mushroomTop->setColor(NormalColor);
    addChild(mushroomTop);
    
    auto numberSprite = Sprite::create(String::createWithFormat("number/%d_120_highlighted.png", 1)->getCString());
    numberSprite->setPosition(kMushroomWidth/2, kMushroomHeight/2);
    numberSprite->setColor(NormalColor);
    mushroomTop->addChild(numberSprite, 0, kNumber);
    
    auto mask = Sprite::create("mask.png");
    mask->setPosition(kMushroomWidth/2, kMushroomHeight/2);
//    mask->setVisible(false);
    mask->setOpacity(0);
    mushroomTop->addChild(mask, 0, kMask);
    
    //添加left蘑菇
    mushroomLeft = Sprite::create("left_190_highlighted.png");
    mushroomLeft->setPosition(point.x - visibleSize.width/3, point.y);
    mushroomLeft->setColor(NormalColor);
    addChild(mushroomLeft);
    
    auto numberSprite1 = Sprite::create(String::createWithFormat("number/%d_120_highlighted.png", 4)->getCString());
    numberSprite1->setPosition(kMushroomWidth/2, kMushroomHeight/2);
    numberSprite1->setColor(NormalColor);
    mushroomLeft->addChild(numberSprite1, 0, kNumber);
    
    auto mask1 = Sprite::create("mask.png");
    mask1->setPosition(kMushroomWidth/2, kMushroomHeight/2);
//    mask1->setVisible(false);
    mask1->setOpacity(0);
    mushroomLeft->addChild(mask1, 0, kMask);
    
    //添加right蘑菇
    mushroomRight = Sprite::create("right_190_highlighted.png");
    mushroomRight->setPosition(point.x + visibleSize.width/3, point.y);
    mushroomRight->setColor(NormalColor);
    addChild(mushroomRight);
    
    auto numberSprite2 = Sprite::create(String::createWithFormat("number/%d_120_highlighted.png", 5)->getCString());
    numberSprite2->setPosition(kMushroomWidth/2, kMushroomHeight/2);
    numberSprite2->setColor(NormalColor);
    mushroomRight->addChild(numberSprite2, 0, kNumber);
    
    auto mask2 = Sprite::create("mask.png");
    mask2->setPosition(kMushroomWidth/2, kMushroomHeight/2);
//    mask2->setVisible(false);
    mask2->setOpacity(0);
    mushroomRight->addChild(mask2, 0, kMask);
    
    //添加bottom蘑菇
    mushroomBottom = Sprite::create("bottom_190_highlighted.png");
    mushroomBottom->setPosition(point.x, point.y - visibleSize.width/3);
    mushroomBottom->setColor(NormalColor);
    addChild(mushroomBottom);
    
    auto numberSprite3 = Sprite::create(String::createWithFormat("number/%d_120_highlighted.png", 8)->getCString());
    numberSprite3->setPosition(kMushroomWidth/2, kMushroomHeight/2);
    numberSprite3->setColor(NormalColor);
    mushroomBottom->addChild(numberSprite3, 0, kNumber);
    
    auto mask3 = Sprite::create("mask.png");
    mask3->setPosition(kMushroomWidth/2, kMushroomHeight/2);
//    mask3->setVisible(false);
    mask3->setOpacity(0);
    mushroomBottom->addChild(mask3, 0, kMask);
    
    
}

void HelloWorld::addMushroomLogic(const std::string& filename, int number, float x, float y, Sprite* mushroom){
    
//    mushroom = Sprite::create(filename);
//    mushroom->setPosition(x, y);
//    mushroom->setColor(NormalColor);
//    addChild(mushroom);
//    
//    auto numberSprite = Sprite::create(String::createWithFormat("number/%d_120_highlighted.png", number)->getCString());
//    numberSprite->setPosition(kMushroomWidth/2, kMushroomHeight/2);
//    numberSprite->setColor(NormalColor);
//    mushroom->addChild(numberSprite);
//    
//    auto mask = Sprite::create("mask.png");
//    mask->setPosition(kMushroomWidth/2, kMushroomHeight/2);
//    mask->setVisible(false);
//    mushroom->addChild(mask, 0, kMask);
    
}

void HelloWorld::crashMushroomLogic(Sprite* mushroom, int tag, bool highlighted){
    
    person->runAction(this->getCrashAction(tag, 40, 0.2));  //人的动画始终要执行, 蘑菇的动画加入延迟
    mushroom->runAction(this->getShakeAction(tag, 100, 0.3));
    
    if (!highlighted) {
        auto mask = mushroom->getChildByTag(kMask);
        auto number = mushroom->getChildByTag(kNumber);
        mushroom->runAction(TintTo::create(1.0, 255, 255, 255));
        mask->runAction(FadeIn::create(0.3));
        number->runAction(TintTo::create(1.0, 255, 255, 255));
        
        switch (tag) {
            case kMushroomTop:
            {
                bMushroomTopHighlighted = true;
                auto emitter = ParticleSystemQuad::create("crash_top.plist");
                emitter->setPosition(mushroom->getPosition().x, mushroom->getPosition().y - mushroom->getContentSize().height/2);
                emitter->setAutoRemoveOnFinish(true);
                addChild(emitter, 10);
                break;
            }
            case kMushroomLeft:
            {
                bMushroomLeftHighlighted = true;
                auto emitter = ParticleSystemQuad::create("crash_left.plist");
                emitter->setPosition(mushroom->getPosition().x + mushroom->getContentSize().width/2, mushroom->getPosition().y);
                emitter->setAutoRemoveOnFinish(true);
                addChild(emitter, 10);
                break;
            }
            case kMushroomRight:
            {
                bMushroomRightHighlighted = true;
                auto emitter = ParticleSystemQuad::create("crash_right.plist");
                emitter->setPosition(mushroom->getPosition().x - mushroom->getContentSize().width/2, mushroom->getPosition().y);
                emitter->setAutoRemoveOnFinish(true);
                addChild(emitter, 10);
                break;
            }
            case kMushroomBottom:
            {
                bMushroomBottomHighlighted = true;
                auto emitter = ParticleSystemQuad::create("crash_bottom.plist");
                emitter->setPosition(mushroom->getPosition().x, mushroom->getPosition().y + mushroom->getContentSize().height/2);
                emitter->setAutoRemoveOnFinish(true);
                addChild(emitter, 10);
                break;
            }
            default:
                break;
        }
//        mushroom->highlighted = true;
        //这里要执行一段由中心点放大至整个的动画
        
    }else{
        
        auto mask = mushroom->getChildByTag(kMask);
        auto number = mushroom->getChildByTag(kNumber);
        mushroom->runAction(TintTo::create(1.0, 100, 100, 100));
        mask->runAction(FadeOut::create(0.3));
        number->runAction(TintTo::create(1.0, 100, 100, 100));
        switch (tag) {
            case kMushroomTop:
                bMushroomTopHighlighted = false;
                break;
            case kMushroomLeft:
                bMushroomLeftHighlighted = false;
                break;
            case kMushroomRight:
                bMushroomRightHighlighted = false;
                break;
            case kMushroomBottom:
                bMushroomBottomHighlighted = false;
                break;
            default:
                break;
        }
//        mushroom->highlighted = false;
        //如果需要的话,也可以渐进动画然后消失
        
    }
    
}

void HelloWorld::crashMushroom(Sprite* mushroom, int tag){
    
    switch (tag) {
        case kMushroomTop:
            if (!bMushroomTopCrashed) {
                crashMushroomLogic(mushroom, tag, bMushroomTopHighlighted);
                bMushroomTopCrashed = true;
            }
            break;
        case kMushroomLeft:
            if (!bMushroomLeftCrashed) {
                crashMushroomLogic(mushroom, tag, bMushroomLeftHighlighted);
                bMushroomLeftCrashed = true;
            }
            break;
        case kMushroomRight:
            if (!bMushroomRightCrashed) {
                crashMushroomLogic(mushroom, tag, bMushroomRightHighlighted);
                bMushroomRightCrashed = true;
            }
            break;
        case kMushroomBottom:
            if (!bMushroomBottomCrashed) {
                crashMushroomLogic(mushroom, tag, bMushroomBottomHighlighted);
                bMushroomBottomCrashed = true;
            }
            break;
        default:
            break;
    }
    
//    if (!mushroom->crashed) { //没有撞过
//        crashMushroomLogic(mushroom, tag, mushroom->highlighted);
//        mushroom->crashed = true;
//    }

}

Action* HelloWorld::getShakeAction(int tag, int distance, float duration){
    
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
    
    
    auto delay = DelayTime::create(0.1);
    auto move = MoveBy::create(duration, Vec2(distanceX, distanceY));
    auto move_ease_in = EaseElasticIn::create(move->clone() );
    auto move_ease_in_back = move_ease_in->reverse();
    auto seq = Sequence::create(delay, move_ease_in, move_ease_in_back, nullptr);
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
            
        } else if (x < 20 && x > -20 && y < 20 && y > -20){
            bMushroomTopCrashed = false;
            bMushroomLeftCrashed = false;
            bMushroomRightCrashed = false;
            bMushroomBottomCrashed = false;
//            mushroomTop->crashed = false;
//            mushroomLeft->crashed = false;
//            mushroomRight->crashed = false;
//            mushroomBottom->crashed = false;
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
