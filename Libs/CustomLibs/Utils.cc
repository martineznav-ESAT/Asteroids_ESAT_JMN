#include <esat/window.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <esat/input.h>
#include <esat/draw.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "./Utils.h"

namespace Utils{
    const unsigned char kFPS = 60;
    const int kWindowWidth = 800, kWindowHeight = 608;
    const int kBaseFontSize = 19;

    double current_time,last_time;

    // Genera nueva semilla en base al 
    // ms del reloj del sistema
    void GenerateRandomSeed(){
        srand(time(NULL)); 
    }
    //Genera un número del 0 al límite indicado
    int GenerateRandomNumber(int limite){
        return (rand()%limite);
    }

    int GetPointerIndex(int row, int col_t, int col){
        return ((row*col_t)+col);
    }

    int GetPointerRowFromIndex(int i, int col_t){
        return (i/col_t);
    }

    int GetPointerColFromIndex(int i, int col_t){
        return (i%col_t);
    }

    void ControlFps(){
        do{
            current_time = esat::Time();
        }while((current_time-last_time)<=1000.0/kFPS);
    }

    //Detects if the mouse is inside the collider area
    bool MouseInCollider(Collider c){
        return (
            c.P1.x < esat::MousePositionX() &&
            c.P1.y < esat::MousePositionY() &&
            c.P2.x > esat::MousePositionX() &&
            c.P2.y > esat::MousePositionY()
        );
    }

    void DrawCollider(Collider c, Color border_color, Color fill_color){
        //Generates draw coords and draws de button collider with the button values
        JMATH::Vec2 *draw_coords = (JMATH::Vec2*) malloc(sizeof(JMATH::Vec2) * 5);

        *(draw_coords+0) = c.P1;
        *(draw_coords+1) = {c.P1.x, c.P2.y};
        *(draw_coords+2) = c.P2;
        *(draw_coords+3) = {c.P2.x, c.P1.y};
        *(draw_coords+4) = c.P1;

        esat::DrawSetStrokeColor(border_color.r, border_color.g, border_color.b, border_color.a);
        esat::DrawSetFillColor(fill_color.r, fill_color.g, fill_color.b, fill_color.a);
        esat::DrawSolidPath(&(draw_coords->x), 5);

        free(draw_coords);
    }
}