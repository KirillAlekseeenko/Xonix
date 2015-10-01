//
//  VerticesGraph.cpp
//  TuturialProject
//
//  Created by Кирилл Алексеенко on 06.09.15.
//
//

#include "VerticesGraph.h"

VerticesGraph::VerticesGraph()
{
    amount = 0;
    for(int i = 0;i < N;i++)
    {
        dots[i] = cocos2d::Vec2::ZERO;
        for(int j = 0;j < N;j++)
        {
            Matrix[i][j] = 0;
        }
    }
}

void VerticesGraph::addEdge(int begin, int end, cocos2d::Vec2 endPoint)
{
    dots[end] = endPoint;
    if(begin>=amount)
        amount++;
    if(end>=amount)
        amount++;
    Matrix[begin][end] = 1;
    Matrix[end][begin] = 1;
}
void VerticesGraph::deleteEdge(int begin, int end)
{
    Matrix[begin][end] = 0;
}
void VerticesGraph::insertVerticesBetweenTwoOther(int begin, int end, int vertice, cocos2d::Vec2 dot)
{
    if(vertice>=amount)
        amount++;
    Matrix[begin][end] = 0;
    Matrix[begin][vertice] = 1;
    Matrix[vertice][end] = 1;
    dots[vertice] = dot;
    Matrix[end][begin] = 0;
    Matrix[end][vertice] = 1;
    Matrix[vertice][end] = 1;
}
cocos2d::Vec2 &VerticesGraph::getDot(int tag)
{
    return this->dots[tag];
}

Polygon& VerticesGraph::createPolygon(int begin, int end)
{
    
}
