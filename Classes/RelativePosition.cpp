//
//  RelativePosition.cpp
//  TuturialProject
//
//  Created by Кирилл Алексеенко on 18.08.15.
//
//

#include "RelativePosition.h"

cocos2d::Size designFrameSize(4000, 3000);

Vec2 RelativePosition::getPosition(Vec2 designPosition, Size frameSize)
{
    if(designPosition.x > designFrameSize.width || designPosition.y > designFrameSize.height)
    {
        MessageBox("Error", "Some elements are out of designSize");
    }
    float d, border;
    if(designFrameSize.width/designFrameSize.height > frameSize.width/frameSize.height)
    {
        d = designFrameSize.width/frameSize.width;
        border = (frameSize.height - designFrameSize.height/d)/2;
        return Vec2(designPosition.x/d, designPosition.y/d + border/2);
    }
    else
    {
        d  = designFrameSize.height/frameSize.height;
        border = (frameSize.width - designFrameSize.width/d)/2;
        return Vec2(designPosition.x/d + border, designPosition.y/d);
    }

}
Size RelativePosition::getSize(Size designSize, Size frameSize)
{
    float d;
    if(designFrameSize.width/designFrameSize.height > frameSize.width/frameSize.height)
    {
        d = designFrameSize.width/frameSize.width;
        return Size(designSize.width/d, designSize.height/d);
    }
    else
    {
        d  = designFrameSize.height/frameSize.height;
        return Size(designSize.width/d, designSize.height/d);
    }
}
Vec2 RelativePosition::getSize(Vec2 designSize, Size frameSize)
{
    float d;
    if(designFrameSize.width/designFrameSize.height > frameSize.width/frameSize.height)
    {
        d = designFrameSize.width/frameSize.width;
        return Vec2(designSize.x/d, designSize.y/d);
    }
    else
    {
        d  = designFrameSize.height/frameSize.height;
        return Vec2(designSize.x/d, designSize.y/d);
    }
}

