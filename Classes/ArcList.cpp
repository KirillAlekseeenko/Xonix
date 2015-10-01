//
//  ArcList.cpp
//  TuturialProject
//
//  Created by Кирилл Алексеенко on 15.09.15.
//
//

#include "ArcList.h"


CircularList::~CircularList()
{
    Unit *p = this->_end;
    Unit *p_;
    this->_begin->prev = nullptr;
    while(p != nullptr)
    {
        p_ = p;
        p = p->prev;
        delete p_;
    }
}

void CircularList::push_back(const cocos2d::Vec2 &data)
{
    
    Unit *unit = new Unit(data);
    
    if(this->_begin == nullptr)
    {
        this->_begin = unit;
        this->_end = unit;
        unit->next = unit;
        unit->prev = unit;
        unit = nullptr;
        return;
    }
    
    
    unit->prev = this->_end;
    unit->next = this->_begin;
    this->_end->next = unit;
    this->_begin->prev = unit;
    this->_end = unit;
    unit = nullptr;
}

void CircularList::print(Unit *begin, Unit *end)
{
    Unit *p = begin;
    
    std::cout<<"CircularList: ";
    
    
    do
    {
        std::cout<<"("<<p->data.x<<", "<<p->data.y<<") ";
        p = p->next;
    }while(p != end->next);
    
    
    std::cout<<std::endl;
    p = nullptr;
}

Unit* CircularList::insert(Unit *position, const cocos2d::Vec2 &data)
{
    Unit *unit = new Unit(data);
    position->prev->next = unit;
    unit->next = position;
    unit->prev = position->prev;
    position->prev = unit;
    _end = _begin->prev;
    return unit;
}

void CircularList::erase(Unit *position)
{
    auto next = position->next;
    auto prev = position->prev;
    if(position == _begin)
    {
        _begin = next;
    }
    if(position == _end)
    {
        _end = prev;
    }
    next->prev = prev;
    prev->next = next;
    delete position;
}

void CircularList::Array(Unit *begin, Unit *end, std::vector<cocos2d::Vec2> &vec)
{
    Unit *p = begin;
    
    do
    {
        vec.push_back(p->data);
        p = p->next;
    }while(p != end->next);
    
    p = nullptr;
}

Unit * CircularList::insert(Unit *position, const std::vector<cocos2d::Vec2>::const_iterator &begin, const std::vector<cocos2d::Vec2>::const_iterator &end)
{
    auto p = position;
    for(auto i = end - 1;i!=begin;i--)
    {
        p = this->insert(p, *i);
    }
    p = this->insert(p, *begin);
    _end = _begin->prev;
    return p;
}

void CircularList::erase(Unit *begin, Unit *end)// true - next, false - prev
{
    auto prev = begin->prev;
    auto next = end->next;
    
    prev->next = next;
    next->prev = prev;
    
    end->next = nullptr;
    
    auto p = begin;
    Unit *p_;
    while(p != nullptr)
    {
        p_ = p;
        p = p->next;
        delete p_;
    }
    _begin = next;
    _end = prev;
}

Unit* CircularList::find(const cocos2d::Vec2& data)
{
    auto p = _begin;
    do
    {
        if(p->data == data)
            return p;
        p = p->next;
    }while(p!=_begin);
    return nullptr;
}

