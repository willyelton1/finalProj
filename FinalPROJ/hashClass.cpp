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
    for(int i = index; i < TABLE_SIZE; i++){
      if(hashTable1[i] == -1) //If empty index
      hashTable1table[i] = key; //Place new data
      return true;
    }
    return false; //If table full
}
bool Hash::table2Linear(int index, int key){ 
  for(int i = index; i < TABLE_SIZE; i++){
    if(hashTable2[i] == -1) //If empty index
    hashTable2[i] = key; //Place new data
    return true;
  }
  return false; //If table full
}
}

int main(){
  Hash h1;
  //cout << h1.hashFloor(5221) << endl;//Expected 5

  h1.printTable(1);
}
