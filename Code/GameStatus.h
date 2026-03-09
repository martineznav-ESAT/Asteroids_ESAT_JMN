#include <esat/window.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <esat/input.h>
#include <esat/draw.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifndef GameStatus_H
#define GameStatus_H

namespace GameStatus{

    enum Level{
        BILLBOX,
        WORLD,
        BATTLE
    };

    struct GameStatus{
        Level level = BILLBOX;
        int last_pkm_id = -1;
    };

    extern GameStatus game_status;

    void Update();
}

#endif