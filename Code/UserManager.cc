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

#include "./UserManager.h"


//Holds the game information needed globally, that may be needed for Level/Screen management 
namespace UserManager{
    FILE *r_users_dat = nullptr;
    char *r_users_dat_path = "./Assets/Files/Data/r_users.dat";
    User *r_users = nullptr;
    int r_users_t = 0;
    
    //Extra length space for '\0' character to have space
    unsigned char kDefaultStrL = 20;
    unsigned char kAliasStrL = 3;
    unsigned char kEmailStrL = 40;
    unsigned char kCreditsStrL = 2;

    bool LoadRegisteredUsers(){
        bool is_loaded = false;
        User aux_user;

        if((r_users_dat = fopen(r_users_dat_path,"rb")) == NULL){
            printf("ERROR NOT FOUND: \n%s\n",r_users_dat_path);
        }else{
            // while (fread(&aux_user, sizeof(aux_user),1,r_users_dat)){

            // }
            fclose(r_users_dat);
        }

        return is_loaded;
    }

    bool RegisterNewUser(User new_user){
        bool is_registered = false;
        User aux_user;
        bool is_found = false;

        // TO_DO LECTURA Y ESCRITURA POR CHARS SEPARADOS. CUIDADIN
        if((r_users_dat = fopen(r_users_dat_path,"r+b")) == NULL){
            printf("ERROR NOT FOUND: \n%s\n",r_users_dat_path);
        }else{
            while (fread(&aux_user, sizeof(aux_user),1,r_users_dat) && !is_found){
                if(strcmp(aux_user.username, new_user.username) == 0){
                    is_found = true;
                }
            }
            fclose(r_users_dat);
        }

        return is_registered;
    }

    void CloseFiles(){
        fclose(r_users_dat);
    }
}