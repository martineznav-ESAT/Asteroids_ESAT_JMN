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

#include "./GameManager.h"
#include "./AdminMenu.h"
#include "./MainMenu.h"
#include "./RegisterMenu.h"

namespace AdminMenu{
    //Memory block that holds all the menu items no matter if they are visible or not.
    UILib::UI_Item *menu_items = nullptr;
    int selected_item = -1;
    int user_page = 0;

    UserManager::User *page_users = nullptr;

    //ACTIONS
    void CreateAction(){
        RegisterMenu::Load(GameManager::Level::ADMIN_MENU);
    }

    void EditAction(UserManager::User *u){
        printf("EDIT ACTION %s WIP",u->name);
    }

    void DeleteAction(UserManager::User *u){
        printf("DELETE ACTION %s WIP",u->name);
    }
    
    void BackAction(){
        MainMenu::Load();
    }

    //ADMIN MENU INIT

    //Initializes all menu buttons
    void InitButtons(){
        Utils::Color text_color = {255,255,255,255};

        UILib::InitButton(
            &((menu_items+((int)AdminMenuItems::CREATE_BTN))->item.btn_item),
            {
                {30.0f, Utils::kWindowHeight-80.0f},
                {100.0f, Utils::kWindowHeight-30.0f}
            },
            {100,100,100,200},
            {100,100,100,200},
            {
                text_color,
                (menu_items+((int)AdminMenuItems::CREATE_BTN))->item_name.text,
                (float)Utils::kBaseFontSize
            },
            true,
            CreateAction
        );

        UILib::InitButton(
            &((menu_items+((int)AdminMenuItems::BACK_BTN))->item.btn_item),
            {
                {Utils::kWindowWidth-100.0f, Utils::kWindowHeight-80.0f},
                {Utils::kWindowWidth-30.0f, Utils::kWindowHeight-30.0f}
            },
            {100,100,100,200},
            {100,100,100,200},
            {
                text_color,
                (menu_items+((int)AdminMenuItems::BACK_BTN))->item_name.text,
                (float)Utils::kBaseFontSize
            },
            true,
            BackAction
        );
        
    }


    //Initializes all UI items
    void InitMenuItems(){

        // text_inputs = (UILib::TextInput*) malloc(sizeof(UILib::TextInput)*(int)AdminMenuItems::TOTAL_ITEMS);
        menu_items = (UILib::UI_Item*) malloc(sizeof(UILib::UI_Item)*(int)AdminMenuItems::TOTAL_ITEMS);

        UILib::InitItem(
            (menu_items + ((int)AdminMenuItems::CREATE_BTN)),
            UILib::ItemType::BUTTON,
            {{255,255,255,255},"CREATE", Utils::kBaseFontSize*2.0f}
        );

        UILib::InitItem(
            (menu_items + ((int)AdminMenuItems::BACK_BTN)),
            UILib::ItemType::BUTTON,
            {{255,255,255,255},"BACK", Utils::kBaseFontSize*2.0f}
        );
    }

    void LoadUserPage(int page = 0){
        //TO_DO LOAD REAL USERS

        for(int i = 0; i < 10; i++){

        }
    }

    void InitUserPage(){
        page_users = (UserManager::User*) malloc(sizeof(UserManager::User)*10);
        LoadUserPage();
    }

    //Whole Admin Menu initializer
    void Init(){
        InitUserPage();
        InitMenuItems();
        InitButtons();
    }

    //ADMIN MENU LOAD

    //Loads the Admin menu
    void Load(){
        GameManager::game_status.level = GameManager::Level::ADMIN_MENU;
    }

    //ADMIN MENU UPDATE

    //Whole Admin Menu update method
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
                selected_item = ((int)AdminMenuItems::TOTAL_ITEMS) - 1;
            }else{
                selected_item--;
            }
        }
        if(esat::IsSpecialKeyDown(esat::kSpecialKey_Down) || esat::IsSpecialKeyDown(esat::kSpecialKey_Tab)){
            ++selected_item %= (int)AdminMenuItems::TOTAL_ITEMS;
        }
        
        for(int i = 0; i < (int)AdminMenuItems::TOTAL_ITEMS; i++){
            UILib::UpdateItem(menu_items+i, &selected_item, i);
        }
    }

    //ADMIN MENU DRAW
    void DrawTitle(){
        UILib::Text title = {
            {255,255,255,255},
            "REGISTERED USERS",
            Utils::kBaseFontSize*2.0f
        };
        
        esat::DrawSetTextFont("./Assets/Fonts/Neuropol.otf");
        UILib::DrawText(
            (Utils::kWindowWidth*0.5f) - ((strlen(title.text)/2.5f)*title.font_size),
            50, 
            title
        );
        esat::DrawSetTextFont("./Assets/Fonts/Hyperspace.ttf");
    }

    void DrawUserItem(JMATH::Vec2 coord){
        UILib::DrawText(
            coord, 
            {
                {255,255,255,255},
                "USERNAME",
                {(float)Utils::kBaseFontSize}
            }
        );
        UILib::DrawText(
            JMATH::Vec2Sum(coord, {(float)Utils::kBaseFontSize*strlen("USERNAME "),0}), 
            {
                {255,255,255,255},
                "AAAAAZZZZZ",
                {(float)Utils::kBaseFontSize}
            }
        );
    }

    void DrawUserList(){
        JMATH::Vec2 base_coord = {
            (Utils::kWindowWidth*0.5f) - 
            (strlen("USERNAME AAAAAZZZZZ        EDIT DELETE") * 0.45f * ((float)Utils::kBaseFontSize)),
            100
        };
        JMATH::Vec2 margin_v = {0,45};

        for(int i = 0; i < 10; i++){
            DrawUserItem(JMATH::Vec2Sum(base_coord,JMATH::Vec2Scale(margin_v,i)));
        }
    }

    void DrawMenuItems(){
        for(int i = 0; i < (int)AdminMenuItems::TOTAL_ITEMS; i++){
            UILib::DrawItem(*(menu_items+i+user_page));
        }
    }

    //Whole Admin Menu draw method
    void Draw(){
        DrawTitle();
        DrawUserList();
        DrawMenuItems();
    }

    void EmptyMemory(){
        for(int i = 0; i < (int)AdminMenuItems::TOTAL_ITEMS; i++){
            UILib::EmptyItemMemory(menu_items+i);
        }
        free(menu_items);
    }
}