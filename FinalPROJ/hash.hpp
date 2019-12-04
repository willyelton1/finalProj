#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct LLNode{ //Linked List collision function
  int key ;
  LLNode* next;
};
struct TreeNode{ //BST collision struct
  int key;
  TreeNode *left , *right;
};
struct HashNode{
  int linearData;
  LLNode* head;
  TreeNode* root;
};
class Hash{

  public:
    Hash();
    ~Hash();
    int hashMod(int key);
    int hashFloor(int key);
    float loadFactor();
    void printLinear(int number);
    void LinearInsert1(int key);
    void LinearInsert2(int key);
    bool table1Linear(int index, int key);
    bool table2Linear(int index, int key);
    void LinearDelete1(int key);
    void LinearDelete2(int key);
    int LinearSearch1(int key);
    int LinearSearch2(int key);
    ////////////////////Linear Probing functions complete
    void LLInsert1(int key);//Linked list
    void LLInsert2(int key);
    void LLPrint();
    void LLCollision1(int key);
    void LLCollision2(int key);
    void LLDelete1(int key);
    void LLDelete2(int key);
    bool LLSearch1(int key);
    bool LLSearch2(int key);

    ///////////////////////////////////
    TreeNode* minValueNode(TreeNode* root);
    TreeNode* deleteNodeHelper(TreeNode* temp, int key);
    bool deleteNode(int key);
    TreeNode* newTreeNode(int key);
    TreeNode* insertTree1(int key);
    TreeNode* insertTree2(int key);
    TreeNode* TreeCollision(TreeNode* node, int key);
    bool TreeSearch1(int key);
    bool TreeSearch2(int key);
    TreeNode* treeSearchHelper(TreeNode* root, int key);
    void printTree1();
    void printTree2();
    void inOrder(TreeNode* root);
    ////////////////////////////////////
    void cuckooDriver();
    void cuckooHelper(int key, int tableNum, int count, int size, int arr[], int arr2[]);
    void cuckooPrint(int arr[], int arr2[]);
    int cuckooHash1(int key);
    int cuckooHash2(int key);
    void reHash();
    bool cuckooSearch(int key, int arr[], int arr2[]);
    bool cuckooDelete(int key, int arr[], int arr2[]);
    void Driver();
    void time(int arr[]);

  private:
    int const static TABLE_SIZE = 10009;
    int cuckooSize;
    HashNode hashTable1[TABLE_SIZE];
    HashNode hashTable2[TABLE_SIZE];
    int itemsInserted;

};
