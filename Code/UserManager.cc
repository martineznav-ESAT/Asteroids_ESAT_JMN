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

#include "../Libs/CustomLibs/BTree.h"

//Holds the game information needed globally, that may be needed for Level/Screen management 
namespace UserManager{
    FILE *user_tree_dat = nullptr;
    char *user_tree_dat_path = "./Assets/Files/Data/user_tree.dat";
    BTree::TreeNode *user_tree = nullptr;
    int user_tree_t = 0;
    
    unsigned char kDefaultStrL = 20;
    unsigned char kAliasStrL = 3;
    unsigned char kEmailStrL = 40;
    unsigned char kDOBDayL = 2;
    unsigned char kDOBMonthL = 2;
    unsigned char kDOBYearL = 4;
    unsigned char kCreditsStrL = 2;

    User NewUser(){
        User new_user;
        new_user.username = (char*) malloc(sizeof(char)*(kDefaultStrL+1));
        *(new_user.username) = '\0';
        
        new_user.password = (char*) malloc(sizeof(char)*(kDefaultStrL+1));
        *(new_user.username) = '\0';
        
        new_user.alias = (char*) malloc(sizeof(char)*(kAliasStrL+1));
        *(new_user.username) = '\0';
        
        new_user.email = (char*) malloc(sizeof(char)*(kEmailStrL+1));
        *(new_user.username) = '\0';
        
        new_user.name = (char*) malloc(sizeof(char)*(kDefaultStrL+1));
        *(new_user.username) = '\0';
        
        new_user.surname = (char*) malloc(sizeof(char)*(kDefaultStrL+1));
        *(new_user.username) = '\0';

        new_user.day_dob = 1;
        new_user.month_dob = 1;
        new_user.year_dob = 1979;
        
        new_user.country = (char*) malloc(sizeof(char)*(kDefaultStrL+1));
        *(new_user.username) = '\0';
        
        new_user.province = (char*) malloc(sizeof(char)*(kDefaultStrL+1));
        *(new_user.username) = '\0';

        new_user.credits = 3;
        new_user.is_admin = false;

        return new_user;
    }

    void FreeUserMemory(User *user){
        free(user->username);
        free(user->password);
        free(user->alias);
        free(user->email);
        free(user->name);
        free(user->surname);
        free(user->country);
        free(user->province);
    }

    void SaveUser(User user, FILE *dat_file){
        //char* values are writen with +1 length to ensure '\0' character has space to be saved 
        //(Should have been written the same way previously) 
        if(dat_file != NULL){
            // printf("SAVE %s\n",user.username);
            fwrite(user.username, sizeof(char), kDefaultStrL+1, dat_file);
            
            // printf("SAVE %s\n",user.password);
            fwrite(user.password, sizeof(char), kDefaultStrL+1, dat_file);
            
            // printf("SAVE %s\n",user.alias);
            fwrite(user.alias, sizeof(char), kAliasStrL+1, dat_file);
            
            // printf("SAVE %s\n",user.email);
            fwrite(user.email, sizeof(char), kEmailStrL+1, dat_file);
            
            // printf("SAVE %s\n",user.name);
            fwrite(user.name, sizeof(char), kDefaultStrL+1, dat_file);
            
            // printf("SAVE %s\n",user.surname);
            fwrite(user.surname, sizeof(char), kDefaultStrL+1, dat_file);
            
            // printf("SAVE %d\n",user.day_dob);
            fwrite(&(user.day_dob), sizeof(int), 1, dat_file);
            
            // printf("SAVE %d\n",user.month_dob);
            fwrite(&(user.month_dob), sizeof(int), 1, dat_file);
            
            // printf("SAVE %d\n",user.year_dob);
            fwrite(&(user.year_dob), sizeof(int), 1, dat_file);
            
            // printf("SAVE %s\n",user.country);
            fwrite(user.country, sizeof(char), kDefaultStrL+1, dat_file);
            
            // printf("SAVE %s\n",user.province);
            fwrite(user.province, sizeof(char), kDefaultStrL+1, dat_file);
            
            // printf("SAVE %d\n",user.credits);
            fwrite(&(user.credits), sizeof(unsigned char), 1, dat_file);
            
            // if(user.is_admin){
            //     printf("SAVE ADMIN\n");
            // }else{
            //     printf("SAVE NO ADMIN\n");
            // }
            fwrite(&(user.is_admin), sizeof(bool), 1, dat_file);
        }
    }

    User LoadUser(FILE *dat_file){
        //char* values are read with +1 length to ensure '\0' character has space to be saved 
        //(Should have been written the same way previously) 
        User aux_user = NewUser();
        if(dat_file != NULL){
            // printf("START LOAD\n");
            fread(aux_user.username, sizeof(char), kDefaultStrL+1, dat_file);
            // printf("LOAD %s\n",aux_user.username);

            fread(aux_user.password, sizeof(char), kDefaultStrL+1, dat_file);
            // printf("LOAD %s\n",aux_user.password);

            fread(aux_user.alias, sizeof(char), kAliasStrL+1, dat_file);
            // printf("LOAD %s\n",aux_user.alias);

            fread(aux_user.email, sizeof(char), kEmailStrL+1, dat_file);
            // printf("LOAD %s\n",aux_user.email);

            fread(aux_user.name, sizeof(char), kDefaultStrL+1, dat_file);
            // printf("LOAD %s\n",aux_user.name);

            fread(aux_user.surname, sizeof(char), kDefaultStrL+1, dat_file);
            // printf("LOAD %s\n",aux_user.surname);

            fread(&(aux_user.day_dob), sizeof(int), 1, dat_file);
            // printf("LOAD %d\n",aux_user.day_dob);
            fread(&(aux_user.month_dob), sizeof(int), 1, dat_file);
            // printf("LOAD %d\n",aux_user.month_dob);
            fread(&(aux_user.year_dob), sizeof(int), 1, dat_file);
            // printf("LOAD %d\n",aux_user.year_dob);
            
            fread(aux_user.country, sizeof(char), kDefaultStrL+1, dat_file);
            // printf("LOAD %s\n",aux_user.country);

            fread(aux_user.province, sizeof(char), kDefaultStrL+1, dat_file);
            // printf("LOAD %s\n",aux_user.province);

            fread(&(aux_user.credits), sizeof(unsigned char), 1, dat_file);
            // printf("LOAD %d\n",aux_user.credits);

            fread(&(aux_user.is_admin), sizeof(bool), 1, dat_file);
            // if(aux_user.is_admin){
            //     printf("LOAD ADMIN\n");
            // }else{
            //     printf("LOAD NO ADMIN\n");
            // }
            
            user_tree_t++;
        }

        return aux_user;
    }

    bool LoadRegisteredUsers(){
        return LoadTree(&user_tree, BTree::TreeType::USER, user_tree_dat, user_tree_dat_path);
    }

    bool RegisterNewUser(User new_user){
        BTree::TreeInfo aux_info = {NULL};
        bool is_registered = true;

        aux_info.user_info = new_user;

        if(BTree::InsertTree(&user_tree, BTree::TreeType::USER, aux_info)){
            printf("---- REGISTERED USERS SEARCH TREE TO SAVE  ----\n");
            BTree::PrintTree(user_tree,0);
            BTree::SaveTree(&user_tree, user_tree_dat, user_tree_dat_path);
        }else{
            is_registered = false;
        }

        return is_registered;
    }

    void CloseFiles(){
        fclose(user_tree_dat);
    }
}