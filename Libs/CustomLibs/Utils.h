#include <esat/window.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <esat/input.h>
#include <esat/draw.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "./JMATH.h"

#ifndef Utils_H
#define Utils_H

namespace Utils{
    struct Color{
        float r, g, b, a ;
    };

    struct Collider{
        JMATH::Vec2 P1 = {0,0};
        JMATH::Vec2 P2 = {10,10};
    };

    extern const unsigned char kFPS;
    extern const int kWindowWidth, kWindowHeight;
    extern const int kBaseFontSize;

    extern double current_time,last_time;

    //Generates a new random number seed based
    //on clock system ms 
    void GenerateRandomSeed();

    //Generates a random number between 0 and limit
    int GenerateRandomNumber(int limit);

    int GetPointerIndex(int row, int col_t, int col);

    int GetPointerRowFromIndex(int i, int col_t);

    int GetPointerColFromIndex(int i, int col_t);

    void ControlFps();

    //Detects if the mouse is inside the collider area
    bool MouseInCollider(Collider c);

    void DrawIntText(float x, float y, int value);

    void DrawCollider(Collider c, Color border_color, Color fill_color);
}

#endif

