//
//  ArcList.cpp
//  TuturialProject
//
//  Created by Кирилл Алексеенко on 15.09.15.
//
//

#include "ArcList.h"


bool isEqual(float x, float y)
{
    float preciseness = 4;
    if(std::abs(x - y) < preciseness)
        return true;
    else
        return false;
}
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

void CircularList::make_straight()
{
    auto ptr = _begin;
    do
    {
        auto ptr_next = ptr->next;
        auto ptr_prev = ptr->prev;
        if(isEqual(ptr_prev->data.x, ptr->data.x) && isEqual(ptr_next->data.x, ptr->data.x))
        {
            this->erase(ptr);
        }
        if(isEqual(ptr_prev->data.y, ptr->data.y) && isEqual(ptr_next->data.y, ptr->data.y))
        {
            this->erase(ptr);
        }
        ptr = ptr_next;
    }while(ptr != _begin);
    
    ptr = _begin;
    
    do
    {
        auto ptr_next = ptr->next;
        auto ptr_prev = ptr->prev;
        if(isEqual(ptr_next->data.x, ptr->data.x))
        {
            ptr->data.x = ptr_next->data.x;
        }
        if(isEqual(ptr_next->data.y, ptr->data.y))
        {
            ptr->data.y = ptr_next->data.y;
        }
        ptr = ptr_next;
    }while(ptr != _begin);
}

