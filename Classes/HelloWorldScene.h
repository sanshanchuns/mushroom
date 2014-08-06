#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
private:    
    Size visibleSize;
    
    Sprite* mushroomTop;
    Sprite* mushroomTopHighlighted;
    Sprite* mushroomLeft;
    Sprite* mushroomLeftHighlighted;
    Sprite* mushroomRight;
    Sprite* mushroomRightHighlighted;
    Sprite* mushroomBottom;
    Sprite* mushroomBottomHighlighted;
    Sprite* person;
    
    bool bMushroomTopCrashed;
    bool bMushroomLeftCrashed;
    bool bMushroomRightCrashed;
    bool bMushroomBottomCrashed;
    bool bPersonCrashed; //人是否已经撞过了
    
    void addMushroom();
    void addMushroomLogic(const std::string& filename, const std::string& filenameHighlighted, float x, float y);
    void addPerson(float x, float y, const std::string& filename, int tag);
    
    Action* getShakeAction(int tag, int distance, float duration);
    void crashMushroom(Sprite* mushroom, Sprite* mushroomHighlighted, int tag);
    void crashMushroomLogic(Sprite* mushroom, Sprite* mushroomHighlighted, int tag);
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
