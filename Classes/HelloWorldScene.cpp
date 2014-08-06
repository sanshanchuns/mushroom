#include "HelloWorldScene.h"
#include "VisibleRect.h"

USING_NS_CC;

#define kMushroomTop 1
#define kMushroomLeft 2
#define kMushroomRight 3
#define kMushroomBottom 4
#define kPerson 5
#define kSwitch 30

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
    
//    //添加道具
    Vec2 point = VisibleRect::center();
    addMushroom();
    
    addPerson(point.x, point.y, "person.png", kPerson);
    
    //添加背景
//    auto background = Sprite::create("background.png");
//    background->setPosition(visibleSize.width/2, visibleSize.height/2);
//    background->setScale(visibleSize.width/background->getContentSize().width, visibleSize.height/background->getContentSize().height);
//    addChild(background);
    
    return true;
}

void HelloWorld::addMushroom(){
    
    Vec2 point = Vec2(visibleSize.width/2, visibleSize.height/2); //屏幕中心点
    
    //添加top蘑菇
    mushroomTop = Sprite::create("blue_190.png");
    mushroomTop->setPosition(point.x, point.y + visibleSize.width/3);
    addChild(mushroomTop);
    
    mushroomTopHighlighted = Sprite::create("blue_190_highlighted.png");
    mushroomTopHighlighted->setPosition(point.x, point.y + visibleSize.width/3);
    mushroomTopHighlighted->setVisible(false);
    addChild(mushroomTopHighlighted);
    
    //添加left蘑菇
    mushroomLeft = Sprite::create("yellow_190.png");
    mushroomLeft->setPosition(point.x - visibleSize.width/3, point.y);
    addChild(mushroomLeft);
    
    mushroomLeftHighlighted = Sprite::create("yellow_190_highlighted.png");
    mushroomLeftHighlighted->setPosition(point.x - visibleSize.width/3, point.y);
    mushroomLeftHighlighted->setVisible(false);
    addChild(mushroomLeftHighlighted);
    
    //添加right蘑菇
    mushroomRight = Sprite::create("red_190.png");
    mushroomRight->setPosition(point.x + visibleSize.width/3, point.y);
    addChild(mushroomRight);
    
    mushroomRightHighlighted = Sprite::create("red_190_highlighted.png");
    mushroomRightHighlighted->setPosition(point.x + visibleSize.width/3, point.y);
    mushroomRightHighlighted->setVisible(false);
    addChild(mushroomRightHighlighted);
    
    //添加bottom蘑菇
    mushroomBottom = Sprite::create("green_190.png");
    mushroomBottom->setPosition(point.x, point.y - visibleSize.width/3);
    addChild(mushroomBottom);
    
    mushroomBottomHighlighted = Sprite::create("green_190_highlighted.png");
    mushroomBottomHighlighted->setPosition(point.x, point.y - visibleSize.width/3);
    mushroomBottomHighlighted->setVisible(false);
    addChild(mushroomBottomHighlighted);
    
//    auto listener = EventListenerTouchOneByOne::create();
//    listener->onTouchBegan = [mushroom, mushroomHighlighted, tag, this](Touch* touch, Event* event){
//        
//        auto node = event->getCurrentTarget();
//        if (node->getBoundingBox().containsPoint(touch->getLocation())) {
//            
//            if (node->isVisible()) {
//                mushroom->setVisible(false);
//                mushroomHighlighted->setVisible(true);
//                mushroomHighlighted->runAction(this->getShakeAction(tag, 100, 0.3));
//                
//            }else{
//                mushroom->setVisible(true);
//                mushroom->runAction(this->getShakeAction(tag, 100, 0.3));
//                mushroomHighlighted->setVisible(false);
//                
//            }
//
//        }
//        
//        return false;
//        
//    };
//    
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, mushroom);
    
}

void HelloWorld::addMushroomLogic(const std::string& filename, const std::string& filenameHighlighted, float x, float y){
    
    auto mushroom = Sprite::create(filename);
    mushroom->setPosition(x, y);
    addChild(mushroom);
    
    auto mushroomHighlighted = Sprite::create(filenameHighlighted);
    mushroomHighlighted->setPosition(x, y);
    mushroomHighlighted->setVisible(false);
    addChild(mushroomHighlighted);

}

void HelloWorld::crashMushroomLogic(Sprite* mushroom, Sprite* mushroomHighlighted, int tag){
    
    person->runAction(this->getShakeAction(tag, 40, 0.3));
    
    if (mushroom->isVisible()) {
        mushroom->setVisible(false);
        mushroomHighlighted->setVisible(true);
        mushroomHighlighted->runAction(this->getShakeAction(tag, 100, 0.3));
        
    }else{
        mushroom->setVisible(true);
        mushroom->runAction(this->getShakeAction(tag, 100, 0.3));
        mushroomHighlighted->setVisible(false);
    }
}

void HelloWorld::crashMushroom(Sprite* mushroom, Sprite* mushroomHighlighted, int tag){
    
    switch (tag) {
        case kMushroomTop:
            if (!bMushroomTopCrashed) { //没有撞过
                crashMushroomLogic(mushroom, mushroomHighlighted, tag);
                bMushroomTopCrashed = true;
            }
            
            break;
            
            
        case kMushroomLeft:
            if (!bMushroomLeftCrashed) { //没有撞过
                crashMushroomLogic(mushroom, mushroomHighlighted, tag);
                bMushroomLeftCrashed = true;
            }
            
            break;
            
        case kMushroomRight:
            if (!bMushroomRightCrashed) { //没有撞过
                crashMushroomLogic(mushroom, mushroomHighlighted, tag);
                bMushroomRightCrashed = true;
            }
            
            break;
            
        case kMushroomBottom:
            if (!bMushroomBottomCrashed) { //没有撞过
                crashMushroomLogic(mushroom, mushroomHighlighted, tag);
                bMushroomBottomCrashed = true;
            }
            
            break;
            
        default:
            break;
    }
    

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
    
    auto move = MoveBy::create(duration, Vec2(distanceX, distanceY));
    auto move_ease_in = EaseElasticIn::create(move->clone() );
    auto move_ease_in_back = move_ease_in->reverse();
    auto seq = Sequence::create(move_ease_in, move_ease_in_back, nullptr);
    return seq;
    
}


void HelloWorld::addPerson(float x, float y, const std::string &filename, int tag){
    
    person = Sprite::create(filename);
    person->setPosition(Vec2(x, y));
    person->setScale(0.7, 0.7);
    addChild(person);
    
    auto l = EventListenerTouchOneByOne::create();
    l->onTouchBegan = [=](Touch* touch, Event* event){
        
        person->runAction(this->getShakeAction(kMushroomLeft, 100, 0.3));
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(l, person);
    
    
    
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
            this->crashMushroom(mushroomLeft, mushroomLeftHighlighted, kMushroomLeft);
            
        } else if (x > kSwitch){
            log("right");
            this->crashMushroom(mushroomRight, mushroomRightHighlighted, kMushroomRight);
            
        } else if (y < -kSwitch){
            log("bottom");
            this->crashMushroom(mushroomBottom, mushroomBottomHighlighted, kMushroomBottom);
            
        } else if (y > kSwitch) {
            log("top");
            this->crashMushroom(mushroomTop, mushroomTopHighlighted, kMushroomTop);
        } else if (x < 10 && x > -10 && y < 10 && y > -10){
            bMushroomTopCrashed = false;
            bMushroomLeftCrashed = false;
            bMushroomRightCrashed = false;
            bMushroomBottomCrashed = false;
        }
        
    });
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
