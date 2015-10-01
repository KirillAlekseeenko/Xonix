//
//  Polygon.h
//  TuturialProject
//
//  Created by Кирилл Алексеенко on 05.09.15.
//
//

#ifndef __TuturialProject__Polygon__
#define __TuturialProject__Polygon__

#include <stdio.h>
#include <list>
#include "cocos2d.h"
#include <iostream>
//#include "VerticesGraph.h"
using namespace std;

const int NPoly = 50;

class Polygon
{
    int PolyTag;
    int amount;
    cocos2d::Vec2 arr[NPoly];
    int Tag[NPoly];
    //friend void InsertionSort(cocos2d::Vec2 **arr, int n, bool y);
public:
    void setPolyTag(int Tag);
    int getPolyTag();
    Polygon();
    //Polygon(int end, int begin, VerticesGraph& graph);
    cocos2d::Vec2* getVerticesArray();
    void chooseTwoAppropriatePoints(cocos2d::Vec2 userPoint, int &other1, int &other2);
    void addPoint(cocos2d::Vec2 point, int Tag);
};

#endif /* defined(__TuturialProject__Polygon__) */
