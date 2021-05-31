//Node cpp file

#include <cstdlib>
#include "Node.h"


//constructor
Node::Node() {
	left = NULL;
	right = NULL;
	data = 0;
	parent = NULL;
	sibling = NULL;
	color = 1; //0 means black and 1 means red
}




//return left
Node* Node::getLeft() {
	return left;
}

//return right
Node* Node::getRight() {
	return right;
} 

//return data
int Node::getData() {
	return data;
} 

//return parent
Node* Node::getParent() {
	return parent;
} 

//return color
int Node::getColor() {
	return color;
}

//return sibling
Node* Node::getSibling() {
	return sibling;
}





//set left
void Node::setLeft(Node* n) {
	left = n;
}

//set right
void Node::setRight(Node* n) {
	right = n;
}

//set data
void Node::setData(int d) {
	data = d;
}

//set parent
void Node::setParent(Node* p) {
	parent = p;
}

//set sibling
void Node::setSibling(Node* s) {
	sibling = s;
}

//set color
void Node::setColor(int c) {
	color = c;
}

