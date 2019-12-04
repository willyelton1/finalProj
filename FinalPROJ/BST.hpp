#include <iostream>
using namespace std;
struct TreeNode{ //BST collision struct
  int key;
  TreeNode *left , *right;
};
class BST{
  public:
    BST();
    ~BST();
    TreeNode* BSTsearch(int key,TreeNode* node);
    void BSTInsert(int key, TreeNode* node);
    void BSTDelete(int key);
    void printTree(TreeNode* node);
    TreeNode* newNode(int key);
  private:
    TreeNode* root;


};
