//
//  LevelScene.hpp
//  TuturialProject
//
//  Created by Кирилл Алексеенко on 13.10.15.
//
//

#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "TransactionHandler.hpp"

class LevelScene : public cocos2d::Layer
{
    int _currentLevel;
    const char* STRING_LEVEL = "CURRENT_LEVEL";
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // a selector callback
    
    // implement the "static create()" method manually
    CREATE_FUNC(LevelScene);
    
    
};

#endif

