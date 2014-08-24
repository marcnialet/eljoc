//
//  Utils.h
//  eljoc
//
//  Created by marc on 23/08/14.
//
//

#ifndef __eljoc__Utils__
#define __eljoc__Utils__

#include <iostream>

#include "cocos2d.h"
#include "Piece.h"
#include "GameBoard.h"

using namespace std;
class Utils
{
public:
    static double getTimeTick();
    static int myrandom (int i);
};
#endif /* defined(__eljoc__Utils__) */
