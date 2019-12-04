#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
// #include "BST.hpp"
using namespace std;
struct LLNode{ //Linked List collision function
  int key ;
  LLNode* next;
};
struct HashNode{
  int linearData;
  LLNode* head;
};
struct hashNode{
  int data;
  TreeNode* root;
  LLNode* head;
};
class Hash{

  public:
    Hash();
    ~Hash();
    int hashMod(int key);
    int hashFloor(int key);
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
    void LLInsert(int key);//Linked list
    void LLPrint();
    void LLCollision(int key);
    void Driver();
  private:
    int const static TABLE_SIZE = 10009;
    HashNode hashTable1[TABLE_SIZE];
    HashNode hashTable2[TABLE_SIZE];

};
Hash::Hash(){
  for(int i = 0; i < TABLE_SIZE; i++){
  hashTable2[i].linearData = hashTable1[i].linearData = -1;
  // hashTable2[i].root = hashTable2[i].root = NULL;
  hashTable2[i].head = hashTable1[i].head = NULL;
  }
}
Hash::~Hash(){

}
int Hash::hashMod(int key){
  return key % TABLE_SIZE;
}
int Hash::hashFloor(int key){
  return key/TABLE_SIZE; // int division just returns floor
}
////////////////////////////////////////////////////Linear Fucntions below
void Hash::printLinear(int number){
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

void Hash::LinearInsert1(int key){
  int index = hashMod(key);
  if(hashTable1[index].linearData == -1)
    hashTable1[index].linearData = key;
  else if(LinearSearch1(key) != -1)
    table1Linear(index, key);
}


void Hash::LinearInsert2(int key){
  int index = hashMod(key);
  if(hashTable2[index].linearData == -1)
    hashTable2[index].linearData = key;
  else
    table2Linear(index, key);
}
void Hash::LinearDelete1(int key){
  cout << "LD1" << endl;
  for(int i = 0; i < TABLE_SIZE; i++){
    if(hashTable1[i].linearData == key){
      hashTable1[i].linearData = -1;
      return;
    }
  }
}
void Hash::LinearDelete2(int key){
  for(int i = 0; i < TABLE_SIZE; i++){
    if(hashTable2[i].linearData == key){
      hashTable2[i].linearData = -1;
      return;
    }
  }
}
int Hash::LinearSearch1(int key){
    for(int i = 0; i < TABLE_SIZE; i++){ //Traverse list until you find correct key
        if(hashTable1[i].linearData == key) return i;//returns index
    }
    return -1; //Return -1 if key isn't found
}
int Hash::LinearSearch2(int key){
      for(int i = 0; i < TABLE_SIZE; i++){ //Traverse list until you find correct key
          if(hashTable2[i].linearData == key) return i;
      }
      return -1; //Return -1 if key isn't found
}
/////////////////////////////////////////////////////
void Hash::LLInsert(int key){
     int index = hashMod(key);
     LLNode* temp = new LLNode;
     if(hashTable1[index].head == NULL){
        temp->key = key;
        temp->next = NULL;
        hashTable1[index].head = temp;
     }
     else{
       LLCollision(key);
     }

}
void Hash::LLPrint(){
  for(int i = 0; i < TABLE_SIZE; i++){ //check each hash node for linked list
    cout << i << ":  ";
    LLNode* temp = hashTable1[i].head;
      while(temp){ //Traverse list
      cout << temp->key << "-->" ; //Print list
      temp = temp->next;
      }
      cout << "NULL" << endl; //Print null at end of list or if no list
  }
}
void Hash::LLCollision(int key){
     int index = hashMod(key);
     LLNode* head = hashTable1[index].head;
     LLNode* temp = new LLNode;
     temp->key = key;
      if(head->key < key){
       temp->next = head;
       hashTable1[index].head = temp;
       return;
       }
       while(head->next && head->key < key){
          head = head->next;
       }
       temp->next = head->next;
       head->next = temp;

}
void Hash::Driver(){
    int count = 0;
    ifstream f;
    string temp;
    f.open("dataSetA.csv");
    while(getline(f, temp, ',')){
    LLInsert(stoi(temp));
    //count ++;
    //if(count == 10) break;
      //  cout << temp2 << endl;
          //LLInsert(stoi(temp2));
    }
}
int main(){
  Hash h1;
  h1.Driver();
  //cout << h1.hashFloor(5221) << endl;//Expected 5

  // h1.printTable(1);
  // // h1.LinearInsert(0);
  // h1.LinearInsert(1018);
  // h1.LinearInsert(1017);
  // h1.LinearInsert(1016);
  // h1.LinearInsert(1019);
  // for(int i =0 ; i < 4; i++){
  //   // cout << i * 1019 << endl;
  //   // h1.LLInsert(i * 1019);
  // }
  // h1.LLInsert(1019*2);
  // h1.LLInsert(1019*5);
  // h1.LLInsert(1019);
  // h1.LLInsert(1018);
  // h1.LLInsert(2 * 1018);
  //
  h1.LLPrint();
//  cout << "Search results:" << h1.LinearSearch1(99325) << endl; //9244

}
