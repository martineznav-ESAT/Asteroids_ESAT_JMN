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
    bool is_last_page = false;

    UserManager::User *page_users = nullptr;

    //ACTIONS
    void EditAction(void *u){
        printf("EDIT ACTION %d WIP\n",((UserManager::User*)u)->credits);
    }

    void DeleteAction(void *u){
        printf("DELETE ACTION %d WIP\n",((UserManager::User*)u)->credits);
    }

    void PrevPageAction(){
        user_page--;
        is_last_page = user_page >= 3;
        printf("PREV_PAGE ACTION %d WIP\n",user_page);
    }

    void NextPageAction(){
        //TO_DO Comprobar si hay mas usuarios
        user_page++;
        is_last_page = user_page >= 3;
        printf("NEXT_PAGE ACTION %d WIP\n",user_page);
    }

    void CreateAction(){
        RegisterMenu::Load(GameManager::Level::ADMIN_MENU);
    }
    
    void BackAction(){
        MainMenu::Load();
    }

    //ADMIN MENU INIT

    //Initializes all menu buttons
    void InitButtons(){
        Utils::Color text_color = {255,255,255,255};

        JMATH::Vec2 base_button_coord = {
            (Utils::kWindowWidth) - (strlen("EDIT DELETE  ") * ((float)Utils::kBaseFontSize)),
            115
        };

        JMATH::Vec2 button_height = {0,25};
        JMATH::Vec2 margin_v = {0,17.5f};
        JMATH::Vec2 edit_width = {(strlen("EDIT")*(float)Utils::kBaseFontSize),0};
        JMATH::Vec2 delete_width_1 = {(strlen("EDIT ")*(float)Utils::kBaseFontSize),0};
        JMATH::Vec2 delete_width_2 = {(strlen("EDIT DELETE")*(float)Utils::kBaseFontSize),0};

        //USER MANAGEMENT BUTTONS
        for(int i = 0, u = 0; i < (int)AdminMenuItems::PREV_PAG_BTN; i++){
            if(i%2 == 0){
                UILib::InitButtonPA(
                    &((menu_items+i)->item.btn_pa_item),
                    {
                        JMATH::Vec2Sum(base_button_coord, JMATH::Vec2Scale(margin_v,i)),
                        JMATH::Vec2Sum(base_button_coord, JMATH::Vec2Sum(button_height,JMATH::Vec2Sum(edit_width, JMATH::Vec2Scale(margin_v,i)))),
                    },
                    {100,100,100,200},
                    {100,100,100,200},
                    {
                        text_color,
                        (menu_items+i)->item_name.text,
                        (float)Utils::kBaseFontSize
                    },
                    true,
                    EditAction,
                    (page_users+u)
                );
            }else{
                UILib::InitButtonPA(
                    &((menu_items+i)->item.btn_pa_item),
                    {
                        JMATH::Vec2Sum(base_button_coord, JMATH::Vec2Sum(delete_width_1, JMATH::Vec2Scale(margin_v,i-1))),
                        JMATH::Vec2Sum(base_button_coord, JMATH::Vec2Sum(button_height,JMATH::Vec2Sum(delete_width_2, JMATH::Vec2Scale(margin_v,i-1)))),
                    },
                    {100,100,100,200},
                    {100,100,100,200},
                    {
                        text_color,
                        (menu_items+i)->item_name.text,
                        (float)Utils::kBaseFontSize
                    },
                    true,
                    DeleteAction,
                    (page_users+u)
                );

                u++;
            }
        }

        UILib::InitButton(
            &((menu_items+((int)AdminMenuItems::PREV_PAG_BTN))->item.btn_item),
            {
                {30.0f, Utils::kWindowHeight-140.0f},
                {80.0f, Utils::kWindowHeight-90.0f}
            },
            {100,100,100,200},
            {100,100,100,200},
            {
                text_color,
                (menu_items+((int)AdminMenuItems::PREV_PAG_BTN))->item_name.text,
                (float)Utils::kBaseFontSize
            },
            true,
            PrevPageAction
        );

        UILib::InitButton(
            &((menu_items+((int)AdminMenuItems::NEXT_PAG_BTN))->item.btn_item),
            {
                {Utils::kWindowWidth-80.0f, Utils::kWindowHeight-140.0f},
                {Utils::kWindowWidth-30.0f, Utils::kWindowHeight-90.0f}
            },
            {100,100,100,200},
            {100,100,100,200},
            {
                text_color,
                (menu_items+((int)AdminMenuItems::NEXT_PAG_BTN))->item_name.text,
                (float)Utils::kBaseFontSize
            },
            true,
            NextPageAction
        );

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

        //USER MANAGEMENT BUTTONS
        for(int i = 0; i < (int)AdminMenuItems::PREV_PAG_BTN; i++){
            if(i%2 == 0){
                UILib::InitItem(
                    (menu_items + i),
                    UILib::ItemType::BUTTON_PA,
                    {{255,255,255,255},"EDIT", (float)Utils::kBaseFontSize}
                );
            }else{
                UILib::InitItem(
                    (menu_items + i),
                    UILib::ItemType::BUTTON_PA,
                    {{255,255,255,255},"DELETE", (float)Utils::kBaseFontSize}
                );
            }
        }

        UILib::InitItem(
            (menu_items + ((int)AdminMenuItems::PREV_PAG_BTN)),
            UILib::ItemType::BUTTON,
            {{255,255,255,255},"<", Utils::kBaseFontSize*2.0f}
        );

        UILib::InitItem(
            (menu_items + ((int)AdminMenuItems::NEXT_PAG_BTN)),
            UILib::ItemType::BUTTON,
            {{255,255,255,255},">", Utils::kBaseFontSize*2.0f}
        );

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

        for(unsigned char i = 0; i < 10; i++){
            *(page_users+i) = {
                "01234567890123456789",
                "password",
                "AAA",
                "EMAIL@MAIL.COM",
                "NAME",
                "SURNAME",
                22,01,2003,
                "SPAIN",
                "VALENCIA",
                i,
                false
            };
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
            do{
                if(selected_item <= 0){
                    selected_item = ((int)AdminMenuItems::TOTAL_ITEMS) - 1;
                }else{
                    selected_item--;
                }
            }while(UILib::IsItemVisible(*(menu_items+selected_item)));
        }
        if(esat::IsSpecialKeyDown(esat::kSpecialKey_Down) || esat::IsSpecialKeyDown(esat::kSpecialKey_Tab)){
            do{
                ++selected_item %= (int)AdminMenuItems::TOTAL_ITEMS;
            }while(UILib::IsItemVisible(*(menu_items+selected_item)));
        }
        
        for(int i = 0; i < (int)AdminMenuItems::TOTAL_ITEMS; i++){
            switch((AdminMenuItems)i){
                case AdminMenuItems::PREV_PAG_BTN:
                    if(user_page > 0){
                        UILib::UpdateItem(menu_items+i, &selected_item, i);
                    }
                break;
                case AdminMenuItems::NEXT_PAG_BTN:
                    if(!is_last_page){
                        UILib::UpdateItem(menu_items+i, &selected_item, i);
                    }
                break;
                default:
                    UILib::UpdateItem(menu_items+i, &selected_item, i);
                break;
            }
        }
    }

    //ADMIN MENU DRAW
    void DrawTitle(){
        UILib::Text title = {
            {255,255,255,255},
            "REGISTERED USERS",
            Utils::kBaseFontSize*3.5f
        };
        
        esat::DrawSetTextFont("./Assets/Fonts/Neuropol.otf");
        UILib::DrawText(
            (Utils::kWindowWidth*0.5f) - ((strlen(title.text)/2.5f)*title.font_size),
            100, 
            title
        );
        esat::DrawSetTextFont("./Assets/Fonts/Hyperspace.ttf");
    }

    void DrawUserItem(JMATH::Vec2 coord, float font_size, UserManager::User user){
        UILib::DrawText(
            coord, 
            {
                {255,255,255,255},
                user.username,
                font_size
            }
        );
        UILib::DrawText(
            JMATH::Vec2Sum(coord, {font_size*strlen("0123456789    "),0}), 
            {
                {255,255,255,255},
                user.alias,
                font_size
            }
        );

        UILib::DrawIntToText(
            JMATH::Vec2Sum(coord, {font_size*strlen("0123456789   ALIAS  "),0}), 
            {
                {255,255,255,255},
                nullptr,
                font_size
            },
            ((int)user.credits),2,true
        );
    }

    void DrawUserList(){
        float list_font_size = Utils::kBaseFontSize * 1.5f;

        JMATH::Vec2 base_coord = {
            (Utils::kWindowWidth*0.5f) - 
            (strlen("0123456789  ALIAS  CREDITS EDIT DELETE") * 0.45f * list_font_size),
            200
        };
        JMATH::Vec2 margin_v = {0,55};

        UILib::DrawText(
            base_coord,
            {
                {255,255,255,255},
                "USERNAME               ALIAS   CREDITS",
                {list_font_size}
            }
        );

        //Starts with 1 to apply margin from the beghining
        for(int i = 0; i < 10; i++){
            DrawUserItem(JMATH::Vec2Sum(base_coord,JMATH::Vec2Scale(margin_v,i+1)), list_font_size, *(page_users+i));
        }
    }

    void DrawMenuItems(){
        for(int i = 0; i < (int)AdminMenuItems::TOTAL_ITEMS; i++){
            switch((AdminMenuItems)i){
                case AdminMenuItems::PREV_PAG_BTN:
                    if(user_page <= 0){
                        (menu_items+i)->item.btn_item.is_visible = false;
                    }else{
                        (menu_items+i)->item.btn_item.is_visible = true;
                    }
                break;
                case AdminMenuItems::NEXT_PAG_BTN:
                    if(is_last_page){
                        (menu_items+i)->item.btn_item.is_visible = false;
                    }else{
                        (menu_items+i)->item.btn_item.is_visible = true;
                    }
                break;
            }
            UILib::DrawItem(*(menu_items+i));
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