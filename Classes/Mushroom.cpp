//
//  Mushroom.cpp
//  demo
//
//  Created by leo.zhu on 14-8-6.
//
//

#include "Mushroom.h"
USING_NS_CC;

bool Mushroom::initWithFile(const std::string &filename){
    Sprite::initWithFile(filename);
    
    return true;
}

Mushroom* Mushroom::create(const std::string &filename){
    auto mushroom = new Mushroom();
    mushroom->initWithFile(filename);
    mushroom->autorelease();
    return mushroom;
}
