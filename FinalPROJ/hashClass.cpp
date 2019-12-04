#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "hash.hpp"
using namespace std;
Hash::Hash(){
  for(int i = 0; i < TABLE_SIZE; i++){
  hashTable2[i].linearData = hashTable1[i].linearData = -1;
  // hashTable2[i].root = hashTable2[i].root = NULL;
  hashTable2[i].head = hashTable1[i].head = NULL;
  }
  cuckooSize = TABLE_SIZE;
  cout << "TABLE_SIZE: " << cuckooSize << endl;
  itemsInserted = 0;
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
    table2Linear(index, key); //collision
}
void Hash::LinearDelete1(int key){
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
/////////////////////////////////////////////////////Linked list func below
void Hash::LLInsert1(int key){
     int index = hashMod(key);
     LLNode* temp = new LLNode;
     if(hashTable1[index].head == NULL){
        temp->key = key; //Create LL if needed
        temp->next = NULL;
        hashTable1[index].head = temp;
     }
     else{
       LLCollision1(key); //chain already existing LL
     }

}
void Hash::LLInsert2(int key){
     int index = hashFloor(key);
     LLNode* temp = new LLNode;
     if(hashTable2[index].head == NULL){
        temp->key = key;
        temp->next = NULL;
        hashTable1[index].head = temp;
     }
     else{// if head is not null use chain
       LLCollision2(key);
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
void Hash::LLCollision1(int key){
     int index = hashMod(key);
     LLNode* head = hashTable1[index].head;
     LLNode* temp = new LLNode; //Create new node and initalize
     temp->key = key;
       temp->next = head; //iNSERT new info at the front of the list
       hashTable1[index].head = temp;
       return;
}
void Hash::LLCollision2(int key){
     int index = hashMod(key);
     LLNode* head = hashTable2[index].head;
     LLNode* temp = new LLNode; //Create new node and initalize
     temp->key = key;
       temp->next = head; //iNSERT new info at the front of the list
       hashTable1[index].head = temp;
       return;
}
void Hash::LLDelete1(int key)

{

  int index = hashMod(key);

  LLNode* temp = hashTable1[index].head;;

  LLNode* prev;

  // temp = hashTable1[index].head;



  if (temp != NULL && temp->key == key)

  {

    hashTable1[index].head = temp->next;

    delete temp;

    return;

  }



  while (temp != NULL && temp->key != key)

  {

    prev = temp;

    temp = temp->next;

  }



  prev->next = temp->next;

  delete temp;

}
void Hash::LLDelete2(int key)

{

  int index = hashFloor(key);

  LLNode* temp = hashTable2[index].head;

  LLNode* prev;

  // temp = hashTable1[index].head;



  if (temp != NULL && temp->key == key)

  {

    hashTable1[index].head = temp->next;

    delete temp;

    return;

  }



  while (temp != NULL && temp->key != key)

  {

    prev = temp;

    temp = temp->next;

  }



  prev->next = temp->next;

  delete temp;

}
bool Hash::LLSearch1(int key)

{

  int index = hashMod(key);

  LLNode* temp = hashTable1[index].head;

  // temp = hashTable1[index].head;

  while (temp != NULL)

  {

    if (temp->key = key)

    {

      return temp;

    }

    temp = temp->next;



  }



}
bool Hash::LLSearch2(int key)

{

  int index = hashFloor(key);

  LLNode* temp = hashTable2[index].head;

  // temp = hashTable1[index].head;

  while (temp != NULL)

  {

    if (temp->key = key)

    {

      return temp;

    }

    temp = temp->next;



  }



}
/////////////////////////////////////////////////////Tree func below

TreeNode* Hash::newTreeNode(int key){
  TreeNode* rv = new TreeNode;
  rv->key = key;
  rv->left = rv->right = NULL;
  return rv;
}
TreeNode* Hash::insertTree1(int key){
  int index = hashMod(key);
  if(hashTable1[index].root == NULL){
    hashTable1[index].root = newTreeNode(key);
  }
  else{
    TreeCollision(hashTable1[index].root, key);
  }
}
TreeNode* Hash::insertTree2(int key){
  int index = hashMod(key);
  if(hashTable2[index].root == NULL){
    hashTable2[index].root = newTreeNode(key);
  }
  else{
    TreeCollision(hashTable2[index].root, key);
  }
}
void Hash::printTree1(){ //for printing all the tree of hashTable1
  for(int i = 0; i < TABLE_SIZE; i++){
    cout << i << " " ;
    if(hashTable1[i].root){
    inOrder(hashTable1[i].root);
    }
    cout << endl;
  }
}
void Hash::printTree2(){//Table 2's print function
  for(int i = 0; i < TABLE_SIZE; i++){
    cout << i << " " ;
    if(hashTable2[i].root){
    inOrder(hashTable2[i].root); //Standard inorder least to greatest printing
    }
    cout << endl;
  }
}
TreeNode* Hash::TreeCollision(TreeNode* root, int key){
  if(root == NULL) return newTreeNode(key);
  if(root->key > key){
    root->left = TreeCollision(root->left, key);
  }
  if(root->key < key){
    root->right = TreeCollision(root->right, key);
  }
  return root;
}
void Hash::inOrder(TreeNode* root){ //Tree printing helper
  if(root == NULL) return; //LEFT ROOT RIGHT
  inOrder(root->left);
  cout << root->key << " ";
  inOrder(root->right);
}
bool Hash::TreeSearch1(int key){
  int index = hashMod(key);
  TreeNode* temp = hashTable1[index].root;
  TreeNode* rv = treeSearchHelper(temp, key);
  if(rv) return true;
  return false;
}

bool Hash::TreeSearch2(int key){
  int index = hashFloor(key);
  TreeNode* temp = hashTable2[index].root;
  TreeNode* rv = treeSearchHelper(temp, key);
  if(rv) return true;
  return false;
}

////use to recursivley search tree
TreeNode* Hash::treeSearchHelper(TreeNode* root, int key){
  if(root == NULL || root->key == key) return root; //Base case
  if(root->key > key){
      return treeSearchHelper(root->left, key);
  }     //If root key is greater than search key search left
  return treeSearchHelper(root->right, key); //else search right
}


TreeNode* Hash::minValueNode(TreeNode* node)

{

    TreeNode* current = node;
    /* loop down to find the leftmost leaf */

    while (current && current->left != NULL)

        current = current->left;



    return current;

}


bool Hash::deleteNode(int key){
  int index = hashMod(key);
  TreeNode* check = hashTable1[index].root;
  deleteNodeHelper(hashTable1[index].root, key);
  return true;
}
TreeNode* Hash::deleteNodeHelper(TreeNode* temp, int key)

{


  // cout << temp->key << endl;
  //
  // cout << key << endl;

  if (key < temp->key)

  {

    temp->left = deleteNodeHelper(temp->left, key);

  }

  else if (key > temp->key)

  {

    temp->right = deleteNodeHelper(temp->right, key);

  }

  else

  {



      if (temp->left == NULL)

      {

          TreeNode *temp1 = temp->right;

          delete temp;

          return temp1;

      }

      else if (temp->right == NULL)

      {

          TreeNode *temp1 = temp->left;

          delete temp;

          return temp1;

      }

      TreeNode* temp1 = minValueNode(temp->right);

      temp->key = temp1->key;

      temp->right = deleteNodeHelper(temp->right, temp->key);

}

return temp;

}
/////////////////////////////////////////////////////////////cuckoo fncs below
void Hash::cuckooHelper(int key, int tableNum,  int count, int size, int cuckooTable1[], int cuckooTable2[]){
  if(count == size) return; //supposed to
  int indexs[2];
  indexs[0] = cuckooHash1(key);
  indexs[1] = cuckooHash2(key);
  int temp = -1;
  if(tableNum%2 == 0){
    //cout << "table 1";
    if(cuckooTable1[indexs[0]] != -1){
        temp = cuckooTable1[indexs[0]];
        cuckooTable1[indexs[0]] = key;
        cuckooHelper(temp,tableNum+1, count+1, size, cuckooTable1, cuckooTable2);
      }
      else{
        cuckooTable1[indexs[0]] = key;
      }
  }
  else{
    if(cuckooTable2[indexs[1]] != -1){
      temp = cuckooTable1[indexs[0]];
      cuckooTable1[indexs[0]] = key;
      cuckooHelper(temp, tableNum+1, count+1, size, cuckooTable1, cuckooTable2);
    }
    else{
      cuckooTable2[indexs[0]] = key; //insert
    }
  }
}
void Hash::cuckooDriver(){
  int cuckooTable1[cuckooSize];
  int cuckooTable2[cuckooSize];
  for(int i = 0; i < cuckooSize;i++){
    cuckooTable1[i] = cuckooTable2[i] = -1;
  }
  fstream f;
  string temp;
  f.open("dataSetC.csv");
  while(getline(f, temp, ',')){
    cuckooHelper(stoi(temp), 0, 0, cuckooSize, cuckooTable1, cuckooTable2);
  }
  cuckooDelete(46471786, cuckooTable1, cuckooTable2);
  cuckooPrint(cuckooTable1, cuckooTable2);

}
int Hash::cuckooHash1(int key){
  return key % cuckooSize;
}
void Hash::reHash(){
  cuckooSize++;
  cuckooDriver();
}
int Hash::cuckooHash2(int key){
  return key/cuckooSize;
}
void Hash::cuckooPrint(int arr[], int arr2[]){
  cout << "Table 1: " << endl;
  for(int i = 0; i < cuckooSize; i++){
    cout << i << ": " << arr[i]<< endl;
  }
  cout << "Table 2: " << endl;
  for(int i = 0; i < cuckooSize; i++){
    cout << i << ": " << arr2[i]<< endl;
  }
}
void Hash::Driver(){
    int temp2[10009];
    int count = 0;
    fstream f;
    string temp;
      f.open("dataSetA.csv");
    while(getline(f, temp, ',')){
      //cout << temp << endl;
    temp2[count] = stoi(temp);
    count++;
    //cout << count << endl;
    if(count == 10009) break;
    }
    time(temp2);
    return;

  // deleteNode(28145303);
  // deleteNode(71884633);
  // deleteNode(6996286);

}
float Hash::loadFactor(){
  return (float) itemsInserted/TABLE_SIZE;
}
bool Hash::cuckooSearch(int key, int arr1[], int arr2[]){
  int index1 = cuckooHash1(key);
  int index2 = cuckooHash2(key);

  if(arr1[index1] == key || arr2[index1] == key || arr2[index2] == key || arr1[index2] == key ){
    return true; //if key is matching in either of tables search is successful
  }
   return false; //else item has not been found
}
bool Hash::cuckooDelete(int key, int arr1[], int arr2[]){
  int index1 = cuckooHash1(key);
  int index2 = cuckooHash2(key);
  if(arr1[index1] == key){ //Check both loactions for key and replace with -1
    arr1[index1] = -1;
    return true;
  }
  if(arr2[index2] == key){
    arr2[index2] = -1;
    return true;
  }
  if(arr2[index1] == key){
    arr2[index1] = -1;
    return true;
  }
  if(arr1[index2] == key){
    arr1[index2] = -1;
    return true;
  }
  return false;
}

void Hash::time(int arr[]){
int count = 0;
string temp;
double totalTime = 0.0;
// cout << "yes";
int startTime, endTime;
double execTime;
cout << endl << "Preformance analysis of Linear probing table 1 function 1: " << endl << endl;
startTime = clock();
  while(true){
    //cout << "temp";
  LinearInsert1(arr[count]);
  count++;
  itemsInserted++;
  if(loadFactor() >= .1){
    break;
  }
  }
  for(int i = count; i < count+100; i++){
    //cout << "yes";
    LinearInsert1(arr[count]);
  }
  for(int i = count; i < count+100; i++){
    //cout << "yes";
    LinearSearch1(arr[count]);
  }
  for(int i = count; i < count+100; i++){
    //cout << "yes";
    LinearDelete1(arr[count]);
  }
endTime = clock();
execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
cout << "load factor: " << loadFactor() << endl;
cout << "execution time: " << execTime << endl;
cout << "Average time per operation: " << (double)execTime/300 << endl;

//////////////////////////////////////////////////////////
while(true){
  //cout << "temp";
LinearInsert1(arr[count]);
count++;
itemsInserted++;
if(loadFactor() >= .2){
  break;
}
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearInsert1(arr[count]);
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearSearch1(arr[count]);
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearDelete1(arr[count]);
}
endTime = clock();
execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
cout << "load factor: " << loadFactor() << endl;
cout << "execution time: " << execTime << endl;
cout << "Average time per operation: " << (double)execTime/300 << endl;

//////////////////////////////////////////////////////////////////////////////////
while(true){
  //cout << "temp";
LinearInsert1(arr[count]);
count++;
itemsInserted++;
if(loadFactor() >= .5){
  break;
}
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearInsert1(arr[count]);
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearSearch1(arr[count]);
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearDelete1(arr[count]);
}
endTime = clock();
execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
cout << "load factor: " << loadFactor() << endl;
cout << "execution time: " << execTime << endl;
cout << "Average time per operation: " << (double)execTime/300 << endl;

///////////////////////////////////////////////////////////////////////////////////
while(true){
  //cout << "temp";
LinearInsert1(arr[count]);
count++;
itemsInserted++;
if(loadFactor() >= .7){
  break;
}
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearInsert1(arr[count]);
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearSearch1(arr[count]);
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearDelete1(arr[count]);
}
endTime = clock();
execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
cout << "load factor: " << loadFactor() << endl;
cout << "execution time: " << execTime << endl;
cout << "Average time per operation: " << (double)execTime/300 << endl;

//  h1.LLPrint();
///////////////////////////////////////////////////////////////////////
while(true){
  //cout << "temp";
LinearInsert1(arr[count]);
count++;
itemsInserted++;
if(loadFactor() >= .9){
  break;
}
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearInsert1(arr[count]);
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearSearch1(arr[count]);
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearDelete1(arr[count]);
}
endTime = clock();
execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
cout << "load factor: " << loadFactor() << endl;
cout << "execution time: " << execTime << endl;
cout << "Average time per operation: " << (double)execTime/300 << endl;

/////////////////////////////////////////////////////////////////////////////
while(true){
  //cout << "temp";
LinearInsert1(arr[count]);
count++;
itemsInserted++;
if(loadFactor() >= 1){
  break;
}
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearInsert1(arr[count]);
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearSearch1(arr[count]);
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearDelete1(arr[count]);
}
endTime = clock();
execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
cout << "load factor: " << loadFactor() << endl;
cout << "execution time: " << execTime << endl;
cout << "Average time per operation: " << (double)execTime/300 << endl;

cout << endl << "Preformance analysis of Linear probing table 2 function 2: " << endl << endl;
itemsInserted = 0;  //reset itemsInserted and count to reset loadFactor and insertion index
count = 0;
// cout << "yes";
startTime = clock();
  while(true){
    //cout << "temp";
  LinearInsert2(arr[count]);
  count++;
  itemsInserted++;
  if(loadFactor() >= .1){
    break;
  }
  }
  for(int i = count; i < count+100; i++){
    //cout << "yes";
    LinearInsert2(arr[count]);
  }
  for(int i = count; i < count+100; i++){
    //cout << "yes";
    LinearSearch2(arr[count]);
  }
  for(int i = count; i < count+100; i++){
    //cout << "yes";
    LinearDelete2(arr[count]);
  }
endTime = clock();
execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
cout << "load factor: " << loadFactor() << endl;
cout << "execution time: " << execTime << endl;
cout << "Average time per operation: " << (double)execTime/300 << endl;

//////////////////////////////////////////////////////////
while(true){
  //cout << "temp";
LinearInsert2(arr[count]);
count++;
itemsInserted++;
if(loadFactor() >= .2){
  break;
}
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearInsert2(arr[count]);
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearSearch2(arr[count]);
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearDelete2(arr[count]);
}
endTime = clock();
execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
cout << "load factor: " << loadFactor() << endl;
cout << "execution time: " << execTime << endl;
cout << "Average time per operation: " << (double)execTime/300 << endl;

//////////////////////////////////////////////////////////////////////////////////
while(true){
  //cout << "temp";
LinearInsert2(arr[count]);
count++;
itemsInserted++;
if(loadFactor() >= .5){
  break;
}
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearInsert2(arr[count]);
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearSearch2(arr[count]);
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearDelete2(arr[count]);
}
endTime = clock();
execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
cout << "load factor: " << loadFactor() << endl;
cout << "execution time: " << execTime << endl;
cout << "Average time per operation: " << (double)execTime/300 << endl;

///////////////////////////////////////////////////////////////////////////////////
while(true){
  //cout << "temp";
LinearInsert2(arr[count]);
count++;
itemsInserted++;
if(loadFactor() >= .7){
  break;
}
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearInsert2(arr[count]);
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearSearch2(arr[count]);
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearDelete2(arr[count]);
}
endTime = clock();
execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
cout << "load factor: " << loadFactor() << endl;
cout << "execution time: " << execTime << endl;
cout << "Average time per operation: " << (double)execTime/300 << endl;

//  h1.LLPrint();
///////////////////////////////////////////////////////////////////////
while(true){
  //cout << "temp";
LinearInsert2(arr[count]);
count++;
itemsInserted++;
if(loadFactor() >= .9){
  break;
}
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearInsert2(arr[count]);
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearSearch2(arr[count]);
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearDelete2(arr[count]);
}
endTime = clock();
execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
cout << "load factor: " << loadFactor() << endl;
cout << "execution time: " << execTime << endl;
cout << "Average time per operation: " << (double)execTime/300 << endl;

/////////////////////////////////////////////////////////////////////////////
while(true){
  //cout << "temp";
LinearInsert2(arr[count]);
count++;
itemsInserted++;
if(loadFactor() >= 1){
  break;
}
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearInsert2(arr[count]);
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearSearch2(arr[count]);
}
for(int i = count; i < count+100; i++){
  //cout << "yes";
  LinearDelete2(arr[count]);
}
endTime = clock();
execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
cout << "load factor: " << loadFactor() << endl;
cout << "execution time: " << execTime << endl;
cout << "Average time per operation: " << (double)execTime/300 << endl;

}

int main(){
  Hash h1;
  h1.Driver();
}
