//
//  MainPolygon.cpp
//  TuturialProject
//
//  Created by Кирилл Алексеенко on 21.09.15.
//
//

#include "MainPolygon.h"


const float _PI = 3.141592653589793238462643383279502884L;
const float margin = 1;









float getSquare(std::vector<cocos2d::Vec2> arr)
{
    float res = 0, s;
    auto n = arr.size();
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            s = arr[i].x*(arr[n-1].y - arr[i+1].y); //если i == 0, то y[i-1] заменяем на y[n-1]
            res += s;
        }
        else
            if (i == n-1) {
                s = arr[i].x*(arr[i-1].y - arr[0].y); // если i == n-1, то y[i+1] заменяем на y[0]
                res += s;
            }
            else {
                s = arr[i].x*(arr[i-1].y - arr[i+1].y);
                res += s;
            }
    }

    float sq = std::abs(res/2);
    return sq;
}




void MainPolygon::addPoint(const cocos2d::Vec2 &Point)
{
    mainList.push_back(Point);
}

void MainPolygon::addBeginPoint(cocos2d::Vec2 &bPoint, const cocos2d::Vec2& normal)
{
    
    normalBegin = normal;
    auto p = mainList.begin();
    do
    {
        if(isEqual(p->data.x, bPoint.x) && isEqual(p->data.y, bPoint.y))
        {
            beginPoint = p;
            isNewBeginPoint = false;
            break;
        }
        if(isEqual(p->data.x, bPoint.x) && isEqual(p->next->data.x, bPoint.x) &&
           ((p->data.y < bPoint.y && p->next->data.y > bPoint.y ) || (p->data.y > bPoint.y &&  p->next->data.y < bPoint.y)))
        {
            bPoint.x = p->data.x;
            beginPoint = mainList.insert(p->next, bPoint);
            break;
        }
        if(isEqual(p->data.y, bPoint.y) && isEqual(p->next->data.y, bPoint.y) &&
           ((p->data.x < bPoint.x && p->next->data.x > bPoint.x ) || (p->data.x > bPoint.x &&  p->next->data.x < bPoint.x)))
        {
            bPoint.y = p->data.y;
            beginPoint = mainList.insert(p->next, bPoint);
            break;
        }
        
        p = p->next;
        
    }while(p != mainList.begin());
    
}

void MainPolygon::addEndPoint(cocos2d::Vec2 &ePoint, const cocos2d::Vec2& normal)
{
    if(!isNewBeginPoint)
    {
        if(isEqual(beginPoint->data.x, ePoint.x))
            ePoint.x = beginPoint->data.x;
        if(isEqual(beginPoint->data.y, ePoint.y))
            ePoint.y = beginPoint->data.y;
    }
    normalEnd = normal;
    auto p = mainList.begin();
    do
    {
        
        if(isEqual(p->data.x, ePoint.x) && isEqual(p->next->data.x, ePoint.x) &&
           ((p->data.y < ePoint.y && p->next->data.y > ePoint.y ) || (p->data.y > ePoint.y &&  p->next->data.y < ePoint.y)))
        {
            ePoint.x = p->data.x;
            endPoint = mainList.insert(p->next, ePoint);
            
            break;
        }
        if(isEqual(p->data.y, ePoint.y) && isEqual(p->next->data.y, ePoint.y) &&
           ((p->data.x < ePoint.x && p->next->data.x > ePoint.x ) || (p->data.x > ePoint.x &&  p->next->data.x < ePoint.x)))
        {
            ePoint.y = p->data.y;
            endPoint = mainList.insert(p->next, ePoint);
            break;
        }
        
        p = p->next;
        
    }while(p != mainList.begin());
    
}

std::vector<cocos2d::Vec2> MainPolygon::getPath(const std::vector<cocos2d::Vec2>& newPoints, std::vector<cocos2d::Vec2> &List, cocos2d::Vec2 &direction)
{
    cocos2d::Vec2 newPoints_begin = cocos2d::Vec2::ZERO;
    cocos2d::Vec2 newPoints_end = cocos2d::Vec2::ZERO;
    if(!newPoints.empty())
    {
        newPoints_begin = *newPoints.begin();
        newPoints_end = *(newPoints.end() - 1);
    }
    
    if(beginPoint == nullptr || endPoint == nullptr)
    {
        throw BeginEndException{};
    }
    
    
    std::vector<cocos2d::Vec2> shape_plus;
    std::vector<cocos2d::Vec2> shape_minus;
    // 1.creating shapes
    
    mainList.Array(beginPoint, endPoint, shape_plus);
    mainList.Array(endPoint, beginPoint, shape_minus);
    
    
    
    std::vector<cocos2d::Vec2> newPoints_reversed(newPoints.size());
    
    if(!newPoints.empty())
    {
        auto j = newPoints_reversed.begin();
        for(auto i = newPoints.end() - 1 ;;i--)
        {
            (*j) = (*i);
            j++;
            if(i == newPoints.begin())
                break;
        }
        
        j = newPoints_reversed.begin();
    }
    
    shape_plus.insert(shape_plus.end(), newPoints_reversed.begin(), newPoints_reversed.end());
    shape_minus.insert(shape_minus.end(), newPoints.begin(), newPoints.end());
    
    
    //////////////////////////
    
    
    // 2. comparing squares
    
    
    float square_plus = getSquare(shape_plus);
    float square_minus = getSquare(shape_minus);
    
    
    
    
    std::vector<cocos2d::Vec2> newPolygon;
    
    bool clockwise; // true - plus, false - minus
    
    if(square_plus > square_minus)
    {
        clockwise = false;
        newPolygon.insert(newPolygon.end(), shape_minus.begin(), shape_minus.end());
    }
    else
    {
        clockwise = true;
        newPolygon.insert(newPolygon.end(), shape_plus.begin(), shape_plus.end());
    }
    
    
    if(!clockwise)
    {
        normalEnd.rotate(cocos2d::Vec2::ZERO, _PI/2.0);
        normalBegin.rotate(cocos2d::Vec2::ZERO, _PI/2.0);
    }
    else
    {
        normalEnd.rotate(cocos2d::Vec2::ZERO, -_PI/2.0);
        normalBegin.rotate(cocos2d::Vec2::ZERO, -_PI/2.0);
    }
    
    /*if(!newPoints.empty())
    {
        for(auto &x : newPolygon)
        {
            
            if(x == beginPoint->data)
            {
                x += normalBegin * margin;
            }
            if(x == endPoint->data)
            {
                 x+= normalEnd * margin;
            }
            if(newPoints_begin != newPoints_end)
            {
                
                if(x == newPoints_begin)
                {
                    x += normalBegin * margin;
                }
                if(x == newPoints_end)
                {
                    x += normalEnd * margin;
                }
            }
            else
            {
                if(x == newPoints_begin)
                {
                    x += normalBegin * margin;
                    x += normalEnd * margin;
                }
            }
        }
    }
    else
    {
        for(auto &x : newPolygon)
        {
            if(x == beginPoint->data)
            {
                x -= normalBegin * margin;
            }
            if(x == endPoint->data)
            {
                x+= normalEnd * margin;
            }
        }
    }*/
    
    //////////////////////////
    
    
    
    // 3. updating main polygon
    
    
    if(clockwise)
    {
        if(beginPoint->next != endPoint)
            mainList.erase(beginPoint->next, endPoint->prev);
        if(!newPoints.empty())
            mainList.insert(endPoint, newPoints.begin(), newPoints.end());
    }
    else
    {
        if(endPoint->next != beginPoint)
            mainList.erase(endPoint->next, beginPoint->prev);
        if(!newPoints.empty())
            mainList.insert(beginPoint, newPoints_reversed.begin(), newPoints_reversed.end());
    }
    
    /*if(!newPoints.empty())
    {
        
        auto p = mainList.begin();
        do{
            
            if(p->data == beginPoint->data)
            {
                p->data += normalBegin * margin;
            }
            if(p->data == endPoint->data)
            {
                p->data += normalEnd * margin;
            }
            if(newPoints_begin != newPoints_end)
            {
                if(p->data == newPoints_begin)
                {
                    p->data += normalBegin * margin;
                }
                if(p->data == newPoints_end)
                {
                    p->data += normalEnd * margin;
                }
            }
            else
            {
                p->data += normalBegin * margin;
                p->data += normalEnd * margin;
            }
            p = p->next;
        }while(p != mainList.begin());
    }
    else
    {
        auto p = mainList.begin();
        do{
            if(p->data == beginPoint->data)
            {
                p->data -= normalBegin * margin;
            }
            if(p->data == endPoint->data)
            {
                p->data += normalEnd * margin;
            }
            p = p->next;
        }while(p != mainList.begin());
    }*/
    
    std::cout<<"BeforeMakingStraight: ";
    
    std::cout<<"\nPoints: ";
    
    auto ptr = mainList.begin();
    do{
        std::cout<<"("<<ptr->data.x<<", "<<ptr->data.y<<") ";
        ptr = ptr->next;
    }while(ptr != mainList.begin());
    
    std::cout<<std::endl;
    
    mainList.make_straight();
    
    
    beginPoint = nullptr;
    endPoint = nullptr;
    
    

    
    
    
    //////////////////////////
    
    auto p = mainList.begin();
    do
    {
        List.push_back(p->data);
        p = p->next;
    }while(p != mainList.begin());
    List.push_back(p->data);
    
    direction = normalEnd * margin;
    
    
    return newPolygon;
    
}




void MainPolygon::printPoints()
{
    std::cout<<"\nPoints: ";
    
    auto p = mainList.begin();
    do{
        std::cout<<"("<<p->data.x<<", "<<p->data.y<<") ";
        p = p->next;
    }while(p != mainList.begin());
    
    std::cout<<std::endl;
}




