//
//  TransactionHandler.cpp
//  TuturialProject
//
//  Created by Кирилл Алексеенко on 09.10.15.
//
//

#include "TransactionHandler.hpp"
#include "GameScene.h"


void TransactionHandler::popScene()
{
    if(!cocos2d::Director::getInstance()->isPaused())
        cocos2d::Director::getInstance()->pause();
    cocos2d::Director::getInstance()->popScene();
    cocos2d::Director::getInstance()->resume();
    
}

void TransactionHandler::reloadGameScene()
{
    if(!cocos2d::Director::getInstance()->isPaused())
        cocos2d::Director::getInstance()->pause();
    cocos2d::Director::getInstance()->popScene();
    cocos2d::Director::getInstance()->pushScene(GameScene::createScene(4));
    cocos2d::Director::getInstance()->resume();
    
}

void TransactionHandler::loadLevel(int level)
{
    if(!cocos2d::Director::getInstance()->isPaused())
        cocos2d::Director::getInstance()->pause();
    cocos2d::Director::getInstance()->popScene();
    cocos2d::Director::getInstance()->pushScene(GameScene::createScene(level));
    cocos2d::Director::getInstance()->resume();

}