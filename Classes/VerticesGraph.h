//
//  VerticesGraph.h
//  TuturialProject
//
//  Created by Кирилл Алексеенко on 06.09.15.
//
//

#ifndef __TuturialProject__VerticesGraph__
#define __TuturialProject__VerticesGraph__

#include <stdio.h>
#include <list>
#include "cocos2d.h"
#include "Polygon.h"


const int N = 2000;

class VerticesGraph
{
    short int Matrix[N][N];
    cocos2d::Vec2 dots[N];
    int amount;
public:
    VerticesGraph();
    void addEdge(int begin, int end, cocos2d::Vec2 endPoint);
    void deleteEdge(int begin, int end);
    void insertVerticesBetweenTwoOther(int begin, int end, int vertice, cocos2d::Vec2 dot);
    cocos2d::Vec2 &getDot(int tag);
    Polygon& createPolygon(int begin, int end);
};

#endif /* defined(__TuturialProject__VerticesGraph__) */
