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
  TreeNode* root;
  LLNode* head;
};
class Hash{

  public:
    Hash();
    ~Hash();
    int hashMod(int key);
    int hashFloor(int key);
    void printTable(int number);
    void LinearInsert(int key);
    bool table1Linear(int index, int key);
    bool table2Linear(int index, int key);
    void LLInsert(int key);
    void LLPrint();
    void LLCollision(int key);
  private:
    static const int TABLE_SIZE = 1019;
    HashNode hashTable1[TABLE_SIZE];
    HashNode hashTable2[TABLE_SIZE];

};
Hash::Hash(){
  for(int i = 0; i < TABLE_SIZE; i++){
  hashTable2[i].linearData = hashTable1[i].linearData = -1;
  hashTable2[i].root = hashTable2[i].root = NULL;
  hashTable2[i].head = hashTable1[i].head = NULL;
  }
}
Hash::~Hash(){

}
int Hash::hashMod(int key){
  return key % TABLE_SIZE;
}
int Hash::hashFloor(int key){
  return key/TABLE_SIZE; //Uneven int division just returns floor
}
void Hash::printTable(int number){
    if(number == 1){
      for(int i = 0; i < TABLE_SIZE; i++){//print table 1
        cout << i << " : " << hashTable1[i].linearData << endl;

      }
      return;
    }
    for(int p = 0; p < TABLE_SIZE; p++){ //print table 2
      cout << hashTable2[p].linearData << " ";
    }
return ;
}
bool Hash::table1Linear(int index, int key){
    for(int i = index+1; i < TABLE_SIZE; i++){
        if(hashTable1[i].linearData == -1){ //If empty index
            hashTable1[i].linearData = key; //Place new data
            return true;
        }
      }
      for(int p = 0; p < index; p++){ //After end of table is reached check from begging to index for open slot
          if(hashTable1[p].linearData == -1){
            hashTable1[p].linearData = key;
            return true;
          }
      }
    return false; //If table full
}
bool Hash::table2Linear(int index, int key){
  for(int i = index+1; i < TABLE_SIZE; i++){
      if(hashTable2[i].linearData == -1){ //If empty index
          hashTable2[i].linearData = key; //Place new data
          return true;
      }
    }
    for(int p = 0; p < index; p++){ //After end of table is reached check from begging to index for open slot
        if(hashTable2[p].linearData == -1){
          hashTable2[p].linearData = key;
          return true;
        }
    }
  return false; //If table full
}

void Hash::LinearInsert(int key){
  int index = hashMod(key);
  if(hashTable1[index].linearData == -1)
    hashTable1[index].linearData = key;
  else
    table1Linear(index, key);



}
void Hash::LLInsert(int key){
     int index = hashMod(key);
     LLNode* temp = new LLNode;
     if(hashTable1[index].head == NULL){
        temp->key = key;
        temp->next = NULL;
        hashTable1[index].head = temp;
     }

}
void Hash::LLPrint(){
  for(int i = 0; i < TABLE_SIZE; i++){
    cout << i << ":  ";
    LLNode* temp = hashTable1[i].head;
      while(temp){
      cout << temp->key << "-->" ; //Print list
      temp = temp->next;
      }
      cout << "NULL" << endl;
  }
}
void Hash::LLCollision(int key){
     int index = hashMod(key);

}

int main(){
  Hash h1;
  //cout << h1.hashFloor(5221) << endl;//Expected 5

  // h1.printTable(1);
  // // h1.LinearInsert(0);
  // h1.LinearInsert(1018);
  // h1.LinearInsert(1017);
  // h1.LinearInsert(1016);
  // h1.LinearInsert(1019);
  for(int i =0 ; i < 4; i++){
    // cout << i * 1019 << endl;
    h1.LLInsert(i * 1017);
  }
  h1.LLInsert(1018);
  h1.LLInsert(2 * 1018);
  h1.LLPrint();
}
