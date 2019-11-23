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
class Hash{

  public:
    Hash();
    ~Hash();
    int hashMod(int key);
    int hashFloor(int key);
    void printTable(int number);
    void testInsert(int key);
    bool table1Linear(int index, int key);
    bool table2Linear(int index, int key);
  private:
    static const int TABLE_SIZE = 1019;
    int hashTable1[TABLE_SIZE];
    int hashTable2[TABLE_SIZE];

};
Hash::Hash(){
  for(int i = 0; i < TABLE_SIZE; i++){
  hashTable2[i] = hashTable1[i] = -1;
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
        cout << i << " : " << hashTable1[i] << endl;

      }
      return;
    }
    for(int p = 0; p < TABLE_SIZE; p++){ //print table 2
      cout << hashTable2[p] << " ";
    }
return ;
}
bool Hash::table1Linear(int index, int key){
    for(int i = index+1; i < TABLE_SIZE; i++){
        if(hashTable1[i] == -1){ //If empty index
            hashTable1[i] = key; //Place new data
            return true;
        }
      }
      for(int p = 0; p < index; p++){ //After end of table is reached check from begging to index for open slot
          if(hashTable1[p] == -1){
            hashTable1[p] = key;
            return true;
          }
      }
    return false; //If table full
}
bool Hash::table2Linear(int index, int key){
  for(int i = index+1; i < TABLE_SIZE; i++){
      if(hashTable2[i] == -1){ //If empty index
          hashTable2[i] = key; //Place new data
          return true;
      }
    }
    for(int p = 0; p < index; p++){ //After end of table is reached check from begging to index for open slot
        if(hashTable2[p] == -1){
          hashTable2[p] = key;
          return true;
        }
    }
  return false; //If table full
}

void Hash::testInsert(int key){
  int index = hashMod(key);
  if(hashTable1[index] == -1)
    hashTable1[index] = key;
  else
    table1Linear(index, key);



}

int main(){
  Hash h1;
  //cout << h1.hashFloor(5221) << endl;//Expected 5

  // h1.printTable(1);
  // // h1.testInsert(0);
  // h1.testInsert(1018);
  // h1.testInsert(1017);
  // h1.testInsert(1016);
  // h1.testInsert(1019);
  for(int i =0 ; i < 4; i++){
    // cout << i * 1019 << endl;
    h1.testInsert(i * 1017);
  }
  h1.testInsert(1018);
  h1.testInsert(2 * 1018);
  h1.printTable(1);
}
