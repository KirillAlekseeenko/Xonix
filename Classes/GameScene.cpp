//
//  GameScene.cpp
//  TuturialProject
//
//  Created by Кирилл Алексеенко on 12.06.15.
//
//

#include "GameScene.h"
#include "TransactionHandler.hpp"
//#include "algorithm"

USING_NS_CC;


bool _isDrawing;
bool _isTouchDown;
bool _isMoving;
float _initialTouchPos[2];
float _currentTouchPos[2];
int _time = 0;
const float _speed = 100;
float _swipeLength;
const float _PI = 3.141592653589793238462643383279502884L;
bool removing_objects;
bool character_move;

float margin = 1;



int GameScene::_currentLevel;








Scene* GameScene::createScene(int level)
{
    _currentLevel = level;
    auto gamescene = GameScene::createWithPhysics();
    //GameScene::createWithPhysics();
    return gamescene;
}
Scene* GameScene::createWithPhysics()
{
    GameScene *ret = new (std::nothrow) GameScene();
    if (ret && ret->initWithPhysics())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}


void GameScene::setSceneToDefault()
{
    /*auto topBorder = DrawNode::create();
     topBorder->setName("TOP");
     topBorder->setTag(-1);
     Vec2 topBorderVecArr[4] = {RelativePosition::getPosition(Vec2(0, 2500), frameSize), RelativePosition::getPosition(Vec2(0, 3000), frameSize), RelativePosition::getPosition(Vec2(4000, 3000), frameSize), RelativePosition::getPosition(Vec2(4000, 2500), frameSize)};
     topBorder->drawSolidPoly(topBorderVecArr, 4, Color4F(1.0f,0.0f,0.0f,1.0f));
     topBorder->setPosition(Vec2(0, 0));
     addChild(topBorder);
     
     
     
     auto lowBorder = DrawNode::create();
     lowBorder->setName("LOW");
     lowBorder->setTag(-3);
     Vec2 lowBorderVecArr[4] = {RelativePosition::getPosition(Vec2(0, 500), frameSize), RelativePosition::getPosition(Vec2(4000, 500), frameSize), RelativePosition::getPosition(Vec2(4000, 0), frameSize), RelativePosition::getPosition(Vec2(0, 0), frameSize)};
     lowBorder->drawSolidPoly(lowBorderVecArr, 4, Color4F(1.0f,0.0f,0.0f,1.0f));
     lowBorder->setPosition(Vec2(0, 0));
     addChild(lowBorder);
     
     
     
     auto leftBorder = DrawNode::create();
     leftBorder->setName("LEFT");
     leftBorder->setTag(-4);
     Vec2 leftBorderVecArr[4] = {RelativePosition::getPosition(Vec2(0, 2500), frameSize), RelativePosition::getPosition(Vec2(500, 2500), frameSize), RelativePosition::getPosition(Vec2(500, 500), frameSize), RelativePosition::getPosition(Vec2(0, 500), frameSize)};
     leftBorder->drawSolidPoly(leftBorderVecArr, 4,  Color4F(1.0f,0.0f,0.0f,1.0f));
     leftBorder->setPosition(Vec2(0, 0));
     addChild(leftBorder);
     
     
     auto rightBorder = DrawNode::create();
     rightBorder->setName("RIGHT");
     rightBorder->setTag(-2);
     Vec2 rightBorderVecArr[4] = {RelativePosition::getPosition(Vec2(3500, 2500), frameSize), RelativePosition::getPosition(Vec2(4000, 2500), frameSize), RelativePosition::getPosition(Vec2(4000, 500), frameSize), RelativePosition::getPosition(Vec2(3500, 500), frameSize)};
     rightBorder->drawSolidPoly(rightBorderVecArr, 4,  Color4F(1.0f,0.0f,0.0f,1.0f));
     rightBorder->setPosition(Vec2(0, 0));
     addChild(rightBorder);*/
    
    
    
    
    
    
    while(!CollisionDots::getCurrentCollision().empty())
    {
        CollisionDots::getCurrentCollision().pop();
    }
    
    auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    
    _gameBegun = false;
    _isDrawing = false;
    removing_objects = false;
    character_move = false;
    _isMoving = false;
    
    Vec2 StartPoly[5] = {RelativePosition::getPosition(Vec2(500, 2500), frameSize), RelativePosition::getPosition(Vec2(500, 500), frameSize), RelativePosition::getPosition(Vec2(3500, 500), frameSize), RelativePosition::getPosition(Vec2(3500, 2500), frameSize), RelativePosition::getPosition(Vec2(500, 2500), frameSize) };
    
    mainPolygon.addPoint(StartPoly[3]);
    mainPolygon.addPoint(StartPoly[2]);
    mainPolygon.addPoint(StartPoly[1]);
    mainPolygon.addPoint(StartPoly[0]);
    
    std::vector<Vec2> initial_polygon;
    initial_polygon.push_back(StartPoly[0]);
    initial_polygon.push_back(StartPoly[1]);
    initial_polygon.push_back(StartPoly[2]);
    initial_polygon.push_back(StartPoly[3]);
    
    startSquare = getSquare(initial_polygon);
    currentSquare = startSquare;
    winPercentage = 0.4;
    
    for(int i = 0;i < 4;i++)
    {
        auto vv = (StartPoly[i+1] - StartPoly[i]).getNormalized();
        auto node = cocos2d::Node::create();
        node->setTag(i);
        physicsStack.push(i);
        auto body = PhysicsBody::createEdgeSegment(StartPoly[i] + vv * margin, StartPoly[i+1] - vv * margin);
        body->setTag(i);
        body->setDynamic(false);
        body->setContactTestBitmask(true);
        node->setPhysicsBody(body);
        addChild(node);
        std::cout<<"added "<< i<<endl;
    }
    
    auto defeatMenu = this->getChildByName("DefeatMenu");
    if(defeatMenu != nullptr)
    {
        defeatMenu->removeFromParent();
    }
    
    
    auto levelLabel = Label::createWithTTF("Level " + std::to_string(_currentLevel), "fonts/Marker Felt.ttf", 64);
    levelLabel->setPosition(RelativePosition::getPosition(Vec2(1500, 2800), frameSize));
    addChild(levelLabel);
    

    createPolygon_ = false;
    
    character->setPosition(RelativePosition::getPosition(Vec2(2000, 500) + Vec2(0, 1), frameSize));
    
    for(auto x : enemies)
    {
        x->setPosition(300,300);
        x->getPhysicsBody()->setVelocity(Vec2(100, 100));
    }
    
}


bool GameScene::initWithPhysics()
{
    if(!Scene::initWithPhysics())
    {
        return false;
    }
    
    
    
    
    
    
    this->currentLine = nullptr;
    
    this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    //this->getPhysicsWorld()->setSubsteps(100);
    //this->getPhysicsWorld()->setAutoStep(false);
    //this->getPhysicsWorld()->step(0.1);
    this->getPhysicsWorld()->setSubsteps(100);
    std::cout<<"Speed: "<<this->getPhysicsWorld()->getSpeed()<<", "<<"Substeps: "<<this->getPhysicsWorld()->getSubsteps()<<", "<<
    "UpdateRate: "<<this->getPhysicsWorld()->getUpdateRate()<<", "<<std::endl;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    
    this->getPhysicsWorld()->setGravity(Vec2::ZERO);
    
    
    
    
    canvas = RenderTexture::create(visibleSize.width, visibleSize.height);
    canvas->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2));
    addChild(canvas, -3);
    
    _swipeLength = 300;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    character = DrawNode::create();
    character->drawSolidRect(RelativePosition::getSize(Vec2(-50, -50), frameSize), RelativePosition::getSize(Vec2(50,50),frameSize),Color4F(0.0f,1.0f,0.0f,1.0f));
    
    
    auto enemy = DrawNode::create();
    enemy->setName("Enemy");
    enemy->drawSolidRect(RelativePosition::getSize(Vec2(-50, -50), frameSize), RelativePosition::getSize(Vec2(50,50),frameSize),Color4F(0.0f,0.0f,1.0f,1.0f));
    auto ebody = PhysicsBody::createCircle(1, PhysicsMaterial(0.0f, 2, 0.0f));
    ebody->setDynamic(true);
    ebody->setContactTestBitmask(true);
    ebody->setRotationEnable(false);
    enemy->setPhysicsBody(ebody);
    addChild(enemy);
    enemies.push_back(enemy);

    
    
    setSceneToDefault();
    
    
    
    //character = Sprite::create("Character.png");
    //character->setPosition(RelativePosition::getPosition(Vec2(2000, 500) + Vec2(0, 1), frameSize));
    //auto cbody = PhysicsBody::createBox(RelativePosition::getSize(Size(2,2), frameSize),PhysicsMaterial(100.0f, 0, 0.0f));
    auto cbody = PhysicsBody::createCircle(1, PhysicsMaterial(100.0f, 0, 0.0f));
    cbody->setContactTestBitmask(true);
    cbody->setDynamic(true);
    cbody->setRotationEnable(false);
    character->setPhysicsBody(cbody);
    character->setName("Character");
    addChild(character);
    
    
    
    auto contactListener = EventListenerPhysicsContact::create();
    

    
    contactListener->onContactBegin = [this, frameSize](PhysicsContact& contact)
    {
        auto nodeA = contact.getShapeA()->getBody()->getNode();
        auto nodeB = contact.getShapeB()->getBody()->getNode();
        std::cout<<nodeB->getTag()<<endl;
        
        std::cout<<"CONTACT: "<<nodeA->getName()<<" AND "<<nodeB->getName()<<" "<<CollisionDots::getCurrentCollision().empty()<<std::endl;
        std::cout<<"ContactData: "<<"count - "<<contact.getContactData()->count<<", normal - ("<<contact.getContactData()->normal.x<<","<<contact.getContactData()->normal.y<<"), "<<"points - ("<<contact.getContactData()->points[0].x<<", "<<contact.getContactData()->points[0].y<<")   ,("<<contact.getContactData()->points[1].x<<", "<<contact.getContactData()->points[1].y<<")   "<<"NodePosition: ("<<nodeA->getPositionX()<<", "<<nodeA->getPositionY()<<")  ("<<nodeB->getPositionX()<<", "<<nodeB->getPositionY()<<")"<<std::endl;
        
        if((nodeA->getName() == "Enemy" && nodeB->getName() == "Line") || (nodeB->getName() == "Enemy" && nodeA->getName() == "Line"))
        {
            this->defeat();
            //DEFEAT
        }
        
        if(nodeA->getName() == "Line" || nodeB->getName() == "Line")
        {
            return true;
        }
        if(nodeA->getName() == "Enemy" || nodeB->getName() == "Enemy")
        {
            return true;
        }
            

            if(CollisionDots::getCurrentCollision().empty() && _gameBegun)
            {
                
                
                if(nodeA->getName() == "Character" || nodeB->getName() == "Character")
                {
                    Vec2 contactPoint;
                    
                    
                    if(contact.getContactData()->count == 1)
                    {
                        contactPoint = contact.getContactData()->points[0];
                    }
                    else
                    {
                        contactPoint = (contact.getContactData()->points[0] + contact.getContactData()->points[1])/2.0;
                    }
                    
                    
                    
                    _isDrawing = false;
                    this->canvas->clear(0, 0, 0, 0);
                    
                    mainPolygon.addEndPoint(contactPoint, contact.getContactData()->normal);
                    
                    mainPolygon.printPoints();
                    
                    
                    std::cout<<"SecList"<<endl;
                    for(auto i = SecList.begin();i!=SecList.end();i++)
                    {
                        std::cout<<(*i).x<<" "<<(*i).y<<"<->";
                    }
                    
                    std::vector<Vec2> mainList;
                    
                    auto node = DrawNode::create();
                    
                    std::vector<Vec2> polygon;
                    
                    float square;
                    
                    try{
                        polygon = mainPolygon.getPath(SecList, mainList, this->direction, square);
                        currentSquare -= square;
                        
                        
                    }
                    catch(BeginEndException)
                    {
                        MessageBox("Error", "BeginEndError");
                        cout<<"BeginEndError";
                        return false;
                    }
                    
                    if(currentSquare / startSquare < winPercentage)
                    {
                        this->victory();
                    }
                    
                
                    std::cout<<"\nPolygonBeforeTriagonalization: ";
                    for(auto x : polygon)
                    {
                        std::cout<<"("<<x.x<<", "<<x.y<<") ";
                    }
                    std::cout<<std::endl;
                    
                    mainPolygon.printPoints();
                    
                    std::cout<<"\nmainList: ";
                    for(auto x : mainList)
                    {
                        std::cout<<"("<<x.x<<", "<<x.y<<") ";
                    }
                    
                    std::vector<int> indices;
                    
                    indices = math::triangulate<int>(polygon);
                    
                    
                    std::cout<<"\nPolygonAfterTriagonalization: ";
                    for(auto x : polygon)
                    {
                        std::cout<<"("<<x.x<<", "<<x.y<<") ";
                    }
                    std::cout<<std::endl;
                    
                    std::cout<<"Indices: ";
                    
                    /*for(int i = 0;i < indices.size();i+=3)
                    {
                        std::cout<<"("<<polygon[indices[i]].x<<", "<<polygon[indices[i]].y<<") <->";
                        std::cout<<"("<<polygon[indices[i+1]].x<<", "<<polygon[indices[i+1]].y<<") <->";
                        std::cout<<"("<<polygon[indices[i+2]].x<<", "<<polygon[indices[i+2]].y<<") <->";
                        std::cout<<" ***** ";
                        node->drawTriangle(polygon[indices[i]], polygon[indices[i+1]], polygon[indices[i+2]], Color4F::GREEN);
                        
                    }*/
                    
                    
                    removing_objects = true;
                    
                    
                    character->getPhysicsBody()->setContactTestBitmask(false);
                    
                    this->update(0.001);
                    
                    removing_objects = false;
                    
                    
                    
                    for(int i = 0;i < mainList.size() - 1;i++)
                    {
                        auto vv = (mainList[i+1] - mainList[i]).getNormalized();
                        auto node = cocos2d::Node::create();
                        node->setTag(i);
                        physicsStack.push(i);
                        auto body = PhysicsBody::createEdgeSegment(mainList[i] + vv * margin, mainList[i+1] - vv * margin);
                        body->setDynamic(false);
                        body->setContactTestBitmask(true);
                        node->setPhysicsBody(body);
                        addChild(node);
                        std::cout<<"added "<< i<<endl;
                    }
                    
                    _gameBegun = false;

                    character->getPhysicsBody()->setContactTestBitmask(true);
                    
                    SecList.clear();
                    
                    character_move = true;
                    
                    std::cout<<"\nLINELIST_SIZE = "<<lineList.size()<<endl;
                    
                    for(auto x : lineList)
                    {
                        x->removeFromParent();
                    }
                    lineList.clear();
                    
                    if(currentLine != nullptr)
                        this->currentLine->removeFromParent();
                    currentLine = nullptr;
                    
                    this->contactPoint = contactPoint;
                    
                    //addChild(node);
                    
                    return true;
                    
                    
                }
            }
        if(!_gameBegun)
        {
            _gameBegun = true;
            CollisionDots::getCurrentCollision().push(contact.getContactData()->points[0]);
            return true;
        }
        CollisionDots::getCurrentCollision().push(contact.getContactData()->points[0]);
        //std::cout<<"Contact: "<<nodeA->getName()<<" AND "<<nodeB->getName()<<" "<<CollisionDots::getCurrentCollision().empty()<<std::endl;
        return true;
    };
    
    
    
    
    
    
    contactListener->onContactSeperate = [this](PhysicsContact& contact)
    {
        if(!_gameBegun)
            return;
        auto nodeA = contact.getShapeA()->getBody()->getNode();
        auto nodeB = contact.getShapeB()->getBody()->getNode();
        std::cout<<nodeB->getTag()<<endl;
        std::cout<<"SEPARATE: "<<nodeA->getName()<<" AND "<<nodeB->getName()<<std::endl;
        std::cout<<"ContactData: "<<"count - "<<contact.getContactData()->count<<", normal - ("<<contact.getContactData()->normal.x<<","<<contact.getContactData()->normal.y<<"), "<<"points - ("<<contact.getContactData()->points[0].x<<", "<<contact.getContactData()->points[0].y<<")   ,("<<contact.getContactData()->points[1].x<<", "<<contact.getContactData()->points[1].y<<")   "<<"NodePosition: ("<<nodeA->getPositionX()<<", "<<nodeA->getPositionY()<<")  ("<<nodeB->getPositionX()<<", "<<nodeB->getPositionY()<<")"<<std::endl;
        
        if(nodeA->getName() == "Line" || nodeB->getName() == "Line")
        {
            return;
        }
        if(nodeA->getName() == "Enemy" || nodeB->getName() == "Enemy")
        {
            return;
        }
        
        if(nodeA->getName() == "Character" || nodeB->getName() == "Character")
        {
            
            if(!CollisionDots::getCurrentCollision().empty())
                CollisionDots::getCurrentCollision().pop();
            if(CollisionDots::getCurrentCollision().empty())
            {
                Vec2 contactPoint;
                if(nodeA->getName() == "Character")
                {
                    contactPoint = nodeA->getPosition();
                }
                else
                {
                    contactPoint = nodeB->getPosition();
                }
                
                this->lastPoint = contactPoint;
                
                mainPolygon.addBeginPoint(this->lastPoint, contact.getContactData()->normal);
                
                mainPolygon.printPoints();
                
                _isDrawing = true;
                
                
                
                std::cout<<"SecList"<<endl;
                for(auto i = SecList.begin();i!=SecList.end();i++)
                {
                    std::cout<<(*i).x<<" "<<(*i).y<<"<->";
                }
                
            }
        }
    };
    
    
    
    touchListener = EventListenerTouchOneByOne::create();
    
    
    touchListener->setSwallowTouches(true);
    
    touchListener->onTouchBegan = [](Touch* touch, Event* event){
        if(!_isMoving)
        _isMoving = true;
        _initialTouchPos[0] = touch->getLocation().x;
        _initialTouchPos[1] = touch->getLocation().y;
        _currentTouchPos[0] = touch->getLocation().x;
        _currentTouchPos[1] = touch->getLocation().y;
        
        _isTouchDown = true;
        
        return true;
    };
    
    touchListener->onTouchMoved = [](Touch* touch, Event* event){
        _currentTouchPos[0] = touch->getLocation().x;
        _currentTouchPos[1] = touch->getLocation().y;
    };
    
    touchListener->onTouchEnded = [=](Touch* touch, Event* event){
        _isTouchDown = false;
    };
    
    touchListener->onTouchCancelled = [=](Touch* touch, Event* event){
        _isTouchDown = false;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    _isTouchDown = false;
    
    _initialTouchPos[0] = 0;
    _initialTouchPos[1] = 0;
    
    this->scheduleUpdate();
    
    
    return true;
}

void GameScene::update(float dt)
{
    if(removing_objects)
    {
        //this->character->getPhysicsBody()->setVelocity(Vec2(0, 3));
        
        std::cout<<"\nDIRECTION: ("<<this->direction.x<<", "<<this->direction.y<<")\n";
        this->character->getPhysicsBody()->setVelocity(Vec2::ZERO);
        while(!physicsStack.empty())
        {
            auto nn = this->getChildByTag(physicsStack.top());
            std::cout<<"deleted "<< nn->getTag()<<endl;
            nn->removeFromParent();
            
            physicsStack.pop();
            
        }
    }
    if(character_move)
    {
        this->character->setPosition(this->contactPoint + this->direction);
        character_move = false;
    }
    _time++;
    if(_isDrawing)
    {
        if(currentLine != nullptr)
        {
            currentLine->removeFromParent();
        }
        currentLine = Node::create();
        auto linebody = PhysicsBody::createEdgeSegment(lastPoint, this->character->getPosition());
        linebody->setContactTestBitmask(true);
        currentLine->setName("Line");
        currentLine->setPhysicsBody(linebody);
        addChild(currentLine);
        
        canvas->begin();
        character->visit();
        canvas->end();
        _time = 0;
    }
    if(_isTouchDown == true)
    {
        if (_initialTouchPos[0] - _currentTouchPos[0] > _swipeLength * 0.05)
        {
            if(character->getPhysicsBody()->getVelocity().x != _speed)
            {
                if(_isDrawing)
                {
                    character->getPhysicsBody()->setVelocity(Vec2::ZERO);
                    SecList.push_back(character->getPosition());
                    
                    this->lastPoint = this->character->getPosition();
                    lineList.push_back(currentLine);
                    currentLine = nullptr;
                }
                
                
                
                
                character->getPhysicsBody()->setVelocity(Vec2(-_speed,0));
                CCLOG("SWIPED LEFT");
                _isTouchDown = false;
            }
        }
        else if (_initialTouchPos[0] - _currentTouchPos[0] < - _swipeLength * 0.05)
        {
            if(character->getPhysicsBody()->getVelocity().x != -_speed)
            {
                if(_isDrawing)
                {
                    character->getPhysicsBody()->setVelocity(Vec2::ZERO);
                    SecList.push_back(character->getPosition());
                    
                    this->lastPoint = this->character->getPosition();
                    lineList.push_back(currentLine);
                    currentLine = nullptr;
                }
                
                
                
                character->getPhysicsBody()->setVelocity(Vec2(_speed,0));
                CCLOG("SWIPED RIGHT");
                _isTouchDown = false;
            }
        }
        else if (_initialTouchPos[1] - _currentTouchPos[1] > _swipeLength * 0.05)
        {
            if(character->getPhysicsBody()->getVelocity().y != _speed)
            {
                if(_isDrawing)
                {
                    character->getPhysicsBody()->setVelocity(Vec2::ZERO);
                    SecList.push_back(character->getPosition());
                    
                    this->lastPoint = this->character->getPosition();
                    lineList.push_back(currentLine);
                    currentLine = nullptr;
                }
                
                
                
                character->getPhysicsBody()->setVelocity(Vec2(0,-_speed));
                CCLOG("SWIPED DOWN");
                _isTouchDown = false;
            }
        }
        else if (_initialTouchPos[1] - _currentTouchPos[1] < - _swipeLength * 0.05)
        {
            if(character->getPhysicsBody()->getVelocity().y != -_speed)
            {
                if(_isDrawing)
                {
                    character->getPhysicsBody()->setVelocity(Vec2::ZERO);
                    SecList.push_back(character->getPosition());
                    
                    this->lastPoint = this->character->getPosition();
                    lineList.push_back(currentLine);
                    currentLine = nullptr;
                }
                

                
                character->getPhysicsBody()->setVelocity(Vec2::ZERO);
                character->getPhysicsBody()->setVelocity(Vec2(0,_speed));
                CCLOG("SWIPED UP");
                _isTouchDown = false;
            }
        }
    }
}

void GameScene::stopScene()
{
    this->character->getPhysicsBody()->setVelocity(Vec2::ZERO);
    for(auto x : enemies)
    {
        x->getPhysicsBody()->setVelocity(Vec2::ZERO);
    }
}




void GameScene::defeat()
{
    
    stopScene();
    Director::getInstance()->pause();
    
    this->touchListener->setEnabled(false);
    cocos2d::Vector<MenuItem*> menuItems;
    
    
    
    auto tryagainLabel = Label::createWithTTF("Try again", "fonts/Marker Felt.ttf", 64);
    auto tryagainItem = MenuItemLabel::create(tryagainLabel, [this](cocos2d::Ref* pSender)
    {
        this->unscheduleAllCallbacks();
        TransactionHandler::loadLevel(_currentLevel);
    
    });
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto visibleOrigin = Director::getInstance()->getVisibleOrigin();
    tryagainItem->setPosition(visibleOrigin.x + visibleSize.width / 2, visibleOrigin.y + visibleSize.height / 2 + 100);
    
    auto backtomenuLabel = Label::createWithTTF("Back to menu", "fonts/Marker Felt.ttf", 64);
    auto backtomenuItem = MenuItemLabel::create(backtomenuLabel, [this](cocos2d::Ref* pSender)
    {
        this->unscheduleAllCallbacks();
        TransactionHandler::popScene();
    });
    backtomenuItem->setPosition(visibleOrigin.x + visibleSize.width / 2, visibleOrigin.y + visibleSize.height / 2 - 100);

    
    menuItems.pushBack(tryagainItem);
    menuItems.pushBack(backtomenuItem);
    
    auto menu = Menu::createWithArray(menuItems);
    menu->setName("DefeatMenu");
    
    menu->setPosition(Vec2::ZERO);
    
    addChild(menu,20);
    
    
}

void GameScene::victory()
{
    auto _maxLevel = UserDefault::getInstance()->getIntegerForKey(STRING_LEVEL);
    if(_currentLevel + 1 > _maxLevel)
    {
        UserDefault::getInstance()->setIntegerForKey(STRING_LEVEL, _currentLevel + 1);
    }
    
    stopScene();
    Director::getInstance()->pause();
    
    this->touchListener->setEnabled(false);
    cocos2d::Vector<MenuItem*> menuItems;

    
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto visibleOrigin = Director::getInstance()->getVisibleOrigin();
    
    auto backtomenuLabel = Label::createWithTTF("Back to menu", "fonts/Marker Felt.ttf", 64);
    auto backtomenuItem = MenuItemLabel::create(backtomenuLabel, [this](cocos2d::Ref* pSender)
                                                {
                                                    this->unscheduleAllCallbacks();
                                                    
                                                    
                                                    TransactionHandler::popScene();

                                                });
    backtomenuItem->setPosition(visibleOrigin.x + visibleSize.width / 2, visibleOrigin.y + visibleSize.height / 2 - 100);
    
    
    auto toNextLevelLabel = Label::createWithTTF("Next Level", "fonts/Marker Felt.ttf", 64);
    auto toNextLevelItem = MenuItemLabel::create(toNextLevelLabel, [this](cocos2d::Ref* pSender)
                                                {
                                                    this->unscheduleAllCallbacks();
                                                    
                                                    TransactionHandler::loadLevel(_currentLevel + 1);
                                                });
    toNextLevelItem->setPosition(visibleOrigin.x + visibleSize.width / 2, visibleOrigin.y + visibleSize.height / 2 + 100);
    
    
    menuItems.pushBack(backtomenuItem);
    menuItems.pushBack(toNextLevelItem);
    
    auto menu = Menu::createWithArray(menuItems);
    menu->setPosition(Vec2::ZERO);
    
    addChild(menu,20);
}








