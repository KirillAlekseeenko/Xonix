//
//  MainPolygon.h
//  TuturialProject
//
//  Created by Кирилл Алексеенко on 21.09.15.
//
//

#ifndef __TuturialProject__MainPolygon__
#define __TuturialProject__MainPolygon__


#include <iostream>
#include <vector>
#include <algorithm>
#include "cocos2d.h"
#include "ArcList.h"



class BeginEndException
{
public:
    BeginEndException(){};
};

/*class NULLContainer
{
    static std::vector<cocos2d::Vec2> nullvector;
public:
    static void setToEnd(std::vector<cocos2d::Vec2>::iterator &i)
    {
        i = nullvector.end();
    }
    static bool check(const std::vector<cocos2d::Vec2>::iterator &i)
    {
        if(i == nullvector.end())
            return true;
        else
            return false;
    }
    
};*/




class MainPolygon
{
    
    float Square;
    
    
    cocos2d::Vec2 normalBegin;
    cocos2d::Vec2 normalEnd;
    
    bool isNewBeginPoint;
    
    
    CircularList mainList;
    
    Unit *beginPoint;
    Unit *endPoint;
    
    
public:
    MainPolygon(){
        beginPoint = nullptr;
        endPoint = nullptr;
        
        isNewBeginPoint = true;
        
        // normal is used to move borders of polygon for a reason of stucking character in physics model
        
        cocos2d::Vec2 normalBegin = cocos2d::Vec2::ZERO;
        cocos2d::Vec2 normalEnd = cocos2d::Vec2::ZERO;
        
        
        Square = 50000; // will be changed in future
        
        
        
        
    }
    ~MainPolygon(){}
    void addPoint(const cocos2d::Vec2 &Point);
    void addBeginPoint(cocos2d::Vec2 &bPoint, const cocos2d::Vec2& normal);
    void addEndPoint(cocos2d::Vec2 &ePoint, const cocos2d::Vec2& normal);
    std::vector<cocos2d::Vec2> getPath(const std::vector<cocos2d::Vec2>& newPoints);
    // where newPoints - path from beginPoint to endPoint
    //return vector - new polygon, that will be created later
    
    
    void printPoints();

};




#endif /* defined(__TuturialProject__MainPolygon__) */
