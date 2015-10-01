//
//  MyDrawNode.cpp
//  TuturialProject
//
//  Created by Кирилл Алексеенко on 28.09.15.
//
//

#include "MyDrawNode.hpp"


void MyDrawNode::update(float dt)
{
    this->setPositionX(1000);
}


cocos2d::DrawNode* MyDrawNode::create()
{
    auto drawnode = DrawNode::create();
    DrawNode::create();
    return drawnode;
}