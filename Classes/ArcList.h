//
//  ArcList.h
//  TuturialProject
//
//  Created by Кирилл Алексеенко on 15.09.15.
//
//

#ifndef __TuturialProject__ArcList__
#define __TuturialProject__ArcList__

#include <stdio.h>
#include <iostream>
#include <vector>





struct Unit{
    Unit *next;
    Unit *prev;
    cocos2d::Vec2 data;
    Unit(const cocos2d::Vec2 &data){this->data = data; next = nullptr; prev = nullptr;}
};


class CircularList
{
    Unit* _begin;
    Unit* _end;
public:
    CircularList(){_begin = nullptr; _end = nullptr;}
    ~CircularList();
    void push_back(const cocos2d::Vec2 &data);
    Unit* find(const cocos2d::Vec2 &data);
    Unit* insert(Unit *position, const std::vector<cocos2d::Vec2>::const_iterator &begin, const std::vector<cocos2d::Vec2>::const_iterator &end);
    Unit* insert(Unit *position, const cocos2d::Vec2& data);
    void erase(Unit *position);
    void erase(Unit *begin, Unit *end);
    void print(Unit *begin, Unit *end);
    void Array(Unit *begin, Unit *end, std::vector<cocos2d::Vec2> &vec);
    Unit *end(){return _end;}
    Unit *begin(){return _begin;}
};

#endif /* defined(__TuturialProject__ArcList__) */
