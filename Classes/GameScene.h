//
//  GameScene.h
//  TuturialProject
//
//  Created by Кирилл Алексеенко on 12.06.15.
//
//

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "CollisionDots.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include <list>
#include <vector>
#include "RelativePosition.h"
#include "triangulate.h"
#include <cmath>
#include "MainPolygon.h"
#include <stack>

class GameScene : public cocos2d::Scene
{
    bool _gameBegun;
    
    DrawNode *character;
    std::vector<DrawNode*> enemies;
    
    cocos2d::RenderTexture *canvas;
    
    std::vector<Vec2> SecList;
    
    
    MainPolygon mainPolygon;
    
    
    
    bool PreSolve_;
    bool ContactBegin_;
    
    float startSquare;
    float currentSquare;
    float winPercentage;
    
        
    bool createPolygon_;
    
    cocos2d::Vec2 direction;
    
    
    std::stack<int> physicsStack;
    
    std::vector<cocos2d::Node*> lineList;
    cocos2d::Node *currentLine;
    cocos2d::Vec2 lastPoint;
    
    cocos2d::Vec2 contactPoint;
    
    cocos2d::EventListenerTouchOneByOne *touchListener;
    
    void closeScene(cocos2d::Ref* pSender);
    void createPhysicLine(Vec2 begin, Vec2 end);
    void createEnemies();
    void swipe();
    void defeat();
    void victory();
    void stopScene();
    void setSceneToDefault();
public:
    static cocos2d::Scene* createScene(int);
    static cocos2d::Scene* createWithPhysics();
    virtual bool initWithPhysics();
    virtual void update(float);
    
    
    //CREATE_FUNC(GameScene);
};



#endif /* defined(__TuturialProject__GameScene__) */
