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

#define kTarget 10 //目标分数 10 或 15

#define kTimer 1*60*1000  //单位是毫秒

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
//    SimpleAudioEngine::getInstance()->playBackgroundMusic("mushroom.mp3");
    
    return true;
}

Action* HelloWorld::getDelayTintToAction(int tag){
    
    auto delay = DelayTime::create(0.3);
    auto tintTo = TintTo::create(0.5, 100, 100, 100);
    auto action = getCrashAction(tag, 200, 0.5);
    auto spawn = Spawn::create(tintTo, action, NULL);
    auto seq = Sequence::create(delay, spawn, NULL);
    return seq;
    
}

Action* HelloWorld::getDelayFadeOutAction(){
    
    auto delay = DelayTime::create(0.3);
    auto fadeOut = FadeOut::create(0.5);
    auto seq = Sequence::create(delay, fadeOut, NULL);
    return seq;
    
}

void HelloWorld::updateNumber(float dt){
    numberSpriteTop->setSpriteFrame(String::createWithFormat("%d_120_highlighted.png", top)->getCString());
    numberSpriteLeft->setSpriteFrame(String::createWithFormat("%d_120_highlighted.png", left)->getCString());
    numberSpriteRight->setSpriteFrame(String::createWithFormat("%d_120_highlighted.png", right)->getCString());
    numberSpriteBottom->setSpriteFrame(String::createWithFormat("%d_120_highlighted.png", bottom)->getCString());
}

void HelloWorld::setMushroomNumber(){
    
    //这里需要一个算法生成4个数字, 其中三个之和或四个之和为10或15
    int first = (arc4random() % 9) + 1;
    int second = (arc4random() % 9) + 1;
    int third = (arc4random() % 9) + 1;
    int fourth = (arc4random() % 9) + 1;
//    int sum = first + second + third + fourth;
    
    top = first;
    left = second;
    right = third;
    bottom = fourth;
//    top = 2;
//    left = 3;
//    right = 5;
//    bottom = 8;
    
    //如何延迟执行??
    schedule(schedule_selector(HelloWorld::updateNumber), 0, 1, 1.f);
    
        
    numberSpriteTop->runAction(getDelayTintToAction(kMushroomTop));
    numberSpriteLeft->runAction(getDelayTintToAction(kMushroomLeft));
    numberSpriteRight->runAction(getDelayTintToAction(kMushroomRight));
    numberSpriteBottom->runAction(getDelayTintToAction(kMushroomBottom));
    
    mushroomTop->runAction(getDelayTintToAction(kMushroomTop));
    mushroomLeft->runAction(getDelayTintToAction(kMushroomLeft));
    mushroomRight->runAction(getDelayTintToAction(kMushroomRight));
    mushroomBottom->runAction(getDelayTintToAction(kMushroomBottom));
    
    maskTop->runAction(getDelayFadeOutAction());
    maskLeft->runAction(getDelayFadeOutAction());
    maskRight->runAction(getDelayFadeOutAction());
    maskBottom->runAction(getDelayFadeOutAction());
    
    bMushroomBottomHighlighted = false;
    bMushroomTopHighlighted = false;
    bMushroomLeftHighlighted = false;
    bMushroomRightHighlighted = false;
    
    //label归0
    tipLabel->setString(String::createWithFormat("0")->getCString());
    
    //开锁, 继续允许操作
//    bAccelerationEnabled = true;
    schedule(schedule_selector(HelloWorld::setEnableAcceleration), 0, 1, 0.5);
    
}

void HelloWorld::setEnableAcceleration(float dt){
    bAccelerationEnabled = true;
}

void HelloWorld::setDisableAcceleration(float dt){
    bAccelerationEnabled = false;
}

void HelloWorld::updateTime(float dt){
    //这里要设置label的文本, 首先累加dt, 用总时间1分钟减去累加dt, 就是剩下的时间, 转换成 分, 秒, 毫秒
    time += dt;
    //1分钟 = 60 秒 =  60 * 1000 毫秒
    float remainer = kTimer - time * 1000;
    
    if (remainer >= 0) {
        float minute = 0;
        float second = remainer/1000;
        float ms = (int)remainer%100;
        
        //    char string[10] = {0};
        //    sprintf(string, "%2.2f", time);
        timeLabel->setString(String::createWithFormat("%02.f'%02.f''%02.f", minute, second, ms)->getCString());
    } else{
        
        timeLabel->setString(String::createWithFormat("%02d'%02d''%02d", 0, 0, 0)->getCString());
        unschedule(schedule_selector(HelloWorld::updateTime));
        
        
    }
    
}

void HelloWorld::addMushroom(){
    
    Vec2 point = Vec2(visibleSize.width/2, visibleSize.height/2); //屏幕中心点
    
//    addMushroomLogic("blue_190_highlighted.png", 1, point.x, point.y + visibleSize.width/3, mushroomTop);
//    addMushroomLogic("yellow_190_highlighted.png", 4, point.x - visibleSize.width/3, point.y, mushroomLeft);
//    addMushroomLogic("red_190_highlighted.png", 5, point.x + visibleSize.width/3, point.y, mushroomRight);
//    addMushroomLogic("green_190_highlighted.png", 8, point.x, point.y - visibleSize.width/3, mushroomBottom);
    frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("number.plist");
    frameCache->addSpriteFramesWithFile("basic.plist");
    
    //添加分数label
    //添加计时器label
    //添加总计label
    auto tipSprite = Sprite::createWithSpriteFrameName("tip_label.png");
    tipSprite->setPosition(visibleSize.width - tipSprite->getContentSize().width/2, visibleSize.height - 100);
    addChild(tipSprite);
    tipLabel = Label::createWithSystemFont("0", "Schwarzwald Regular", 80,
                                            Size(100,100), TextHAlignment::CENTER, TextVAlignment::CENTER);
    tipLabel->setPosition(tipSprite->getContentSize().width/2 - 20, tipSprite->getContentSize().height/2 - 10);
    tipLabel->setColor(Color3B(0, 0, 0));
    tipSprite->addChild(tipLabel);
    
    
    auto timeSprite = Sprite::createWithSpriteFrameName("time_label.png");
    timeSprite->setPosition(visibleSize.width - timeSprite->getContentSize().width/2, 50);
    addChild(timeSprite);
    
    timeLabel = Label::createWithSystemFont("01'00''00", "Schwarzwald Regular", 40, Size(320,30), TextHAlignment::CENTER, TextVAlignment::CENTER);
    timeLabel->setPosition(timeSprite->getContentSize().width/2 + 20, timeSprite->getContentSize().height/2 + 5);
    timeLabel->setColor(Color3B(0, 0, 0));
    timeSprite->addChild(timeLabel);
    
//    schedule(schedule_selector(HelloWorld::updateTime));
    
    auto roundSprite = Sprite::createWithSpriteFrameName("round_label.png");
    roundSprite->setPosition(visibleSize.width - roundSprite->getContentSize().width/2, 150);
    addChild(roundSprite);
    
    roundLabel = Label::createWithSystemFont("0", "Schwarzwald Regular", 40, Size(30, 30), TextHAlignment::CENTER, TextVAlignment::CENTER);
    roundLabel->setPosition(roundSprite->getContentSize().width/2, roundSprite->getContentSize().height/2);
    roundLabel->setTextColor(Color4B(229, 56, 101, 0));
    roundSprite->addChild(roundLabel);
    
    //添加top蘑菇
    mushroomTop = Sprite::createWithSpriteFrameName("top_190_highlighted.png");
    mushroomTop->setPosition(point.x, point.y + visibleSize.width/3);
    mushroomTop->setColor(NormalColor);
    addChild(mushroomTop);
    
    numberSpriteTop = Sprite::create();
    numberSpriteTop->setPosition(kMushroomWidth/2, kMushroomHeight/2);
    numberSpriteTop->setColor(NormalColor);
    mushroomTop->addChild(numberSpriteTop, 0, kNumber);
    
    maskTop = Sprite::createWithSpriteFrameName("mask.png");
    maskTop->setPosition(kMushroomWidth/2, kMushroomHeight/2);
    maskTop->setOpacity(0);
    mushroomTop->addChild(maskTop, 0, kMask);
    
    //添加left蘑菇
    mushroomLeft = Sprite::createWithSpriteFrameName("left_190_highlighted.png");
    mushroomLeft->setPosition(point.x - visibleSize.width/3, point.y);
    mushroomLeft->setColor(NormalColor);
    addChild(mushroomLeft);
    
    numberSpriteLeft = Sprite::create();
    numberSpriteLeft->setPosition(kMushroomWidth/2, kMushroomHeight/2);
    numberSpriteLeft->setColor(NormalColor);
    mushroomLeft->addChild(numberSpriteLeft, 0, kNumber);
    
    maskLeft = Sprite::createWithSpriteFrameName("mask.png");
    maskLeft->setPosition(kMushroomWidth/2, kMushroomHeight/2);
    maskLeft->setOpacity(0);
    mushroomLeft->addChild(maskLeft, 0, kMask);
    
    //添加right蘑菇
    mushroomRight = Sprite::createWithSpriteFrameName("right_190_highlighted.png");
    mushroomRight->setPosition(point.x + visibleSize.width/3, point.y);
    mushroomRight->setColor(NormalColor);
    addChild(mushroomRight);
    
    numberSpriteRight = Sprite::create();
    numberSpriteRight->setPosition(kMushroomWidth/2, kMushroomHeight/2);
    numberSpriteRight->setColor(NormalColor);
    mushroomRight->addChild(numberSpriteRight, 0, kNumber);
    
    maskRight = Sprite::createWithSpriteFrameName("mask.png");
    maskRight->setPosition(kMushroomWidth/2, kMushroomHeight/2);
    maskRight->setOpacity(0);
    mushroomRight->addChild(maskRight, 0, kMask);
    
    //添加bottom蘑菇
    mushroomBottom = Sprite::createWithSpriteFrameName("bottom_190_highlighted.png");
    mushroomBottom->setPosition(point.x, point.y - visibleSize.width/3);
    mushroomBottom->setColor(NormalColor);
    addChild(mushroomBottom);
    
    numberSpriteBottom = Sprite::create();
    numberSpriteBottom->setPosition(kMushroomWidth/2, kMushroomHeight/2);
    numberSpriteBottom->setColor(NormalColor);
    mushroomBottom->addChild(numberSpriteBottom, 0, kNumber);
    
    maskBottom = Sprite::createWithSpriteFrameName("mask.png");
    maskBottom->setPosition(kMushroomWidth/2, kMushroomHeight/2);
    maskBottom->setOpacity(0);
    mushroomBottom->addChild(maskBottom, 0, kMask);
    
    
    setMushroomNumber(); //给蘑菇设置数字
    
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
        mushroom->runAction(TintTo::create(0.5, 255, 255, 255));
        number->runAction(TintTo::create(0.5, 255, 255, 255));
        
        auto scale = ScaleBy::create(0.15, 2);
        auto scaleBack = scale->reverse();
        auto seq = Sequence::create(scale, scaleBack, NULL);
        auto spawn = Spawn::create(seq, FadeIn::create(0.3), NULL);
        mask->runAction(spawn);
        
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
        mushroom->runAction(TintTo::create(0.5, 100, 100, 100));
        mask->runAction(FadeOut::create(0.3));
        number->runAction(TintTo::create(0.5, 100, 100, 100));
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
    
    person = Sprite::createWithSpriteFrameName("person.png");
    person->setPosition(visibleSize.width/2, visibleSize.height/2);
    person->setScale(0.7, 0.7);
    addChild(person);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [=](Touch* touch, Event* event){
        this->setMushroomNumber();
        person->runAction(RotateBy::create(0.2, 360));
        return true;
    };
    touchListener->onTouchEnded = [=](Touch* touch, Event* event){
        //这里可以做一些复原操作
        person->setSpriteFrame("person.png");
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, person);

    Device::setAccelerometerEnabled(true);
    Device::setAccelerometerInterval(0.1);
    
    auto listener = EventListenerAcceleration::create([=](Acceleration *acc, Event *event){
        
        //手机水平放置 (0, 0, -100)
        //手机背面竖直放置 (0, 100, 0)
        //手机正面竖直放置 (0, -100, 0)
        //手机左侧面放置 (-100, 0, 0)
        //手机右侧面放置 (100, 0, 0)
        if (bAccelerationEnabled) {
            int x = int(acc->x * 100);
            int y = int(acc->y * 100);
            
            if (x < -kSwitch) {
                log("left");
                this->crashMushroom(mushroomLeft, kMushroomLeft);
                //这里添加一个检测是否满足获胜条件的逻辑, 但需要延迟执行
                this->checkWin();
                
            } else if (x > kSwitch){
                log("right");
                this->crashMushroom(mushroomRight, kMushroomRight);
                this->checkWin();
                
            } else if (y < -kSwitch){
                log("bottom");
                this->crashMushroom(mushroomBottom, kMushroomBottom);
                this->checkWin();
                
            } else if (y > kSwitch) {
                log("top");
                this->crashMushroom(mushroomTop, kMushroomTop);
                this->checkWin();
                
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
        }
        
        
    });
    
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
}


int HelloWorld::getNumberSum(){
    int sum = 0;
    
    if (bMushroomTopHighlighted) {
        sum += top;
        tipLabel->setString(String::createWithFormat("%d", sum)->getCString());
    }
    
    if (bMushroomLeftHighlighted) {
        sum += left;
        tipLabel->setString(String::createWithFormat("%d", sum)->getCString());
    }
    
    if (bMushroomRightHighlighted) {
        sum += right;
        tipLabel->setString(String::createWithFormat("%d", sum)->getCString());
    }
    
    if (bMushroomBottomHighlighted) {
        sum += bottom;
        tipLabel->setString(String::createWithFormat("%d", sum)->getCString());
    }
    
    if (!bMushroomTopHighlighted && !bMushroomLeftHighlighted && !bMushroomRightHighlighted && !bMushroomBottomHighlighted) {
        tipLabel->setString(String::createWithFormat("0")->getCString());
    }
    
    return sum;
    
}

bool HelloWorld::checkWin(){
    if (getNumberSum() == kTarget) {
        
        roundNumber++; //获胜的局数加1
        roundLabel->setString(String::createWithFormat("%d", roundNumber)->getCString());
        bAccelerationEnabled = false; //获胜的时候加一把锁, 防止再操作
        //这里要添加一个person胜利动画, 播放粒子效果, 进入一下局
        auto emitter = ParticleSystemQuad::create("win.plist");
        emitter->setPosition(visibleSize.width/2, visibleSize.height/2);
        emitter->setAutoRemoveOnFinish(true);
        addChild(emitter, 10);
        
//        int height = (arc4random() % 100) + 1;
//        int count = (arc4random() % 3) + 1;
//        int degree = (arc4random() % 180) + 181;
        auto spawn = Spawn::create(EaseBackInOut::create(MoveBy::create(0.5, Vec2(0, visibleSize.height/2))), RotateBy::create(0.5, 360), NULL);
        auto spawnBack = spawn->reverse();
        person->runAction(Sequence::create(DelayTime::create(0.3), spawn, spawnBack, NULL));
        
        setMushroomNumber();
        
        return true;
    }else{
        return false;
    }
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
