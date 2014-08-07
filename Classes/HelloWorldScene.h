#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Mushroom.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
private:    
    Size visibleSize;
    
    Sprite* mushroomTop;
    Sprite* mushroomLeft;
    Sprite* mushroomRight;
    Sprite* mushroomBottom;
    Sprite* person;
    
    //以下bool用于标记是否撞击过
    bool bMushroomTopCrashed;
    bool bMushroomLeftCrashed;
    bool bMushroomRightCrashed;
    bool bMushroomBottomCrashed;
    bool bPersonCrashed; //人是否已经撞过了
    
    //以下bool用于标记是否高亮
    bool bMushroomTopHighlighted;
    bool bMushroomLeftHighlighted;
    bool bMushroomRightHighlighted;
    bool bMushroomBottomHighlighted;
    
    void addMushroom();
    void addMushroomLogic(const std::string& filename, int number, float x, float y, Sprite* mushroom);
    void addPerson();
    
    Action* getShakeAction(int tag, int distance, float duration);
    Action* getCrashAction(int tag, int distance, float duration);
    
    void crashMushroom(Sprite* mushroom, int tag);
    void crashMushroomLogic(Sprite* mushroom, int tag, bool highlighted);
//    void addMushroom(Vec2 point, const std::string& filename, const std::string& filenameHighlighted);
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
