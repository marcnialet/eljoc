//
//  Utils.h
//  eljoc
//
//  Created by marc on 23/08/14.
//
//

#ifndef __eljoc__Defines__
#define __eljoc__Defines__

#define kFontName "Marker Felt.ttf"

enum GestureType
{
    None = 0,
    Swipe_Left = 1,
    Swipe_Right = 2,
    Swipe_Up = 3,
    Swipe_Down = 4,
    
    Swipe_Left_Multi = 5,
    Swipe_Right_Multi = 6,
    Swipe_Up_Multi = 7,
    Swipe_Down_Multi = 8
};

enum GameMode
{
    NotLoaded = 0,
    LoadingLevel = 1,
    LevelLoaded = 2,
    Running = 3,
    GameOver = 4,
    LevelDone = 5,
    
    Paused = 6,
};

#endif /* defined(__eljoc__Defines__) */