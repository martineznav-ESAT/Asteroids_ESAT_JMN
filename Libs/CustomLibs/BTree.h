#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "../../Code/UserManager.h"

#ifndef BTree_H
#define BTree_H

namespace BTree{
    enum TreeType{
        INT,
        CHAR,
        USER,
    };

    union TreeInfo{
        int int_info;
        char char_info;
        UserManager::User user_info;
    };

    struct TreeNode{
        TreeInfo info;
        TreeType node_type;
        TreeNode* left_leaf;
        TreeNode* right_leaf;
    };

    TreeNode* CreateTree();

    bool IsTreeEmpty(TreeNode* tree);

    TreeNode* FindTreeNode(TreeNode *tree, TreeInfo info);

    bool InsertTree(TreeNode** tree, TreeType node_type, TreeInfo info);

    void ClearTree(TreeNode** tree);

    void PrintTree(TreeNode* tree, int margin);

    void SaveNode(TreeNode *tree, FILE *opened_file);

    void SaveTree(TreeNode **tree, FILE *dat_file, char* dat_path);

    bool LoadTree(TreeNode **tree_to_load,TreeType tree_type, FILE *dat_file, char* dat_path);
}

#endif
