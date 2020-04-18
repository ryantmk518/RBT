#include <iostream>
#include "node.h"
#include <cstring>
#include <sstream>
#include <fstream>
#include "stdlib.h"

//Ryan Thammakhoune Binary Search Tree. Add integers to a binary tree. Can check if int is in tree. Can remove int from tree. Type Console to keep adding integers to the tree.

using namespace std;

Node* add(Node* head, Node* node); //Initialize functions
void print(Node* head, int space);
void search(Node* head, int num);
void remove(Node* head, Node* first, int num);
Node* twoChild(Node* head);
void fixColor(Node* head, Node* node);
Node* getParent(Node* head, Node* node);
Node* getUncle(Node* head, Node* node);
Node* getGrand(Node* head, Node* node);
Node* getSibling(Node* head, Node* node);
void Case1(Node* head, Node* node);
void Case2(Node* head, Node* node);
void Case3(Node* head, Node* node);
void Case4(Node* head, Node* node);
void rotateRight(Node* head, Node* node);
void rotateLeft(Node* head, Node* node);
void addFix(Node* head, Node* node);

int main(){
  bool quit = false;
  Node* head = NULL; //Head node
  while (quit == false) {
    cout << "Enter Console, File, Search, Remove, or Quit" << endl;
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
      if (head == NULL) { //If tree does not exist
        cout << "New tree" << endl;
        for(int i = 0; i < a; i++) {
          Node* newNode = new Node(array[i]);
          head = add(head, newNode);
        }
      }
      else { //If tree already exists
        for(int i = 0; i < a; i++) {
          Node* newNode = new Node(array[i]);
          head = add(head, newNode);
        }
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
      for (int i = 0; i < a; i++) {
        Node* newNode = new Node(array[i]);
        head = add(head, newNode);
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
      if (getUncle(head, head->getLeft()->getLeft()->getLeft()) != NULL) {
        cout << getUncle(head, head->getLeft()->getLeft()->getLeft()) -> getValue() << endl;
      }
    }
  }
}

void rotateLeft(Node* head, Node* node) {
  Node* newNode = node->getRight();
  node->setRight(newNode->getLeft());
  newNode->setLeft(node);
  node->setParent(newNode);
  if (node->getRight() != NULL) {
    node->getRight()->setParent(node);
  }
  if (getParent(head, node) != NULL) {
    if (getParent(head, node) -> getLeft() == node) {
      getParent(head, node) ->setLeft(newNode);
    }
    else if (getParent(head, node) -> getRight() == node) {
      getParent(head, node) ->setRight(newNode);
    }
  }
  newNode->setParent(getParent(head, node));
}

void rotateRight(Node* head, Node* node) {
  Node* newNode = node->getLeft();
  node->setLeft(newNode->getRight());
  newNode->setRight(node);
  node->setParent(newNode);
  if (node->getLeft() != NULL) {
    node->getLeft()->setParent(node);
  }
  if (getParent(head, node) != NULL) {
    if (getParent(head, node) -> getLeft() == node) {
      getParent(head, node) ->setLeft(newNode);
    }
    else if (getParent(head, node) -> getRight() == node) {
      getParent(head, node) ->setRight(newNode);
    }
  }
  newNode->setParent(getParent(head, node));
}


void Case1(Node* head, Node* node) {
  node->setColor(1);
}

void Case2(Node* head, Node* node) {
  return;
}

void Case3(Node* head, Node* node) {
  getParent(head, node) ->setColor(1);
  getUncle(head, node) ->setColor(1);
  getGrand(head, node) ->setColor(0);
  fixColor(head, getGrand(head, node));
}

void Case4(Node* head, Node* node) {
  if (getParent(head, node) -> getRight() == node && getGrand(head, node)->getRight() == getParent(head, node)) {
    rotateLeft(head, getParent(head, node));
    node = node->getLeft();
  }
  else if (getParent(head, node) -> getLeft() == node && getGrand(head, node)->getLeft() == getParent(head, node)) {
    rotateRight(head, getParent(head, node));
    node = node->getRight();
  }
  if (getParent(head, node) -> getLeft() == node) {
    rotateRight(head, getGrand(head, node));
  }
  else {
    rotateLeft(head, getGrand(head, node));
  }
  getParent(head, node) ->setColor(1);
  getGrand(head, node) -> setColor(0);
}

void remove(Node* head, Node* first, int num) {
  if (head == NULL) { //If tree doesn't exist
    return;
  }
  else if (head->getValue() < num) { //Go right
    if (head->getRight() -> getValue() == num) { //If right is the int we want
      if (head->getRight()->getRight() == NULL && head->getRight()->getLeft() == NULL) { //No child case
        head->setRight(NULL);
      }
      else if (head->getRight()->getLeft() != NULL && head->getRight()->getRight() == NULL) { //One child case
        int newValue = head->getRight()->getLeft()->getValue();
        remove(first, first, newValue);
        head->getRight()->setValue(newValue);
      }
      else if (head->getRight()->getRight() != NULL && head->getRight()->getLeft() == NULL) { //One child case
        int newValue = head->getRight()->getRight()->getValue();
        remove(first, first, newValue);
        head->getRight()->setValue(newValue);
      }
      else if (head->getRight() -> getRight() != NULL && head->getRight()->getLeft() != NULL) { //Two child case
        int newValue = twoChild(head->getRight()->getRight())->getValue();
        remove(first, first, twoChild(head->getRight()->getRight())->getValue());
        head->getRight()->setValue(newValue);
      }
    }
    else {
      remove(head->getRight(), first, num);
    }
  }
  else if (head->getValue() > num) { //Go left
    if (head->getLeft() -> getValue() == num) {
      if (head->getLeft()->getRight() == NULL && head->getLeft()->getLeft() == NULL) { //No child case
        head->setLeft(NULL);
      }
      else if (head->getLeft()->getLeft() != NULL && head->getLeft()->getRight() == NULL) { //One child case
        int newValue = head->getLeft()->getLeft()->getValue();
        remove(first, first, newValue);
        head->getLeft()->setValue(newValue);
      }
      else if (head->getLeft()->getRight() != NULL && head->getLeft()->getLeft() == NULL) { //One child case
        int newValue = head->getLeft()->getRight()->getValue();
        remove(first, first, newValue);
        head->getLeft()->setValue(newValue);
      }
      else if (head->getLeft() -> getRight() != NULL && head->getLeft()->getLeft() != NULL) { //Two child case
        int newValue = twoChild(head->getLeft()->getRight())->getValue();
        remove(first, first, twoChild(head->getLeft()->getRight())->getValue());
        head->getLeft()->setValue(newValue);
      }
    }
    else {
      remove(head->getLeft(), first, num);
    }
  }
  else if (head->getValue() == num) { //If the head is the delete num
    int newValue = head->getRight()->getValue();
    remove(first, first, newValue);
    head->setValue(newValue);
  }
}

void fixColor(Node* head, Node* node) {
  cout << "Fix color" << endl;
  if (node->getParent() == NULL) {
    cout << "Parent is null" << endl;
    Case1(head, node);
  }
  else if (node->getParent() ->getColor() == 1) {
    Case2(head, node);
  }
  else if (getUncle(head, node) != NULL && getUncle(head, node) -> getColor() == 0) {
    Case3(head, node);
  }
  else {
    Case4(head, node);
  }
}


Node* getParent(Node* head, Node* node) {
  return node->getParent();
}

Node* getSibling(Node* head, Node* node) {
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

Node* getUncle(Node* head, Node* node) {
  return getSibling(head, getParent(head, node));
}

Node* getGrand(Node* head, Node* node) {
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

Node* add(Node* head, Node* node) {
  cout << "begin add" << endl;
  Node* root = head;
  addFix(head, node);
  fixColor(head, node);
  head = node;
  while (getParent(root, head) != NULL) {
    head = getParent(root, head);
  }
  return head;
}

void addFix(Node* head, Node* node) {
  cout << "Adding" << endl;
  if (head != NULL) {
    cout << "Is not head" << endl;
    if (node->getValue() < head->getValue()) {
      if (head->getLeft() != NULL) {
        add(head->getLeft(), node);
        return;
      }
      else {
        head->setLeft(node);
      }
    }
    else {
      if (head->getRight() != NULL) {
        add(head->getRight(), node);
        return;
      }
      else {
        head->setRight(node);
      }
    }
  }
  node->setParent(head);
}
