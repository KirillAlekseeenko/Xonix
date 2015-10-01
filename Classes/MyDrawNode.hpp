//
//  MyDrawNode.hpp
//  TuturialProject
//
//  Created by Кирилл Алексеенко on 28.09.15.
//
//

#ifndef MyDrawNode_hpp
#define MyDrawNode_hpp

#include <stdio.h>
#include "cocos2d.h"


class MyDrawNode : public cocos2d::DrawNode
{
    virtual void update(float dt);
public:
    static cocos2d::DrawNode* create();
};



#endif /* MyDrawNode_hpp */
