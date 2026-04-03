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
#include "../Libs/CustomLibs/TList.h"

#include "./GameManager.h"
#include "./UserManager.h"
#include "./LoginMenu.h"
#include "./RegisterMenu.h"
#include "./AdminMenu.h"
#include "./UserManager.h"

namespace RegisterMenu{
    //Memory block that holds all the menu items no matter if they are visible or not.
    UILib::UI_Item *menu_items = nullptr;
    GameManager::Level prev_level;
    int selected_item = -1;
    bool edit_mode = false;
    UserManager::User form_user;
    UserManager::User* form_user_edit;

    //ACTIONS

    //Copies form/menu_items values into User form_user with the corresponding typing conversions 
    //and saves the user on registered users list/tree. 
    //After finishing the registration, goes back to one of the possible previous pages before registration
    void SaveAction(){
        UserManager::FreeUserMemory(&form_user);
        form_user = UserManager::NewUser();

        strcpy(form_user.username, (menu_items+RegisterItems::USERNAME_TI)->item.text_item.input_text.text);
        strcpy(form_user.password, (menu_items + RegisterItems::PASSWORD_TI)->item.text_item.input_text.text);
        strcpy(form_user.alias, (menu_items + RegisterItems::ALIAS_TI)->item.text_item.input_text.text);

        if(strlen(form_user.username) > 0 && strlen(form_user.password) > 0 && strlen(form_user.alias) > 0){

            strcpy(form_user.email, (menu_items + RegisterItems::EMAIL_TI)->item.text_item.input_text.text);
            strcat(form_user.email, "@ASTEROIDS.ESAT");

            strcpy(form_user.name, (menu_items + RegisterItems::NAME_TI)->item.text_item.input_text.text);
            strcpy(form_user.surname, (menu_items + RegisterItems::SURNAME_TI)->item.text_item.input_text.text);

            form_user.day_dob = atoi((menu_items + RegisterItems::DOB_DAY_TI)->item.text_item.input_text.text);
            form_user.month_dob = atoi((menu_items + RegisterItems::DOB_MONTH_TI)->item.text_item.input_text.text);
            form_user.year_dob = atoi((menu_items + RegisterItems::DOB_YEAR_TI)->item.text_item.input_text.text);

            strcpy(form_user.country, (menu_items + RegisterItems::COUNTRY_TI)->item.text_item.input_text.text);
            strcpy(form_user.province, (menu_items + RegisterItems::PROVINCE_TI)->item.text_item.input_text.text);

            form_user.credits = atoi((menu_items + RegisterItems::CREDITS_TI)->item.text_item.input_text.text);
            form_user.is_admin = (menu_items + RegisterItems::ADMIN_CHK)->item.chk_item.is_checked;

            if(UserManager::RegisterNewUser(form_user)){
                if(prev_level == GameManager::Level::ADMIN_MENU){
                    AdminMenu::Load();
                }else{
                    LoginMenu::Load(GameManager::Level::REGISTER_MENU);
                }
            }else{
                //TO_DO GRAPHIC MODE
                printf("USERNAME TAKEN\n");
            }
        }else{
            //TO_DO GRAPHIC MODE
            printf("USERNAME, PASSWORD AND ALIAS ARE MANDATORY\n");
        }
    }

    void BackAction(){
        if(prev_level == GameManager::Level::ADMIN_MENU){
            AdminMenu::Load();
        }else{
            LoginMenu::Load(GameManager::Level::REGISTER_MENU);
        }
    }

    //REGISTER MENU INIT

    //Initializes all menu buttons
    void InitButtons(){
        JMATH::Vec2 centered_bottom_coords = {Utils::kWindowWidth*0.5f, Utils::kWindowHeight-200.0f};
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

        float btn_font_size = Utils::kBaseFontSize;

        UILib::InitButton(
            &((menu_items+((int)RegisterItems::SAVE_BTN))->item.btn_item),
            left_button,
            button_color,
            button_color,
            {
                text_color,
                "SAVE",
                btn_font_size
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
                btn_font_size
            },
            true,
            BackAction
        );
    }

    //Initializes all menu text Inputs
    void InitTextInputs(){
        Utils::Collider first_left_side = {{(Utils::kWindowWidth*0.5f)-350, 100}, JMATH::Vec2Sub({(Utils::kWindowWidth*0.5f)-50, 150},{0.0f, 4.0f})};
        Utils::Collider first_right_side = {{(Utils::kWindowWidth*0.5f)+40, 112.5f}, {(Utils::kWindowWidth*0.5f)+40 + (Utils::kBaseFontSize*14), 152.5f}};
        JMATH::Vec2 margin_y = {0.0f, 57.5f};
        float aux_input_width = first_right_side.P2.x-first_right_side.P1.x;

        JMATH::Vec2 dob_aux_P1 = JMATH::Vec2Sum(first_right_side.P1, JMATH::Vec2Scale(margin_y,6));
        JMATH::Vec2 dob_aux_P2 = JMATH::Vec2Sum(first_right_side.P2, JMATH::Vec2Scale(margin_y,6));

        JMATH::Vec2 admin_aux_P1 = JMATH::Vec2Sum(first_right_side.P1, JMATH::Vec2Scale(margin_y,9));
        JMATH::Vec2 admin_aux_P2 = JMATH::Vec2Sum(first_right_side.P2, JMATH::Vec2Scale(margin_y,9));

        float ti_font_size = Utils::kBaseFontSize;

        UILib::InitTextInput(
            &((menu_items + ((int)RegisterItems::USERNAME_TI))->item.text_item),
            first_left_side,
            first_right_side,
            {255,255,255,255},
            {0,0,0,255},
            {{255,255,255,255},nullptr, ti_font_size},
            true,
            true,
            false,
            false
        );

        UILib::InitTextInput(
            &((menu_items + ((int)RegisterItems::PASSWORD_TI))->item.text_item),
            {JMATH::Vec2Sum(first_left_side.P1, margin_y),JMATH::Vec2Sum(first_left_side.P2, margin_y)},
            {JMATH::Vec2Sum(first_right_side.P1, margin_y),JMATH::Vec2Sum(first_right_side.P2, margin_y)},
            {255,255,255,255},
            {0,0,0,255},
            {{255,255,255,255},nullptr, ti_font_size},
            true,
            true,
            false,
            true
        );

        UILib::InitTextInput(
            &((menu_items + ((int)RegisterItems::ALIAS_TI))->item.text_item),
            {JMATH::Vec2Sum(first_left_side.P1, JMATH::Vec2Scale(margin_y,2)),JMATH::Vec2Sum(first_left_side.P2, JMATH::Vec2Scale(margin_y,2))},
            {JMATH::Vec2Sum(first_right_side.P1, JMATH::Vec2Scale(margin_y,2)),JMATH::Vec2Sum(JMATH::Vec2Sum(first_right_side.P1,{ti_font_size*3.5f,40}), JMATH::Vec2Scale(margin_y,2))},
            {255,255,255,255},
            {0,0,0,255},
            {{255,255,255,255},nullptr, ti_font_size},
            true,
            true,
            false,
            false,
            UserManager::kAliasStrL
        );

        UILib::InitTextInput(
            &((menu_items + ((int)RegisterItems::EMAIL_TI))->item.text_item),
            {JMATH::Vec2Sum(first_left_side.P1, JMATH::Vec2Scale(margin_y,3)),JMATH::Vec2Sum(first_left_side.P2, JMATH::Vec2Scale(margin_y,3))},
            {
                JMATH::Vec2Sum(first_right_side.P1, JMATH::Vec2Scale(margin_y,3)),
                JMATH::Vec2Sum(first_right_side.P2, JMATH::Vec2Scale(margin_y,3))
            },
            {255,255,255,255},
            {0,0,0,255},
            {{255,255,255,255},nullptr, ti_font_size},
            true,
            true,
            false,
            false
        );

        UILib::InitTextInput(
            &((menu_items + ((int)RegisterItems::NAME_TI))->item.text_item),
            {JMATH::Vec2Sum(first_left_side.P1, JMATH::Vec2Scale(margin_y,4)),JMATH::Vec2Sum(first_left_side.P2, JMATH::Vec2Scale(margin_y,4))},
            {JMATH::Vec2Sum(first_right_side.P1, JMATH::Vec2Scale(margin_y,4)),JMATH::Vec2Sum(first_right_side.P2, JMATH::Vec2Scale(margin_y,4))},
            {255,255,255,255},
            {0,0,0,255},
            {{255,255,255,255},nullptr, ti_font_size},
            true,
            true,
            false,
            false
        );

        UILib::InitTextInput(
            &((menu_items + ((int)RegisterItems::SURNAME_TI))->item.text_item),
            {JMATH::Vec2Sum(first_left_side.P1, JMATH::Vec2Scale(margin_y,5)),JMATH::Vec2Sum(first_left_side.P2, JMATH::Vec2Scale(margin_y,5))},
            {JMATH::Vec2Sum(first_right_side.P1, JMATH::Vec2Scale(margin_y,5)),JMATH::Vec2Sum(first_right_side.P2, JMATH::Vec2Scale(margin_y,5))},
            {255,255,255,255},
            {0,0,0,255},
            {{255,255,255,255},nullptr, ti_font_size},
            true,
            true,
            false,
            false
        );

        UILib::InitTextInput(
            &((menu_items + ((int)RegisterItems::DOB_DAY_TI))->item.text_item),
            {JMATH::Vec2Sum(first_left_side.P1, JMATH::Vec2Scale(margin_y,6)),JMATH::Vec2Sum(first_left_side.P2, JMATH::Vec2Scale(margin_y,6))},
            {dob_aux_P1, JMATH::Vec2Sub(dob_aux_P2, {(aux_input_width/3)*2, 0.0f})},
            {255,255,255,255},
            {0,0,0,255},
            {{255,255,255,255},nullptr, ti_font_size},
            true,
            true,
            true,
            false,
            UserManager::kDOBDayL
        );

        UILib::InitTextInput(
            &((menu_items + ((int)RegisterItems::DOB_MONTH_TI))->item.text_item),
            {JMATH::Vec2Sum(first_left_side.P1, JMATH::Vec2Scale(margin_y,6)),JMATH::Vec2Sum(first_left_side.P2, JMATH::Vec2Scale(margin_y,6))},
            {JMATH::Vec2Sum(dob_aux_P1, {(aux_input_width/3), 0.0f}), JMATH::Vec2Sub(dob_aux_P2, {(aux_input_width/3), 0.0f})},
            {255,255,255,255},
            {0,0,0,255},
            {{255,255,255,255},nullptr, ti_font_size},
            true,
            false,
            true,
            false,
            UserManager::kDOBMonthL
        );

        UILib::InitTextInput(
            &((menu_items + ((int)RegisterItems::DOB_YEAR_TI))->item.text_item),
            {JMATH::Vec2Sum(first_left_side.P1, JMATH::Vec2Scale(margin_y,6)),JMATH::Vec2Sum(first_left_side.P2, JMATH::Vec2Scale(margin_y,6))},
            {JMATH::Vec2Sum(dob_aux_P1, {(aux_input_width/3)*2, 0.0f}), dob_aux_P2},
            {255,255,255,255},
            {0,0,0,255},
            {{255,255,255,255},nullptr, ti_font_size},
            true,
            false,
            true,
            false,
            UserManager::kDOBYearL
        );

        UILib::InitTextInput(
            &((menu_items + ((int)RegisterItems::COUNTRY_TI))->item.text_item),
            {JMATH::Vec2Sum(first_left_side.P1, JMATH::Vec2Scale(margin_y,7)),JMATH::Vec2Sum(first_left_side.P2, JMATH::Vec2Scale(margin_y,7))},
            {JMATH::Vec2Sum(first_right_side.P1, JMATH::Vec2Scale(margin_y,7)),JMATH::Vec2Sum(first_right_side.P2, JMATH::Vec2Scale(margin_y,7))},
            {255,255,255,255},
            {0,0,0,255},
            {{255,255,255,255},nullptr, ti_font_size},
            true,
            true,
            false,
            false
        );

        UILib::InitTextInput(
            &((menu_items + ((int)RegisterItems::PROVINCE_TI))->item.text_item),
            {JMATH::Vec2Sum(first_left_side.P1, JMATH::Vec2Scale(margin_y,8)),JMATH::Vec2Sum(first_left_side.P2, JMATH::Vec2Scale(margin_y,8))},
            {JMATH::Vec2Sum(first_right_side.P1, JMATH::Vec2Scale(margin_y,8)),JMATH::Vec2Sum(first_right_side.P2, JMATH::Vec2Scale(margin_y,8))},
            {255,255,255,255},
            {0,0,0,255},
            {{255,255,255,255},nullptr, ti_font_size},
            true,
            true,
            false,
            false
        );

        UILib::InitTextInput(
            &((menu_items + ((int)RegisterItems::CREDITS_TI))->item.text_item),
            {JMATH::Vec2Sum(first_left_side.P1, JMATH::Vec2Scale(margin_y,9)),JMATH::Vec2Sum(first_left_side.P2, JMATH::Vec2Scale(margin_y,9))},
            {JMATH::Vec2Sub(admin_aux_P1,{100.0f,0.0f}),JMATH::Vec2Sub(admin_aux_P2,{aux_input_width+50.0f,0.0f})},
            {255,255,255,255},
            {0,0,0,255},
            {{255,255,255,255},nullptr, ti_font_size},
            true,
            true,
            true,
            false,
            UserManager::kCreditsStrL
        );
    }

    void InitCheckboxes(){
        Utils::Collider first_left_side = {{(Utils::kWindowWidth*0.5f)-250, 100}, JMATH::Vec2Sub({(Utils::kWindowWidth*0.5f)-50, 150},{0.0f, 4.0f})};
        Utils::Collider first_right_side = {{(Utils::kWindowWidth*0.5f)+40, 120}, {(Utils::kWindowWidth*0.5f)+40 + (Utils::kBaseFontSize*14), 155}};
        JMATH::Vec2 margin_y = {0.0f, 57.5f};
        float aux_input_width = first_right_side.P2.x-first_right_side.P1.x;

        float chk_font_size = Utils::kBaseFontSize*1.5f;

        JMATH::Vec2 admin_aux_P1 = JMATH::Vec2Sum(first_right_side.P1, JMATH::Vec2Scale(margin_y,9));
        JMATH::Vec2 admin_aux_P2 = JMATH::Vec2Sum(first_right_side.P2, JMATH::Vec2Scale(margin_y,9));

        UILib::InitCheckbox(
            &((menu_items + ((int)RegisterItems::ADMIN_CHK))->item.chk_item),
            {admin_aux_P1,JMATH::Vec2Sub(admin_aux_P2,{0.0f, 4.0f})},
            {{admin_aux_P2.x-40.0f,admin_aux_P1.y},admin_aux_P2},
            {255,255,255,200},
            {50,50,50,200},
            {{255,255,255,255},"X", chk_font_size},
            false,
            true
        );
    }

    //Initializes all UI items
    void InitMenuItems(){

        // text_inputs = (UILib::TextInput*) malloc(sizeof(UILib::TextInput)*(int)RegisterItems::TOTAL_ITEMS);
        menu_items = (UILib::UI_Item*) malloc(sizeof(UILib::UI_Item)*(int)RegisterItems::TOTAL_ITEMS);
        float tag_font_size = Utils::kBaseFontSize*2.0f;

        UILib::InitItem(
            (menu_items + ((int)RegisterItems::USERNAME_TI)),
            UILib::ItemType::TEXT_INPUT,
            {{255,255,255,255},"USERNAME", tag_font_size}
        );
        UILib::InitItem(
            (menu_items + ((int)RegisterItems::PASSWORD_TI)),
            UILib::ItemType::TEXT_INPUT,
            {{255,255,255,255},"PASSWORD", tag_font_size}
        );

        UILib::InitItem(
            (menu_items + ((int)RegisterItems::ALIAS_TI)),
            UILib::ItemType::TEXT_INPUT,
            {{255,255,255,255},"ALIAS", tag_font_size}
        );

        UILib::InitItem(
            (menu_items + ((int)RegisterItems::EMAIL_TI)),
            UILib::ItemType::TEXT_INPUT,
            {{255,255,255,255},"E-MAIL", tag_font_size}
        );

        UILib::InitItem(
            (menu_items + ((int)RegisterItems::NAME_TI)),
            UILib::ItemType::TEXT_INPUT,
            {{255,255,255,255},"NAME", tag_font_size}
        );

        UILib::InitItem(
            (menu_items + ((int)RegisterItems::SURNAME_TI)),
            UILib::ItemType::TEXT_INPUT,
            {{255,255,255,255},"SURNAME", tag_font_size}
        );

        UILib::InitItem(
            (menu_items + ((int)RegisterItems::DOB_DAY_TI)),
            UILib::ItemType::TEXT_INPUT,
            {{255,255,255,255},"DATE OF BIRTH", tag_font_size}
        );

        UILib::InitItem(
            (menu_items + ((int)RegisterItems::DOB_MONTH_TI)),
            UILib::ItemType::TEXT_INPUT,
            {{255,255,255,255},"DOB_M", tag_font_size}
        );

        UILib::InitItem(
            (menu_items + ((int)RegisterItems::DOB_YEAR_TI)),
            UILib::ItemType::TEXT_INPUT,
            {{255,255,255,255},"DOB_Y", tag_font_size}
        );

        UILib::InitItem(
            (menu_items + ((int)RegisterItems::COUNTRY_TI)),
            UILib::ItemType::TEXT_INPUT,
            {{255,255,255,255},"COUNTRY", tag_font_size}
        );

        UILib::InitItem(
            (menu_items + ((int)RegisterItems::PROVINCE_TI)),
            UILib::ItemType::TEXT_INPUT,
            {{255,255,255,255},"PROVINCE", tag_font_size}
        );

        UILib::InitItem(
            (menu_items + ((int)RegisterItems::CREDITS_TI)),
            UILib::ItemType::TEXT_INPUT,
            {{255,255,255,255},"CREDITS", tag_font_size}
        );

        UILib::InitItem(
            (menu_items + ((int)RegisterItems::ADMIN_CHK)),
            UILib::ItemType::CHECKBOX,
            {{255,255,255,255},"ADMIN", tag_font_size}
        );

        UILib::InitItem(
            (menu_items + ((int)RegisterItems::SAVE_BTN)),
            UILib::ItemType::BUTTON,
            {{255,255,255,255},"SAVE", tag_font_size}
        );
        UILib::InitItem(
            (menu_items + ((int)RegisterItems::BACK_BTN)),
            UILib::ItemType::BUTTON,
            {{255,255,255,255},"BACK", tag_font_size}
        );
    }

    //Whole Register Menu initializer
    void Init(){
        form_user = UserManager::NewUser();
        InitMenuItems();
        InitTextInputs();
        InitButtons();
        InitCheckboxes();
    }

    //REGISTER MENU LOAD

    void CleanForm(bool is_admin = false){
        strcpy((menu_items + RegisterItems::USERNAME_TI)->item.text_item.input_text.text, "\0");
        strcpy((menu_items + RegisterItems::USERNAME_TI)->item.text_item.pointer, "|\0");

        strcpy((menu_items + RegisterItems::PASSWORD_TI)->item.text_item.input_text.text, "\0");
        strcpy((menu_items + RegisterItems::PASSWORD_TI)->item.text_item.pointer, "|\0");
        
        strcpy((menu_items + RegisterItems::ALIAS_TI)->item.text_item.input_text.text, "\0");
        strcpy((menu_items + RegisterItems::ALIAS_TI)->item.text_item.pointer, "|\0");
        
        strcpy((menu_items + RegisterItems::EMAIL_TI)->item.text_item.input_text.text, "\0");
        strcpy((menu_items + RegisterItems::EMAIL_TI)->item.text_item.pointer, "|\0");
        
        strcpy((menu_items + RegisterItems::NAME_TI)->item.text_item.input_text.text, "\0");
        strcpy((menu_items + RegisterItems::NAME_TI)->item.text_item.pointer, "|\0");
        
        strcpy((menu_items + RegisterItems::SURNAME_TI)->item.text_item.input_text.text, "\0");
        strcpy((menu_items + RegisterItems::SURNAME_TI)->item.text_item.pointer, "|\0");

        strcpy((menu_items + RegisterItems::DOB_DAY_TI)->item.text_item.input_text.text, "1\0");
        strcpy((menu_items + RegisterItems::DOB_DAY_TI)->item.text_item.pointer, "  |\0");
        
        strcpy((menu_items + RegisterItems::DOB_MONTH_TI)->item.text_item.input_text.text, "1\0");
        strcpy((menu_items + RegisterItems::DOB_MONTH_TI)->item.text_item.pointer, "  |\0");
        
        strcpy((menu_items + RegisterItems::DOB_YEAR_TI)->item.text_item.input_text.text, "1979\0");
        strcpy((menu_items + RegisterItems::DOB_YEAR_TI)->item.text_item.pointer, "    |\0");

        strcpy((menu_items + RegisterItems::COUNTRY_TI)->item.text_item.input_text.text, "\0");
        strcpy((menu_items + RegisterItems::COUNTRY_TI)->item.text_item.pointer, "|\0");
        
        strcpy((menu_items + RegisterItems::PROVINCE_TI)->item.text_item.input_text.text, "\0");
        strcpy((menu_items + RegisterItems::PROVINCE_TI)->item.text_item.pointer, "|\0");

        strcpy((menu_items + RegisterItems::CREDITS_TI)->item.text_item.input_text.text, "3\0");
        strcpy((menu_items + RegisterItems::CREDITS_TI)->item.text_item.pointer, " |\0");
        
        (menu_items + RegisterItems::ADMIN_CHK)->item.chk_item.is_checked = is_admin;
    }

    void AdjustPointerLength(UILib::TextInput* ti){
        // printf("ADJUST %d\n",strlen(ti->input_text.text));
        Utils::StringFillWithChar(ti->pointer, UserManager::kDefaultStrL,' ', strlen(ti->input_text.text));

        *(ti->pointer+strlen(ti->input_text.text)) = '|';
        *(ti->pointer+strlen(ti->input_text.text)+1) = '\0';
    }

    void LoadFormUserEdit(UserManager::User *user_edit){
        form_user_edit = user_edit;
        strcpy((menu_items + RegisterItems::USERNAME_TI)->item.text_item.input_text.text, form_user_edit->username);
        AdjustPointerLength(&((menu_items + RegisterItems::USERNAME_TI)->item.text_item));

        strcpy((menu_items + RegisterItems::PASSWORD_TI)->item.text_item.input_text.text, form_user_edit->password);
        AdjustPointerLength(&((menu_items + RegisterItems::PASSWORD_TI)->item.text_item));
        
        strcpy((menu_items + RegisterItems::ALIAS_TI)->item.text_item.input_text.text, form_user_edit->alias);
        AdjustPointerLength(&((menu_items + RegisterItems::ALIAS_TI)->item.text_item));
        
        //Checks if there's a registered email
        if(Utils::FindCharIndexInString(form_user_edit->email,'@') <= 0){
            //Fills it empty
            strcpy((menu_items + RegisterItems::EMAIL_TI)->item.text_item.input_text.text, "\0");
        }else{
            //Copy content before @ and forces end of word at @ location for the text input
            strncpy((menu_items + RegisterItems::EMAIL_TI)->item.text_item.input_text.text, form_user_edit->email, Utils::FindCharIndexInString(form_user_edit->email,'@'));
            *((menu_items + RegisterItems::EMAIL_TI)->item.text_item.input_text.text+Utils::FindCharIndexInString(form_user_edit->email,'@')) = '\0';
        }
        AdjustPointerLength(&((menu_items + RegisterItems::EMAIL_TI)->item.text_item));
        
        // strcpy((menu_items + RegisterItems::NAME_TI)->item.text_item.input_text.text, "\0");
        // strcpy((menu_items + RegisterItems::NAME_TI)->item.text_item.pointer, "|\0");
        
        // strcpy((menu_items + RegisterItems::SURNAME_TI)->item.text_item.input_text.text, "\0");
        // strcpy((menu_items + RegisterItems::SURNAME_TI)->item.text_item.pointer, "|\0");

        // strcpy((menu_items + RegisterItems::DOB_DAY_TI)->item.text_item.input_text.text, "01\0");
        // strcpy((menu_items + RegisterItems::DOB_DAY_TI)->item.text_item.pointer, "  |\0");
        
        // strcpy((menu_items + RegisterItems::DOB_MONTH_TI)->item.text_item.input_text.text, "01\0");
        // strcpy((menu_items + RegisterItems::DOB_MONTH_TI)->item.text_item.pointer, "  |\0");
        
        // strcpy((menu_items + RegisterItems::DOB_YEAR_TI)->item.text_item.input_text.text, "1979\0");
        // strcpy((menu_items + RegisterItems::DOB_YEAR_TI)->item.text_item.pointer, "    |\0");

        // strcpy((menu_items + RegisterItems::COUNTRY_TI)->item.text_item.input_text.text, "\0");
        // strcpy((menu_items + RegisterItems::COUNTRY_TI)->item.text_item.pointer, "|\0");
        
        // strcpy((menu_items + RegisterItems::PROVINCE_TI)->item.text_item.input_text.text, "\0");
        // strcpy((menu_items + RegisterItems::PROVINCE_TI)->item.text_item.pointer, "|\0");

        // strcpy((menu_items + RegisterItems::CREDITS_TI)->item.text_item.input_text.text, "3\0");
        // strcpy((menu_items + RegisterItems::CREDITS_TI)->item.text_item.pointer, " |\0");
        
        // (menu_items + RegisterItems::ADMIN_CHK)->item.chk_item.is_checked = is_admin;
    }

    //Based on the level/screen you come from, the Register Menu will be loaded differently
    void Load(GameManager::Level level_p, UserManager::User *user_edit){
        GameManager::game_status.level = GameManager::Level::REGISTER_MENU;
        
        selected_item = -1;
        prev_level = level_p;

        if(TList::ListLength((TList::ListNode*) (UserManager::user_list)) <= 0){
            //First ever game execution opens ADMIN REGISTRATION 
            (menu_items+((int)RegisterItems::ADMIN_CHK))->item.chk_item.is_checked = true;
            (menu_items+((int)RegisterItems::BACK_BTN))->item.btn_item.is_visible = false;

            form_user.is_admin = true;
        }else{
            (menu_items+((int)RegisterItems::ADMIN_CHK))->item.chk_item.is_checked = false;
            (menu_items+((int)RegisterItems::BACK_BTN))->item.btn_item.is_visible = true;

            form_user.is_admin = false;
        }

        if(user_edit == nullptr){
            edit_mode = false;
            CleanForm(form_user.is_admin);
        }else{
            edit_mode = true;
            LoadFormUserEdit(user_edit);
        }

    }

    //REGISTER MENU UPDATE

    //In case its the first ever user being registered, or in case the logged user is not an admin (or there's no logged user at all)
    //The fields CREDITS and ADMIN will not be modifieable.
    //Same goes to the Username TextInput if the menu is opened in edit mode
    bool IsUneditable(RegisterItems r_item){
        return (
            (r_item == RegisterItems::CREDITS_TI || r_item == RegisterItems::ADMIN_CHK || (r_item == RegisterItems::USERNAME_TI && edit_mode)) &&
            (
                TList::ListLength((TList::ListNode*) (UserManager::user_list)) <= 0 || 
                GameManager::game_status.logged_user == nullptr || 
                !((GameManager::game_status.logged_user)->is_admin)
            )
        );
    }

    //Whole Register Menu update method
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
                    selected_item = ((int)RegisterItems::TOTAL_ITEMS) - 1;
                }else{
                    selected_item--;
                }
            }while(!UILib::IsItemVisible(*(menu_items+selected_item)));
        }
        if(esat::IsSpecialKeyDown(esat::kSpecialKey_Down) || esat::IsSpecialKeyDown(esat::kSpecialKey_Tab)){
            do{
                ++selected_item %= (int)RegisterItems::TOTAL_ITEMS;
            }while(!UILib::IsItemVisible(*(menu_items+selected_item)));
        }
        
        for(int i = 0; i < (int)RegisterItems::TOTAL_ITEMS; i++){
            if(!IsUneditable((RegisterItems)i)){
                UILib::UpdateItem(menu_items+i, &selected_item, i);
            }
        }
    }

    //REGISTER MENU DRAW

    void DrawMenuItems(){
        Utils::Collider first_right_side = {{(Utils::kWindowWidth*0.5f)+40, 120}, {(Utils::kWindowWidth*0.5f)+40 + (Utils::kBaseFontSize*14), 155}};
        JMATH::Vec2 margin_y = {0.0f, 57.5f};

        for(int i = 0; i < (int)RegisterItems::TOTAL_ITEMS; i++){
            UILib::DrawItem(*(menu_items+i));
        }

        

        UILib::DrawText(
            JMATH::Vec2Sum(JMATH::Vec2Sum(first_right_side.P2, JMATH::Vec2Scale(margin_y,2.75)), {20,0}),
            {{255,255,255,255},"@ASTEROIDS.ESAT",(float)Utils::kBaseFontSize}
        );
    }

    //Whole Register Menu draw method
    void Draw(){
        DrawMenuItems();
    }

    void EmptyMemory(){
        for(int i = 0; i < (int)RegisterItems::TOTAL_ITEMS; i++){
            UILib::EmptyItemMemory(menu_items+i);
        }
        UserManager::FreeUserMemory(&form_user);
        free(menu_items);
    }
}