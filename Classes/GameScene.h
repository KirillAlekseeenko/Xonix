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
#include "MyDrawNode.hpp"
#include <stack>

class GameScene : public cocos2d::Scene
{
    bool _gameBegun;
    
    DrawNode *character;
    cocos2d::RenderTexture *canvas;
    
    std::vector<Vec2> SecList;
    
    
    MainPolygon mainPolygon;
    
    
    
    //std::vector<Vec2> polygon;
    //std::vector<int> indices;
    //Vec2 *polygon_;
    bool PreSolve_;
    bool ContactBegin_;
    
    float startArea;
    float currentArea;
    
    //std::vector<int> indices;
    //std::vector<Vec2> polygon;
    //Vec2 *polygon_;
    
    bool createPolygon_;
    
    cocos2d::Vec2 direction;
    
    
    std::stack<int> physicsStack;
    
    
    
    void closeScene(cocos2d::Ref* pSender);
    void createPhysicLine(Vec2 begin, Vec2 end);
public:
    static cocos2d::Scene* createScene(int);
    static cocos2d::Scene* createWithPhysics();
    virtual bool initWithPhysics();
    virtual void update(float);
    
    
    //CREATE_FUNC(GameScene);
};



#endif /* defined(__TuturialProject__GameScene__) */
