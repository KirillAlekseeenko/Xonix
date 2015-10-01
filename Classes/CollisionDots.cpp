//
//  CollisionDots.cpp
//  TuturialProject
//
//  Created by Кирилл Алексеенко on 24.08.15.
//
//

#include "CollisionDots.h"

bool initialized = false;

stack<Vec2> CollisionDots::currentCollision;
stack<Vec2> CollisionDots::dotsPoly;
int CollisionDots::beginTag;
int CollisionDots::endTag;
void CollisionDots::create()
{
    currentCollision = stack<Vec2>();
    dotsPoly = stack<Vec2>();
}
stack<Vec2>& CollisionDots::getCurrentCollision()
{
    if(!initialized)
    {
        initialized = true;
        create();
    }
    return currentCollision;
}

stack<Vec2>& CollisionDots::getDotsPoly()
{
    if(!initialized)
    {
        initialized = true;
        create();
    }
    return dotsPoly;
}