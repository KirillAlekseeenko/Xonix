//
//  LevelScene.cpp
//  TuturialProject
//
//  Created by Кирилл Алексеенко on 13.10.15.
//
//

#include "LevelScene.hpp"

Scene* LevelScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LevelScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool LevelScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    _currentLevel = UserDefault::getInstance()->getIntegerForKey(STRING_LEVEL, -1);
    
    if(_currentLevel == -1)
    {
        _currentLevel = 1;
    }
    
    std::cout<<"INIT HELLO WORLD\n";
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    
    Vector<MenuItem*> menuItems;
    
    
    
    for(int i = 1;i <= _currentLevel;i++)
    {
        auto label = Label::createWithTTF("Level " + std::to_string(i), "fonts/Marker Felt.ttf", 32);
        auto menuItem = MenuItemLabel::create(label, [i](cocos2d::Ref* pSender)
        {
            Director::getInstance()->replaceScene(GameScene::createScene(i));
        });
        menuItem->setPosition(RelativePosition::getPosition(Vec2(300, 2900 - i * 200), frameSize));
        menuItems.pushBack(menuItem);
    }
    
    auto menu = Menu::createWithArray(menuItems);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    
    return true;
}
