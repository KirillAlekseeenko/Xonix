#include "HelloWorldScene.h"
#include "iostream"
#include "LevelScene.hpp"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    std::cout<<"INIT HELLO WORLD\n";
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Vector<MenuItem*> MenuItems;
    
    auto quitLabel = LabelTTF::create("Quit", "Marker Felt.ttf", 64);
    auto quitMenu = MenuItemLabel::create(quitLabel, CC_CALLBACK_1(HelloWorld::menuQuitCallback, this));
    quitMenu->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2 - 70));
    
    auto settingsLabel = LabelTTF::create("Settings", "Marker Felt.ttf", 64);
    auto settingsMenu = MenuItemLabel::create(settingsLabel, CC_CALLBACK_1(HelloWorld::menuSettingsCallback, this));
    settingsMenu->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2 + 70));
    
    auto startLabel = LabelTTF::create("Start", "Marker Felt.ttf", 64);
    auto startMenu = MenuItemLabel::create(startLabel, CC_CALLBACK_1(HelloWorld::menuStartCallback, this));
    startMenu->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2 + 140));
    
    auto aboutLabel = LabelTTF::create("About", "Marker Felt.ttf", 64);
    auto aboutMenu = MenuItemLabel::create(aboutLabel, CC_CALLBACK_1(HelloWorld::menuAboutCallback, this));
    aboutMenu->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2));
    
    MenuItems.pushBack(quitMenu);
    MenuItems.pushBack(settingsMenu);
    MenuItems.pushBack(startMenu);
    MenuItems.pushBack(aboutMenu);
    
    auto menuExample = Menu::createWithArray(MenuItems);
    menuExample->setPosition(Vec2::ZERO);
    this->addChild(menuExample, 1);
    
    
    
    return true;
}

void HelloWorld::menuQuitCallback(cocos2d::Ref* pSender)
{
    std::cout<<"Quit\n";
}
void HelloWorld::menuSettingsCallback(cocos2d::Ref* pSender)
{
    std::cout<<"Settings\n";
}
void HelloWorld::menuStartCallback(cocos2d::Ref* pSender)
{
    std::cout<<"Start\n";
    Director::getInstance()->pushScene(LevelScene::createScene());
}
void HelloWorld::menuAboutCallback(cocos2d::Ref* pSender)
{
    std::cout<<"About\n";
}






