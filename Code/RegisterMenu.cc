#include <esat/window.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <esat/input.h>
#include <esat/draw.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "../Libs/CustomLibs/Utils.h"
#include "../Libs/CustomLibs/UILib.h"

#include "./GameStatus.h"
#include "./LoginMenu.h"
#include "./RegisterMenu.h"

namespace RegisterMenu{
    //Memory block that holds all the buttons no matter if they are visible or not.
    UILib::UI_Item *menu_items = nullptr;
    GameStatus::Level prev_level;
    int selected_item = -1;


    //ACTIONS
    void SaveAction(){
        printf("SAVE ACTION WIP\n");
    }

    void BackAction(){
        if(prev_level == GameStatus::Level::ADMIN_MENU){
            //TO_DO
        }else{
            LoginMenu::Load(GameStatus::Level::REGISTER_MENU);
        }
    }

    //LOGIN MENU INIT

    //Initializes all menu buttons
    void InitButtons(){
        JMATH::Vec2 centered_bottom_coords = {Utils::kWindowWidth*0.5f, Utils::kWindowHeight-50.0f};
        Utils::Collider left_button = 
        {
            {centered_bottom_coords.x-150-50, centered_bottom_coords.y-50},
            {centered_bottom_coords.x-50, centered_bottom_coords.y},
        };
        Utils::Collider right_button = 
        {
            {centered_bottom_coords.x+50, centered_bottom_coords.y-50},
            {centered_bottom_coords.x+50+150, centered_bottom_coords.y},
        };

        Utils::Color button_color = {100,100,100,200};
        Utils::Color text_color = {255,255,255,255};

        UILib::InitButton(
            &((menu_items+((int)RegisterItems::SAVE_BTN))->item.btn_item),
            left_button,
            button_color,
            button_color,
            {
                text_color,
                "SAVE",
                (float)Utils::kBaseFontSize
            },
            true,
            SaveAction
        );

        UILib::InitButton(
            &((menu_items+((int)RegisterItems::BACK_BTN))->item.btn_item),
            right_button,
            button_color,
            button_color,
            {
                text_color,
                "BACK",
                (float)Utils::kBaseFontSize
            },
            true,
            BackAction
        );
    }

    //Initializes all menu text Inputs
    void InitTextInputs(){
        Utils::Collider first_right_side = {{(Utils::kWindowWidth*0.5f)+40, 30}, {(Utils::kWindowWidth*0.5f)+40 + (Utils::kBaseFontSize*14), 60}};
        JMATH::Vec2 margin_y = {0.0f, 50.0f};
        UILib::InitTextInput(
            &((menu_items + ((int)RegisterItems::USERNAME_TI))->item.text_item),
            first_right_side,
            {255,255,255,255},
            {0,0,0,255},
            {{255,255,255,255},nullptr, (float)Utils::kBaseFontSize},
            true
        );

        UILib::InitTextInput(
            &((menu_items + ((int)RegisterItems::PASSWORD_TI))->item.text_item),
            {JMATH::Vec2Sum(first_right_side.P1, margin_y),JMATH::Vec2Sum(first_right_side.P2, margin_y)},
            {255,255,255,255},
            {0,0,0,255},
            {{255,255,255,255},nullptr, (float)Utils::kBaseFontSize},
            true
        );

        UILib::InitTextInput(
            &((menu_items + ((int)RegisterItems::ALIAS_TI))->item.text_item),
            {JMATH::Vec2Sum(first_right_side.P1, JMATH::Vec2Scale(margin_y,2)),JMATH::Vec2Sum(first_right_side.P2, JMATH::Vec2Scale(margin_y,2))},
            {255,255,255,255},
            {0,0,0,255},
            {{255,255,255,255},nullptr, (float)Utils::kBaseFontSize},
            true
        );

        UILib::InitTextInput(
            &((menu_items + ((int)RegisterItems::EMAIL_TI))->item.text_item),
            {JMATH::Vec2Sum(first_right_side.P1, JMATH::Vec2Scale(margin_y,3)),JMATH::Vec2Sum(first_right_side.P2, JMATH::Vec2Scale(margin_y,3))},
            {255,255,255,255},
            {0,0,0,255},
            {{255,255,255,255},nullptr, (float)Utils::kBaseFontSize},
            true
        );

        UILib::InitTextInput(
            &((menu_items + ((int)RegisterItems::NAME_TI))->item.text_item),
            {JMATH::Vec2Sum(first_right_side.P1, JMATH::Vec2Scale(margin_y,4)),JMATH::Vec2Sum(first_right_side.P2, JMATH::Vec2Scale(margin_y,4))},
            {255,255,255,255},
            {0,0,0,255},
            {{255,255,255,255},nullptr, (float)Utils::kBaseFontSize},
            true
        );

        UILib::InitTextInput(
            &((menu_items + ((int)RegisterItems::SURNAME_TI))->item.text_item),
            {JMATH::Vec2Sum(first_right_side.P1, JMATH::Vec2Scale(margin_y,5)),JMATH::Vec2Sum(first_right_side.P2, JMATH::Vec2Scale(margin_y,5))},
            {255,255,255,255},
            {0,0,0,255},
            {{255,255,255,255},nullptr, (float)Utils::kBaseFontSize},
            true
        );
    }

    //Initializes all UI items
    void InitMenuItems(){

        // text_inputs = (UILib::TextInput*) malloc(sizeof(UILib::TextInput)*(int)RegisterItems::TOTAL_ITEMS);
        menu_items = (UILib::UI_Item*) malloc(sizeof(UILib::UI_Item)*(int)RegisterItems::TOTAL_ITEMS);

        UILib::InitItem(
            (menu_items + ((int)RegisterItems::USERNAME_TI)),
            UILib::ItemType::TEXT_INPUT,
            {{255,255,255,255},"USERNAME", Utils::kBaseFontSize*1.5f}
        );
        UILib::InitItem(
            (menu_items + ((int)RegisterItems::PASSWORD_TI)),
            UILib::ItemType::TEXT_INPUT,
            {{255,255,255,255},"PASSWORD", Utils::kBaseFontSize*1.5f}
        );

        UILib::InitItem(
            (menu_items + ((int)RegisterItems::ALIAS_TI)),
            UILib::ItemType::TEXT_INPUT,
            {{255,255,255,255},"ALIAS", Utils::kBaseFontSize*1.5f}
        );

        UILib::InitItem(
            (menu_items + ((int)RegisterItems::EMAIL_TI)),
            UILib::ItemType::TEXT_INPUT,
            {{255,255,255,255},"E-MAIL", Utils::kBaseFontSize*1.5f}
        );
        UILib::InitItem(
            (menu_items + ((int)RegisterItems::NAME_TI)),
            UILib::ItemType::TEXT_INPUT,
            {{255,255,255,255},"NAME", Utils::kBaseFontSize*1.5f}
        );

        UILib::InitItem(
            (menu_items + ((int)RegisterItems::SURNAME_TI)),
            UILib::ItemType::TEXT_INPUT,
            {{255,255,255,255},"SURNAME", Utils::kBaseFontSize*1.5f}
        );


        UILib::InitItem(
            (menu_items + ((int)RegisterItems::SAVE_BTN)),
            UILib::ItemType::BUTTON,
            {{255,255,255,255},"SAVE", Utils::kBaseFontSize*1.5f}
        );
        UILib::InitItem(
            (menu_items + ((int)RegisterItems::BACK_BTN)),
            UILib::ItemType::BUTTON,
            {{255,255,255,255},"BACK", Utils::kBaseFontSize*1.5f}
        );
    }

    //Whole Login Menu initializer
    void Init(){
        InitMenuItems();
        InitTextInputs();
        InitButtons();
    }

    //LOGIN MENU LOAD

    //Based on the level/screen you come from, the Login Menu will be loaded differently
    void Load(GameStatus::Level level_p){
        prev_level = level_p;
        GameStatus::game_status.level = GameStatus::Level::REGISTER_MENU;
    }

    //LOGIN MENU UPDATE

    //Whole Login Menu update method
    void Update(){

        //Unselect Menu item on click
        //Since its the first click event registered, there's no need to check for collision
        //If later on a collision with the same input its located, the selected_item will be 
        //overriden to the proper value
        if(esat::MouseButtonDown(0)){
            selected_item = -1;
        }

        //Menu Key controls
        if(esat::IsSpecialKeyDown(esat::kSpecialKey_Up)){
            if(selected_item <= 0){
                selected_item = ((int)RegisterItems::TOTAL_ITEMS) - 1;
            }else{
                selected_item--;
            }
        }
        if(esat::IsSpecialKeyDown(esat::kSpecialKey_Down) || esat::IsSpecialKeyDown(esat::kSpecialKey_Tab)){
            ++selected_item %= (int)RegisterItems::TOTAL_ITEMS;
        }
        
        for(int i = 0; i < (int)RegisterItems::TOTAL_ITEMS; i++){
            UILib::UpdateItem(menu_items+i, &selected_item, i);
        }
    }

    //LOGIN MENU DRAW

    void DrawMenuItems(){
        for(int i = 0; i < (int)RegisterItems::TOTAL_ITEMS; i++){
            UILib::DrawItem(*(menu_items+i));
        }
    }

    //Whole Login Menu draw method
    void Draw(){
        DrawMenuItems();
    }

    void EmptyMemory(){
        for(int i = 0; i < (int)RegisterItems::TOTAL_ITEMS; i++){
            UILib::EmptyItemMemory(menu_items+i);
        }
        free(menu_items);
    }
}