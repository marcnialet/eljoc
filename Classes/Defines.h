//
//  Utils.h
//  eljoc
//
//  Created by marc on 23/08/14.
//
//

#ifndef __eljoc__Defines__
#define __eljoc__Defines__

#define LAYER_TAG_GAMEPLAY      1
#define LAYER_TAG_GAMEOVER      2
#define LAYER_TAG_GAMEHUD       3
#define LAYER_TAG_GAMEENDLEVEL  4
#define LAYER_TAG_GAMESETTINGS  5

#define LAYER_Z_GAMEHUD       1
#define LAYER_Z_GAMESETTINGS  1000
#define LAYER_Z_GAMEPLAY      100
#define LAYER_Z_GAMEOVER      200
#define LAYER_Z_GAMEENDLEVEL  200

#define kFontName "fonts/Marker Felt.ttf"

#define COLOR_WHITE Color4B(255, 255, 255, 255)
#define COLOR_RED   Color4B(255, 0, 0, 255)

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
    Swipe_Down_Multi = 8,
    
    Single_Click = 9
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