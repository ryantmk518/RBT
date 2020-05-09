#include <iostream>
#include "node.h"
#include <cstring>
#include <sstream>
#include <fstream>
#include "stdlib.h"

//Ryan Thammakhoune Red Black Tree. Add integers to a binary tree. Assigns red or black to each node. The number of black nodes in each path is the same.

//With help from Wikipedia page for Red Black Tree
using namespace std;

Node* add(Node* &head, Node* root, Node* node); //Initialize functions
void print(Node* head, int space);
void search(Node* head, int num);
Node* twoChild(Node* head);
void fixColor(Node* &head, Node* node);
Node* getParent(Node* head, Node* node);
Node* getUncle(Node* head, Node* node);
Node* getGrand(Node* head, Node* node);
Node* getSibling(Node* head, Node* node);
void Case1(Node* &head, Node* node);
void Case2(Node* &head, Node* node);
void Case3(Node* &head, Node* node);
void Case4(Node* &head, Node* node);
void rotateRight(Node* node);
void rotateLeft(Node* node);
void addFix(Node* head, Node* node);
Node* fixHead (Node* node);
Node* remove(Node* head, int num);
void removeOne(Node* head, Node* node);
void replace(Node* node, Node* child);
void Rm1(Node* head, Node* node);
void Rm2(Node* head, Node* node);
void Rm3(Node* head, Node* node);
void Rm4(Node* head, Node* node);
void Rm5(Node* head, Node* node);
void Rm6(Node* head, Node* node);

int main(){
  bool quit = false;
  Node* head = NULL; //Head node
  while (quit == false) {
    cout << "Enter Console, File, or Quit" << endl;
    char input[99];
    cin.getline(input, 99);
    if (strcmp(input, "Console") == 0) { //Enter through console
      cout << "Enter input separated by spaces" << endl;
      char in[999];
      cin.getline(in, 999);
      int* array = new int[999];
      int a = 0;
      char* token = strtok(in, " ");
      while (token != NULL) { //Split the input
        array[a] = atoi(token);
        token = strtok(NULL, " ");
        ++a;
      }
      for(int i = 0; i < a; i++) {
        Node* newNode = new Node(array[i]);
        head = add(head, head, newNode);
      }
      print(head, 0); //Print the tree
      cout << "\n";
    }
    else if (strcmp(input, "File") == 0) { //Enter through file
      cout << "Enter file name" << endl;
      char fname[99];
      cin.getline(fname, 99);
      ifstream file;
      file.open(fname);
      char* output = new char[999];
      int* array = new int[999];
      int i = 0;
      while (!file.eof()) { //While not end of file, get char
        file.get(output[i]);
        i++;
      }
      char* split = strtok(output, " ");
      int a = 0;
      while (split!=NULL) { //Split the char array
        array[a] = atoi(split);
        split = strtok(NULL, " ");
        ++a;
      }
      cout << a << endl;
      for(int i = 0; i < a; i++) {
        cout << array[i] << endl;
        Node* newNode = new Node(array[i]);
        head = add(head, head, newNode);
      }
      print(head, 0);
      cout << "\n";
    }
    else if (strcmp(input, "Search") == 0) { //Search
      char input[99];
      cout << "Enter search integer" << endl;
      cin.getline(input, 99);
      int num = atoi(input); //Gets num
      search(head, num);
    }
    /*
    else if (strcmp(input, "Remove") == 0) { //Remove
      char input[99];
      cout << "Enter integer to remove" << endl;
      cin.getline(input, 99);
      cout << "\n" << endl;
      int num = atoi(input);
      remove(head, head, num);
      print(head, 0);
      }*/
    else if (strcmp(input, "Quit") == 0) { //Quit
      quit = true;
      return 0;
    }
    else if (strcmp(input, "Test") == 0) {
      
    }
  }
}

void replace(Node* node, Node* child) {
  child->setParent(node->getParent());
  if (node == node->getParent()->getLeft()) {
    node->getParent()->setLeft(child);
  }
  else {
    node->getParent()->setRight(child);
  }
}

void removeOne(Node* head, Node* node) {
  Node* child = new Node(NULL);
  if (node->getLeft() != NULL) {
    child = node->getLeft();
  }
  else {
    child = node->getRight();
  }
  replace(node, child);
  if (node->getColor() == 1) {
    if (child->getColor() == 0) {
      child->setColor(1);
    }
    else {
      Rm1(head, child);
    }
  }
}

Node* remove(Node* head, int num) {
  if (head == NULL) {
    return NULL;
  }
  else if (head->getValue() == num) {
    return head;
  }
  else{
    if (head->getRight() != NULL) {
      return remove(head->getRight(), num);
    }
    if (head->getLeft() != NULL) {
      return remove(head->getLeft(), num);
    }
  }
}

void Rm1(Node* head, Node* node) {
  if (node->getParent() != NULL) {
    Rm2(head, node);
  }
}

void Rm2(Node* head, Node* node) {
  Node* sibling = getSibling(head, node);
  if (sibling->getColor() == 0) {
    node->getParent()->setColor(0);
    sibling->setColor(1);
    if (node == node->getParent()->getLeft()) {
      rotateLeft(node->getParent());
    }
    else {
      rotateRight(node->getParent());
    }
  }
  Rm3(head, node);
}

void Rm3(Node* head, Node* node) {
  Node* sibling = getSibling(head, node);
  if (node->getParent()->getColor()==1 && sibling->getColor() == 1 && sibling->getLeft()->getColor() == 1 && sibling->getRight()->getColor() == 1) {
    sibling->setColor(0);
    Rm1(head, node->getParent());
  }
  else {
    Rm4(head, node);
  }
}

void Rm4(Node* head, Node* node) {
  Node* sibling = getSibling(head, node);
  if (node->getParent()->getColor()==0 && sibling->getColor() == 1 && sibling->getLeft()->getColor() == 1 && sibling->getRight()->getColor() == 1) {
    sibling->setColor(0);
    node->getParent()->setColor(1);
  }
  else {
    Rm5(head, node);
  }
}

void Rm5(Node* head, Node* node) {
  Node* sibling = getSibling(head, node);
  if (sibling->getColor() == 1) {
    if (node == node->getParent()->getLeft() && sibling->getRight()->getColor() == 1 && sibling->getLeft()->getColor() == 0) {
      sibling->setColor(0);
      sibling->getLeft()->setColor(1);
    }
    else if (node == node->getParent()->getRight() && sibling->getLeft()->getColor()==1 && sibling->getRight()->getColor() == 0) {
      sibling -> setColor(0);
      sibling->getRight()->setColor(1);
      rotateLeft(sibling);
    }
  }
  Rm6(head, node);
}

void Rm6 (Node* head, Node* node) {
  Node* sibling = getSibling(head, node);
  sibling->setColor(node->getParent()->getColor());
  node->getParent()->setColor(1);
  if (node == node->getParent()->getLeft()) {
    sibling->getRight()->setColor(1);
    rotateLeft(node->getParent());
  }
  else {
    sibling->getLeft()->setColor(1);
    rotateRight(node->getParent());
  }
}

void rotateLeft(Node* node) { //Rotate left for case 4
  Node* newNode = node->getRight();
  Node* parent = node->getParent();
  node->setRight(newNode->getLeft());
  newNode->setLeft(node);
  node->setParent(newNode);
  cout << "All set" << endl;
  if (node->getRight() != NULL) {
    cout << "right is not null" << endl;
    node->getRight()->setParent(node);
  }
  if (parent != NULL) {
    cout << "Parent is not null" << endl;
    if (parent -> getLeft() == node) {
      cout << "is left" << endl;
      parent ->setLeft(newNode);
    }
    else if (parent -> getRight() == node) {
      cout << "is on right" << endl;
      parent ->setRight(newNode);
    }
  }
  newNode->setParent(parent);
}

void rotateRight(Node* node) { //Rotate tree right for case 4
  Node* newNode = node->getLeft();
  Node* parent = node->getParent();
  node->setLeft(newNode->getRight());
  newNode->setRight(node);
  node->setParent(newNode);
  if (node->getLeft() != NULL) {
    node->getLeft()->setParent(node);
  }
  if (parent != NULL) {
    if (parent -> getLeft() == node) {
      parent ->setLeft(newNode);
    }
    else if (node->getParent() -> getRight() == node) {
      parent ->setRight(newNode);
    }
  }
  newNode->setParent(parent);
}


void Case1(Node* &head, Node* node) {
  node->setColor(1);
}

void Case2(Node* &head, Node* node) {
  return;
}

void Case3(Node* &head, Node* node) {
  getParent(head, node) ->setColor(1);
  getUncle(head, node) ->setColor(1);
  getGrand(head, node) ->setColor(0);
  fixColor(head, getGrand(head, node));
}

void Case4(Node* &head, Node* node) {
  Node* parent = node->getParent();
  Node* grandparent = node->getParent()->getParent();
  cout << "Set vars" << endl;
  if (node == parent->getRight() && parent == grandparent->getLeft()) {
    cout << "Rotating Left" << endl;
    rotateLeft(parent);
    cout << "Rotated left" << endl;
    node = node->getLeft();
  }
  else if (node == parent->getLeft() && parent == grandparent->getRight()) {
    cout << "Rotating Right" << endl;
    rotateRight(parent);
    cout << "Rotated right" << endl;
    node = node->getRight();
  }
  parent = node->getParent();
  grandparent = node->getParent()->getParent();
  if (node == parent->getLeft()){
    cout << "Rotating Right" << endl;
    rotateRight(grandparent);
    cout << "Rotated right" << endl;
  }
  else {
    cout << "Rotating Left" << endl;
    rotateLeft(grandparent);
    cout << "Rotated left" << endl;
  }
  if (head == grandparent) {
    head = parent;
  }
  parent->setColor(0);
  grandparent->setColor(1);
}



void fixColor(Node* &head, Node* node) {
  if (node->getParent() == NULL) { //If parent is null
    Case1(head, node);
  }
  else if (node->getParent() ->getColor() == 1) { //If parent is black
    Case2(head, node);
  }
  else if (getUncle(head, node) != NULL && getUncle(head, node) -> getColor() == 0) { //If uncle red
    Case3(head, node);
  }
  else { //All other cases
    Case4(head, node);
  }
  cout << "Color fixed" << endl;
}


Node* getParent(Node* head, Node* node) { //Return parent
  return node->getParent();
}

Node* getSibling(Node* head, Node* node) { //Return sibling
  if (getParent(head, node) == NULL) {
    return NULL;
  }
  if (getParent(head, node) -> getLeft() == node) {
    return getParent(head, node) -> getRight();
  }
  else {
    return getParent(head, node) -> getLeft();
  }
}

Node* getUncle(Node* head, Node* node) { //Return uncle
  return getSibling(head, getParent(head, node));
}

Node* getGrand(Node* head, Node* node) { //Return grandparent
  return getParent(head, getParent(head, node));
}

Node* twoChild(Node* head) { //Goes all the way left until null
  if (head->getLeft() != NULL) {
    twoChild(head->getLeft());
  }
  else {
    return head;
  }
}

void search(Node* head, int num) { //Search
  if (head == NULL) { //Cannot find it
    cout << "Not found" << endl;
  }
  else if (head->getValue() == num) { //If it is found
    cout << "Int is found" << "\n" << endl;
  }
  else if (head->getValue() < num) { //Search right
    search(head->getRight(), num);
  }
  else if (head->getValue() > num) { //Search left
    search(head->getLeft(), num);
  }
}

void print(Node* head, int space){ //Print
  if (head == NULL){ //If tree is empty
    return;
  }
  space += 5; //Amount of spaces
  print(head->getRight(), space);
  cout << "\n";
  for (int i = 5; i < space; i++){ //Prints spaces
    cout << " ";
  }
  cout << head->getValue();
  if (head->getColor() == 0) {
    cout << " R" << endl;
  }
  else if (head->getColor() == 1) {
    cout << " B" << endl;
  }
  print(head->getLeft(), space);
}

Node* add(Node* &head, Node* root, Node* node) {
  addFix(head, node);
  fixColor(head, node);
  return fixHead(node);
}

Node* fixHead(Node* node) {
  if (node->getParent() == NULL) {
    return node;
  }
  else {
    return fixHead(node->getParent());
  }
}

void addFix(Node* head, Node* node) {
  if (head != NULL) { //If there is already a tree
    if (node->getValue() < head->getValue()) {
      cout << "Go left" << endl;
      if (head->getLeft() != NULL) {
        addFix(head->getLeft(), node);
        return;
      }
      else {
        node->setParent(head);
        head->setLeft(node);
      }
    }
    else {
      cout << "Go right" << endl;
      if (head->getRight() != NULL) {
        addFix(head->getRight(), node);
        return;
      }
      else {
        node->setParent(head);
        head->setRight(node);
        cout << "Set right" << endl;
      }
    }
  }
  else {
    head = node;
    head->setParent(NULL);
    return;
  }
}
