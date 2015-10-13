//
//  TransactionHandler.hpp
//  TuturialProject
//
//  Created by Кирилл Алексеенко on 09.10.15.
//
//

#ifndef TransactionHandler_hpp
#define TransactionHandler_hpp

#include <stdio.h>
#include "cocos2d.h"

class TransactionHandler
{
public:
    static void popScene();
    static void reloadGameScene();
    static void loadLevel(int level);
};

#endif /* TransactionHandler_hpp */
