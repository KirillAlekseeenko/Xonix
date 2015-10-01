//
//  CollisionDots.h
//  TuturialProject
//
//  Created by Кирилл Алексеенко on 24.08.15.
//
//

#ifndef __TuturialProject__CollisionDots__
#define __TuturialProject__CollisionDots__

#include <stdio.h>
#include "cocos2d.h"
#include <algorithm>
using namespace std;
using namespace cocos2d;

#endif /* defined(__TuturialProject__CollisionDots__) */

class CollisionDots
{
    static stack<Vec2> currentCollision;
    static stack<Vec2> dotsPoly;
    static void create();

public:
    static int beginTag;
    static int endTag;
    static stack<Vec2>& getCurrentCollision();
    static stack<Vec2>& getDotsPoly();
};