//
//  RelativePosition.h
//  TuturialProject
//
//  Created by Кирилл Алексеенко on 18.08.15.
//
//

#ifndef __TuturialProject__RelativePosition__
#define __TuturialProject__RelativePosition__

#include "cocos2d.h"
using namespace cocos2d;



class RelativePosition
{
public:
    static Vec2 getPosition(Vec2 designPosition, Size frameSize);
    static Size getSize(Size designSize, Size frameSize);
    static Vec2 getSize(Vec2 designSize, Size frameSize);
};


#endif /* defined(__TuturialProject__RelativePosition__) */
