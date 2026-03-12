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

    void DrawIntText(float x, float y, int value){
        char* text = (char*) malloc(sizeof(char)*3);
        text = itoa(value,text,10);
        esat::DrawText(x, y, text);
        free(text);
    }
}