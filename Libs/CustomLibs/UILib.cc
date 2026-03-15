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

#include "./Utils.h"
#include "./UILib.h"
#include "../../Code/GameStatus.h"

namespace UILib{
    const int kMaxTextLength = 20;

    //UI_ITEM
    void InitItem(UI_Item* ui_item, ItemType it, Text name){
        *ui_item = {
            it,
            name,
            NULL,
            false
        };
    }
    
    //TEXT

    //Draws a text given a position and Text structure 
    void DrawText(float x, float y, Text text){
        esat::DrawSetFillColor(text.color.r, text.color.g, text.color.b, text.color.a);
        esat::DrawSetTextSize(text.font_size);
        esat::DrawText(x, y, text.text);
    }

    //Draws the int value given as text on designed position 
    void DrawIntText(float x, float y, int value){
        char* text = (char*) malloc(sizeof(char)*3);
        text = itoa(value,text,10);
        esat::DrawText(x, y, text);
        free(text);
    }



    //BUTTON

    //Executes the given function
    //Gives a print in case its given null
    //Mainly thought for buttons or similar action-like UI elements and keyboard inputs
    void LaunchAction(void (*action)()){
        if(action != nullptr){
            action();
        }else{
            printf("Action WIP\n");
        }
    }

    //Changes button color in case the mouse is hovering on it
    //and grants acces to click the button if that's the case
    void OnButtonHover(Button *b){
        if(b->is_visible && Utils::MouseInCollider(b->collider)){
            //OnHover
            b->border_color.a = 255;
            b->fill_color.a = 255;
            if(esat::MouseButtonDown(0)){
                //OnClick
                LaunchAction(b->action);
            }
        }else{
            b->border_color.a = 230;
            b->fill_color.a = 230;
        }
    }

    //Given a button as parameter, fills it with the rest of the parameters. Created mainly for readability
    void InitButton(UILib::Button *b, Utils::Collider coll, Utils::Color border_color, Utils::Color fill_color, UILib::Text b_text, bool is_visible, void (*action)()){
        *b = {
            coll,
            border_color,
            fill_color,
            b_text,
            is_visible,
            action
        };
    }

    //Given a button, it gets checked to manage workability
    void UpdateButton(Button *button){
        OnButtonHover(button);
    }

    //Draws on screen the button given as parameter
    void DrawButton(Button b){
        if(b.is_visible){
            Utils::DrawCollider(b.collider, b.border_color, b.fill_color);

            //In case the button has a text, it's drawn centered to the button
            if(b.button_text.text != nullptr){
                UILib::DrawText(
                    b.collider.P1.x + ((b.collider.P2.x-b.collider.P1.x) * 0.5f) - (strlen(b.button_text.text) * b.button_text.font_size * 0.33 ), //Multiplied by 0.33 because it is the scale needed to be centered based con the custom font. The reasonable multiplication should be 0.5 (/2)
                    b.collider.P2.y - ((b.collider.P2.y-b.collider.P1.y) * 0.5f) + (b.button_text.font_size*0.5f), 
                    b.button_text
                );
            }
        }
    }



    //TEXT_INPUT

    //Given a button as parameter, fills it with the rest of the parameters. Created mainly for readability
    void InitTextInput(UILib::TextInput *ti, Utils::Collider coll, Utils::Color border_color, Utils::Color fill_color, UILib::Text ti_text, bool is_visible){
        *ti = {
            coll,
            border_color,
            fill_color,
            ti_text,
            is_visible
        };
    }

    //Given a Text Input, it gets checked to manage input workability
    void UpdateTextInput(TextInput *ti){
        if(Utils::MouseInCollider(ti->input_box)){
            printf("INPUT TEXT SELECCIONABLE\n");
        }
    }

    //Draws on screen the TextInput given as parameter
    void DrawTextInput(TextInput ti){
        if(ti.is_visible){

            Utils::DrawCollider(ti.input_box, ti.border_color, ti.fill_color);

            if(ti.input_text.text != nullptr){
                //Draws the text centered vertically inside de input box and aligned to the left horizontaly
                UILib::DrawText(
                    ti.input_box.P1.x + ti.input_text.font_size*0.66f,
                    ti.input_box.P2.y - ((ti.input_box.P2.y - ti.input_box.P1.y) * 0.5) + (ti.input_text.font_size * 0.5f), 
                    ti.input_text
                );
            }
        }
    }
}