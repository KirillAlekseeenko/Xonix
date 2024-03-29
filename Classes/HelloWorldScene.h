#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // a selector callback
    void menuQuitCallback(cocos2d::Ref* pSender);
    void menuSettingsCallback(cocos2d::Ref* pSender);
    void menuStartCallback(cocos2d::Ref* pSender);
    void menuAboutCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    
};

#endif // __HELLOWORLD_SCENE_H__
