#include <iostream>
#include "node.h"
#include <cstring>
#include <sstream>
#include <fstream>
#include "stdlib.h"

//Ryan Thammakhoune Red Black Tree. Add integers to a binary tree. Assigns red or black to each node. The number of black nodes in each path is the same.

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

void rotateLeft(Node* node) { //Rotate left for case 4
  Node* newNode = node->getRight();
  Node* parent = node->getParent();
  node->setRight(newNode->getLeft());
  newNode->setLeft(node);
  node->setParent(newNode);
  if (node->getRight() != NULL) {
    node->getRight()->setParent(node);
  }
  if (node->getParent() != NULL) {
    if (parent -> getLeft() == node) {
      parent ->setLeft(newNode);
    }
    else if (node->getParent() -> getRight() == node) {
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
  if (node == parent->getRight() && parent == grandparent->getLeft()) {
    rotateLeft(parent);
    node = node->getLeft();
  }
  else if (node == parent->getLeft() && parent == grandparent->getRight()) {
    rotateRight(parent);
    node = node->getRight();
  }
  parent = node->getParent();
  grandparent = node->getParent()->getParent();
  if (node == parent->getLeft()){
    rotateRight(grandparent);
  }
  else {
    rotateLeft(grandparent);
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
      if (head->getRight() != NULL) {
        addFix(head->getRight(), node);
        return;
      }
      else {
        node->setParent(head);
        head->setRight(node);
      }
    }
  }
  else {
    head = node;
    head->setParent(NULL);
    return;
  }
}
