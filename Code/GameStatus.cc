#include <esat/window.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <esat/input.h>
#include <esat/draw.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "./GameStatus.h"

namespace GameStatus{
    GameStatus game_status;

    void Update(){
        //Level switch
        if(esat::IsSpecialKeyDown(esat::kSpecialKey_F1)){
            game_status.level = BILLBOX;
        }
        if(esat::IsSpecialKeyDown(esat::kSpecialKey_F2)){
            game_status.level = WORLD;
        }
        if(esat::IsSpecialKeyDown(esat::kSpecialKey_F3)){
            game_status.level = BATTLE;

        }


    }

}