#include <iostream>
#include "node.h"

using namespace std;

//Node class

Node::Node(int newvalue) { //Create node
  value = newvalue;
  right = NULL;
  left = NULL;
  color = 0;
}

Node::~Node() { //Delete node
  value = NULL;
}

void Node::setValue(int newvalue) { //Set value
  value = newvalue;
}

int Node::getValue() { //Returns value
  return value;
}

Node* Node::getRight() { //Right node
  return right;
}

Node* Node::getLeft() { //Left node
  return left;
}

void Node::setRight(Node* newRight) { //Set right node
  right = newRight;
}

void Node::setLeft(Node* newLeft) { //Set left node
  left = newLeft;
}

void Node::setColor(int newColor) {
  color = newColor;
}

int Node::getColor() {
  return color;
}
