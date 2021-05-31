//Node header file

//include guards
#ifndef NODE_H
#define NODE_H


class Node {

public:
	Node(); //constructor
	//~Node(); //destructor
	Node* getLeft(); //getter
	Node* getRight(); //getter
	int getData(); //getter
	Node* getParent(); //getter
	int getColor(); //getter
	Node* getSibling(); //getter
	void setLeft(Node* n); //setter
	void setRight(Node* n); //setter
	void setData(int d); //setter
	void setParent(Node* p); //setter
	void setColor(int c); //setter
	void setSibling(Node* s); //setter
private:
	Node* left;
	Node* right;
	int data;
	Node* parent;
	int color;
	Node* sibling;
};


#endif