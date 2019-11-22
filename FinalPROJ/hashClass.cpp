#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class Hash{

  public:
    Hash();
    ~Hash();
    int hashMod(int key);
    int hashFloor(int key);
    void printTable(int number);
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

int main(){
  Hash h1;
  //cout << h1.hashFloor(5221) << endl;//Expected 5

  h1.printTable(1);
}
