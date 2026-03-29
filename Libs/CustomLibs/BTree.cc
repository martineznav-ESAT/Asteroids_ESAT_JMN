#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "./BTree.h"

namespace BTree{
    TreeNode* CreateTree(){
        return nullptr;
    }

    bool IsTreeEmpty(TreeNode* tree){
        return tree == nullptr;
    }

    TreeNode* FindTreeNode(TreeNode *tree, TreeInfo info){
        TreeNode* aux_tree = nullptr;

        if(!IsTreeEmpty(tree)){
            switch (tree->node_type){
                case TreeType::INT:
                    if(tree->info.int_info == info.int_info){
                        aux_tree = tree;
                    }else{
                        if(tree->right_leaf != nullptr && info.int_info > tree->info.int_info){
                            aux_tree = FindTreeNode(tree->right_leaf, info);
                        }

                        if(tree->left_leaf != nullptr && info.int_info < tree->info.int_info){
                            aux_tree = FindTreeNode(tree->left_leaf, info);
                        }
                    }
                break;
            
                case TreeType::CHAR:
                    if(tree->info.char_info == info.char_info){
                        aux_tree = tree;
                    }else{
                        if(tree->right_leaf != nullptr && info.char_info > tree->info.char_info){
                            aux_tree = FindTreeNode(tree->right_leaf, info);
                        }

                        if(tree->left_leaf != nullptr && info.char_info < tree->info.char_info){
                            aux_tree = FindTreeNode(tree->left_leaf, info);
                        }
                    }
                break;

                case TreeType::USER:
                    if(strcmp(info.user_info.username, tree->info.user_info.username) == 0){
                        aux_tree = tree;
                    }else{
                        if(tree->right_leaf != nullptr && strcmp(info.user_info.username, tree->info.user_info.username) > 0){
                            aux_tree = FindTreeNode(tree->right_leaf, info);
                        }

                        if(tree->left_leaf != nullptr && strcmp(info.user_info.username, tree->info.user_info.username) < 0){
                            aux_tree = FindTreeNode(tree->left_leaf, info);
                        }
                    }
                break;
            }
        }
        

        return aux_tree;
    }

    bool InsertTree(TreeNode** tree, TreeType node_type, TreeInfo info){
        bool is_insertable = IsTreeEmpty(FindTreeNode(*tree, info));

        if(is_insertable){
            // switch (node_type){
            //     case TreeType::USER:
            //         printf("SE VA A INSERTAR %s\n",info.user_info.username);
            //     break;
                
            //     default:
            //         printf("SE VA A INSERTAR %d\n",info.int_info);
            //     break;
            // }
            if(IsTreeEmpty(*tree)){
                *tree = (TreeNode*) malloc(sizeof(TreeNode));
                
                (*tree)->info = info;
                (*tree)->node_type = node_type;
                (*tree)->left_leaf = nullptr;
                (*tree)->right_leaf = nullptr;

            }else{
                switch (node_type){
                    case TreeType::INT:
                        if(info.int_info > (*tree)->info.int_info){
                            InsertTree(&(*tree)->right_leaf, node_type, info);
                        }

                        if(info.int_info < (*tree)->info.int_info){
                            InsertTree(&(*tree)->left_leaf, node_type, info);
                        }
                    break;
                
                    case TreeType::CHAR:
                        if(info.char_info > (*tree)->info.char_info){
                            InsertTree(&(*tree)->right_leaf, node_type, info);
                        }

                        if(info.char_info < (*tree)->info.char_info){
                            InsertTree(&(*tree)->left_leaf, node_type, info);
                        }
                    break;

                    case TreeType::USER:
                        if(strcmp(info.user_info.username, (*tree)->info.user_info.username) > 0){
                            InsertTree(&(*tree)->right_leaf, node_type, info);
                        }

                        if(strcmp(info.user_info.username, (*tree)->info.user_info.username) < 0){
                            InsertTree(&(*tree)->left_leaf, node_type, info);
                        }
                    break;
                }
            }
        }

        return is_insertable;
    }

    void ClearTree(TreeNode** tree){
        if((*tree)->right_leaf != nullptr){
            ClearTree(&(*tree)->right_leaf);
        }

        if((*tree)->left_leaf != nullptr){
            ClearTree(&(*tree)->left_leaf);
        }

        if((*tree)->node_type == TreeType::USER){
            UserManager::FreeUserMemory(&((*tree)->info.user_info));
        }
        free(*tree);
        *tree = nullptr;
    }

    void PrintTree(TreeNode* tree, int margin){
        if(!IsTreeEmpty(tree)){
            PrintTree(tree->right_leaf, margin+1);

            for(int i = 0; i < margin; i++){
                printf("         ");
            }
            switch (tree->node_type){
                case TreeType::INT:
                    printf("Info %d\n",tree->info.int_info);
                break;
            
                case TreeType::CHAR:
                    printf("Info %c\n",tree->info.char_info);
                break;

                case TreeType::USER:
                    printf("|| User %s - Passwd %s ",tree->info.user_info.username, tree->info.user_info.password);
                    if(tree->info.user_info.is_admin){
                        printf("A ");
                    }
                    printf("||\n");
                break;
            }

            PrintTree(tree->left_leaf, margin+1);
        }
    }

    void SaveNode(TreeNode *tree, FILE *file){
        if(file != NULL && !IsTreeEmpty(tree)){
            fwrite(&(tree->node_type), sizeof(tree->node_type), 1, file);

            switch (tree->node_type){
                case TreeType::INT:
                    fwrite(&(tree->info.int_info), sizeof(tree->info.int_info), 1, file);
                break;
            
                case TreeType::CHAR:
                    fwrite(&(tree->info.char_info), sizeof(tree->info.char_info), 1, file);
                break;

                case TreeType::USER:
                    UserManager::SaveUser(tree->info.user_info, file);
                break;
            }


            SaveNode(tree->left_leaf, file);

            SaveNode(tree->right_leaf, file);
        }
    }

    void SaveTree(TreeNode **tree, FILE *dat_file, char* dat_path){
        dat_file = fopen(dat_path, "wb");
        SaveNode(*tree, dat_file);
        fclose(dat_file);
    }

    bool LoadTree(TreeNode **tree_to_load, TreeType tree_type, FILE *dat_file, char* dat_path){
        bool is_loaded = true;
        *tree_to_load = CreateTree();
        TreeType aux_type;
        //Initialize "empty" info
        TreeInfo aux_info = {NULL};

        // Comprobar archivo antes de leer
        if((dat_file = fopen(dat_path,"rb")) == NULL){
            printf("ERROR NOT FOUND: \n%s\n",dat_path);
            is_loaded = false;
        }else{
            //If the read type is different than the parameter intended, fails to read file 
            //By C logic, the while conditional should execute the fread before aux_type comparison. 
            //So the aux_type == tree_type comparison should always be properly executed
            while (fread(&aux_type, sizeof(TreeType), 1, dat_file) && aux_type == tree_type){
                switch (tree_type){
                    case TreeType::INT:
                        fread(&(aux_info.int_info), sizeof(aux_info.int_info), 1, dat_file);
                    break;
                
                    case TreeType::CHAR:
                        fread(&(aux_info.char_info), sizeof(aux_info.char_info), 1, dat_file);
                    break;

                    case TreeType::USER:
                        aux_info.user_info = UserManager::LoadUser(dat_file);
                    break;
                }
                // printf("LOADED\n");
                InsertTree(tree_to_load, tree_type, aux_info);
            }

            if(aux_type != tree_type){
                is_loaded = false;
            }else{
                printf("---- REGISTERED USERS LOADED SEARCH TREE ----\n");
                PrintTree(*tree_to_load,0);
            }

            fclose(dat_file);
        }

        return is_loaded;
    }
}