//
//  Mushroom.cpp
//  demo
//
//  Created by leo.zhu on 14-8-6.
//
//

#include "Mushroom.h"
USING_NS_CC;

Mushroom* Mushroom::create(const std::string &filename){
    auto mushroom = (Mushroom*)Sprite::create(filename);
    return mushroom;
}
