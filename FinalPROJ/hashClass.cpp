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
  private:
    int TABLE_SIZE;



};
Hash::Hash(){
  TABLE_SIZE = 1019; //Project Writeup
  //cout << TABLE_SIZE << endl;
}
Hash::~Hash(){

}
int Hash::hashMod(int key){
  return key % TABLE_SIZE;
}
int Hash::hashFloor(int key){
  return key/TABLE_SIZE; //Uneven int division just returns floor
}

int main(){
  Hash h1;
  cout << h1.hashFloor(5221) << endl;//Expected 5
}
