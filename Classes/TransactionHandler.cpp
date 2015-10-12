//
//  TransactionHandler.cpp
//  TuturialProject
//
//  Created by Кирилл Алексеенко on 09.10.15.
//
//

#include "TransactionHandler.hpp"


void TransactionHandler::popScene()
{
    if(!cocos2d::Director::getInstance()->isPaused())
        cocos2d::Director::getInstance()->pause();
    cocos2d::Director::getInstance()->popScene();
    cocos2d::Director::getInstance()->resume();
    
}