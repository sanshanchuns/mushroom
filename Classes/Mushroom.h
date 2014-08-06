//
//  Mushroom.h
//  demo
//
//  Created by leo.zhu on 14-8-6.
//
//

#ifndef demo_Mushroom_h
#define demo_Mushroom_h

#include "cocos2d.h"

USING_NS_CC;

class Mushroom : public Sprite {
private:
    
public:

    bool highlighted; //是否高亮
    bool crashed; //是否已经撞击过
    
    bool initWithFile(const std::string& filename);
    static Mushroom* create(const std::string& filename);
    
};

#endif
