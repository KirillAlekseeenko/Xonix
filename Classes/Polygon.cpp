//
//  Polygon.cpp
//  TuturialProject
//
//  Created by Кирилл Алексеенко on 05.09.15.
//
//

#include "Polygon.h"


Polygon::Polygon()
{
    this->amount = 0;
}

cocos2d::Vec2* Polygon::getVerticesArray()
{
    return this->arr;
}
void InsertionSort(cocos2d::Vec2 &p, int n, bool y)
{
    cocos2d::Vec2 *arr = &p;
    cocos2d::Vec2 x;
    long i, j;
    
    for ( i=0; i < n; i++) {  // цикл проходов, i - номер прохода
        x = arr[i];
        
        // поиск места элемента в готовой последовательности
        for ( j=i-1; j>=0 && y? arr[j].y > x.y : arr[j].x > x.x; j--)
            arr[j+1] = arr[j];  	// сдвигаем элемент направо, пока не дошли
        
        // место найдено, вставить элемент
        arr[j+1] = x;
    }
}

void Polygon::chooseTwoAppropriatePoints(cocos2d::Vec2 userPoint, int &other1, int &other2)
{
    cocos2d::Vec2 X[NPoly/2];
    cocos2d::Vec2 Y[NPoly/2];
    int count_x = 0;
    int count_y = 0;
    for(int i = 0;i < amount;i++)
    {
        if(userPoint.x == arr[i].x)
        {
            X[count_x] = arr[i];
            count_x++;
        }
        if(userPoint.y == arr[i].y)
        {
            Y[count_y] = arr[i];
            count_y++;
        }
    }
    X[count_x++] = userPoint;
    Y[count_y++] = userPoint;
    InsertionSort(*X, count_x, true);
    InsertionSort(*Y ,count_y, false);
    std::cout<<"Arr"<<endl;
    for(int i = 0;i < amount;i++)
    {
        std::cout<<"NonSortedpoints:"<<arr[i].x<< " "<<arr[i].y<<endl;
    }
    std::cout<<"X"<<endl;
    for(int i = 0;i < count_x;i++)
    {
        std::cout<<"Sortedpoints:"<<X[i].x<< " "<<X[i].y<<endl;
    }
    std::cout<<"Y"<<endl;
    for(int i = 0;i < count_y;i++)
    {
        std::cout<<"Sortedpoint1:"<<Y[i].x<< " "<<Y[i].y<<endl;
    }
    int i_x, i_y;
    for(int i = 0;i < count_x;i++)
    {
        if(X[i] == userPoint)
        {
            i_x = i;
            break;
        }
    }
    for(int i = 0;i < count_y;i++)
    {
        if(Y[i] == userPoint)
        {
            i_y = i;
            break;
        }
    }
    if(i_y == 0 || i_y == count_y - 1)
    {
        cocos2d::Vec2 d1 = X[i_x-1];
        cocos2d::Vec2 d2 = X[i_x+1];
        for(int i = 0;i < amount; i++)
        {
            if(d1 == arr[i])
                other1 = Tag[i];
            if(d2 == arr[i])
                    other2 = Tag[i];
            
        }
        return;
    }
    if(i_x == 0 || i_x == count_x - 1)
    {
        cocos2d::Vec2 d1 = Y[i_y-1];
        cocos2d::Vec2 d2 = Y[i_y+1];
        for(int i = 0;i < amount; i++)
        {
            if(d1 == arr[i])
                other1 = Tag[i];
            if(d2 == arr[i])
                other2 = Tag[i];
            
        }

        return;
    }
        
            
}


void Polygon::addPoint(cocos2d::Vec2 point, int Tag)
{
    arr[amount] = point;
    this->Tag[amount] = Tag;
    amount++;
}


void Polygon::setPolyTag(int Tag)
{
    this->PolyTag = Tag;
}


int Polygon::getPolyTag()
{
    return this->PolyTag;
}

