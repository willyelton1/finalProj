#include <iostream>
#include "BST.hpp"


BST::BST(){
  root = NULL;
}
BST::~BST(){
  
}
TreeNode* BST::BSTsearch(int key,TreeNode* node){
      if(node == NULL || node->key == key) return node;

      else if(node->key > key){
        return BSTsearch(key, node->left);
      }
      else if(node->key < key){
        return BSTsearch(key , node->right);
      }
  }
  void BST::BSTInsert(int key, TreeNode* node){
    if(node == NULL) return;

    if(node->key > key){
      node->left = BSTInsert(key, root->left);
    }
    if(node->key < key){
      node->right = BSTInsert(key, root->right);
    }

  }
  void BST::BSTDelete(int key){

  }
  void BST::printTree(TreeNode* node){
      printTree(node->left);
      cout << node->key << " ";
      printTree


  }
