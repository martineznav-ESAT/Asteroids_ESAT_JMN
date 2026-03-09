#include <esat/window.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <esat/input.h>
#include <esat/draw.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "./Libs/CustomLibs/TList.h"
#include "./Libs/CustomLibs/Utils.h"

#include "./Code/GameStatus.h"
#include "./Code/BillBox.h"
#include "./Code/Pokemon.h"

TList::TList lista;

void EmptyMemory(){
    Pokemon::EmptyMemory();
    BillBox::EmptyMemory();
}

void CloseFiles(){
    Pokemon::CloseFiles();
}


void InitGame(){
    Pokemon::Init();
    BillBox::Init();
}

void UpdateGame(){
    GameStatus::Update();
    switch(GameStatus::game_status.level){
        case GameStatus::Level::BILLBOX :
            BillBox::Update();
        break;
        case GameStatus::Level::WORLD :

        break;
        case GameStatus::Level::BATTLE :

        break;
    }
}

void DrawGame(){
    esat::DrawClear(0,0,0);
    switch(GameStatus::game_status.level){
        case GameStatus::Level::BILLBOX :
            BillBox::Draw();
        break;
        case GameStatus::Level::WORLD :
            esat::DrawClear(0,200,0);
        break;
        case GameStatus::Level::BATTLE :
            esat::DrawClear(100,0,0);
        break;
    }
}

int esat::main(int argc, char **argv) {
    Utils::GenerateRandomSeed();

	esat::WindowInit(Utils::kWindowWidth, Utils::kWindowHeight);
	WindowSetMouseVisibility(true);

    esat::DrawSetTextFont("./Assets/Fonts/pokemon_classic.ttf");

    InitGame();

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {        
        Utils::last_time = esat::Time();

        esat::DrawBegin();
        esat::DrawClear(0,0,0);
        
        UpdateGame();
        DrawGame();

        esat::DrawEnd();  	
        esat::WindowFrame();

        Utils::ControlFps();
    }
    EmptyMemory();
    CloseFiles();

    esat::WindowDestroy();

    return 0;  
}