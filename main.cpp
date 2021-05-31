//PROJECT DESCRIPTION: Red-Black Tree Insertion program. User can input numbers in console or read from text file.
//NAME: Aammya Sapra
//DATE: 05-25-2021
//referred to wikipedia/youtube/geeksforgeeks


#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "Node.h"

using namespace std;


//function prototypes
Node* add_node(Node* root, Node* n);
void read_file(Node* &root, char file_name[]);
void rotate_right(Node* &root, Node* n);
void rotate_left(Node* &root, Node* n);
void fix_tree(Node* &root, Node* &n);
void display_tree(Node* root, int num_spaces); 




//--------------------------------------------------MAIN FUNCTION-------------------------------------------------

int main() {

	bool inputting = true;
	char command[10];  //stores the command (ADD, DISPLAY, QUIT) inputted by the user

	//print out instructions
	cout << "RED-BLACK TREE" << endl;
	cout << "To add a number through the console, type \'ADD\'." << endl;
	cout << "To read in numbers from a file, type \'READ\'." << endl;
	cout << "To display tree, branching out towards the right, type \'PRINT\'." << endl;
	cout << "To quit, type \'QUIT\'." << endl << endl;

	Node* root = NULL;

	while (inputting) {
		cin >> command;
		cin.get();

		//ADD NUMBER THROUGH CONSOLE------------------------------------
		if (strcmp(command, "ADD") == 0) {
			int d;
			cout << "Enter number between 1-999: ";
			cin >> d;
			cin.get();
			Node* n = new Node();
			n->setData(d);
			root = add_node(root, n);
			fix_tree(root, n);
			cout << "Finished adding." << endl;
			cout << "\nEnter another command to continue or \'QUIT\' to exit." << endl << endl;

		} 

		//READ NUMBERS FROM FILE------------------------------------
		else if (strcmp(command, "READ") == 0) {
			cout << "Enter file name. Current input files stored: \'numbers.txt\'" << endl;
			char file_name[50];
			cin.getline(file_name, 50, '\n');
			read_file(root, file_name);
			cout << "Finished adding." << endl;
			cout << "\nEnter another command to continue or \'QUIT\' to exit." << endl << endl;
		}

		//DISPLAY TREE-------------------------------------
		else if (strcmp(command, "PRINT") == 0) {
			display_tree(root, 0);
			cout << "\nEnter another command to continue or \'QUIT\' to exit." << endl << endl;
		}

		//QUIT------------------------------------------------
		else if (strcmp(command, "QUIT") == 0) {
			inputting = false;
			break;
		}

		//INVALID INPUT---------------------------------------
		else { //prompt user to re-enter command if something invalid was entered
			cout << "\nPlease enter a valid command x_x." << endl;
		}
	} //end of while loop 


	return 0;

} //end of main




//--------------------------------------------------------FUNCTIONS------------------------------------------------------------


//function to read in space-seperated numbers from a single-line text file and add each number sequentially, updating the tree properly after each one
void read_file(Node* &root, char file_name[]) {
	ifstream inFile;
	inFile.open(file_name);
	char* file_contents = new char[500];
	inFile.getline(file_contents, 500);
	int* array = new int[500];
	int index = 0;
	char* number = strtok(file_contents, " ");  //break input into a series of tokens using the delimiter " "
	while (number != NULL) { //walk through the tokens
		array[index] = atoi(number);
		number = strtok(NULL, " ");
		index++;
	}

	//add numbers into tree
	for (int i = 0; i < index; i++) {
		Node* n = new Node();
		n->setData(array[i]);
		root = add_node(root, n);
		fix_tree(root, n);
	}

	return;
}




//function to insert a single number into the tree (BST insertion) and return the root
Node* add_node(Node* root, Node* n) {
	if (root == NULL) { //if tree empty return n as the new root
		return n; 
	}
	else if (root->getData() >= n->getData()) {
		root->setLeft(add_node(root->getLeft(), n));
		root->getLeft()->setParent(root);
	}
	else if (root->getData() < n->getData()) {
		root->setRight(add_node(root->getRight(), n));
		root->getRight()->setParent(root);
	}
	return root; //if tree not empty return unchanged root
}




//function for right rotation
void rotate_right(Node* &root, Node* n) {
	Node* left = n->getLeft();
	n->setLeft(left->getRight());

	if (n->getLeft() != NULL) {
		n->getLeft()->setParent(n);
	}

	left->setParent(n->getParent());

	if (n->getParent() == NULL) {
		root = left;
	}
	else if (n == n->getParent()->getLeft()) {
		n->getParent()->setLeft(left);
	}
	else {
		n->getParent()->setRight(left);
	}

	left->setRight(n);
	n->setParent(left);

	return;
}


//function for left rotation
void rotate_left(Node* &root, Node* n) {

	Node* right = n->getRight();
	n->setRight(right->getLeft());

	if (n->getRight() != NULL) {
		n->getRight()->setParent(n);
	}

	right->setParent(n->getParent());

	if (n->getParent() == NULL) {
		root = right;
	}
	else if (n == n->getParent()->getLeft()) {
		n->getParent()->setLeft(right);
	}
	else {
		n->getParent()->setRight(right);
	}

	right->setLeft(n);
	n->setParent(right);

	return;
}



//function to fix the tree so that it fits RBT rules after doing BST insertion
//called after every add_node function call
void fix_tree(Node* &root, Node* &n) {

	Node* parent = NULL;
	Node* grandparent = NULL;

	//COLOR KEY---------------
	//BLACK: 0
	//RED: 1

	while ((n != root) && (n->getColor() != 0) && (n->getParent()->getColor() == 1)) {

		parent = n->getParent();
		grandparent = n->getParent()->getParent();

		//If parent of n is right child of grandparent of n----------------------
		if (parent == grandparent->getRight()) {
			Node* uncle = grandparent->getLeft();

			//if uncle is red then only need to fix color
			if (uncle != NULL && uncle->getColor() == 1) {
				grandparent->setColor(1);
				parent->setColor(0);
				uncle->setColor(0);
				n = grandparent;
			}
			else {

				//if n is left child of parent, rotate right
				if (n == parent->getLeft()) {
					rotate_right(root, parent);
					n = parent;
					parent = n->getParent();
				}
				//if n is right child of parent, rotate left
				rotate_left(root, grandparent);
				int parent_color = parent->getColor();
				int grandparent_color = grandparent->getColor();
				parent->setColor(grandparent_color); //swap
				grandparent->setColor(parent_color); //swap
				n = parent;
			}
		}
		//If parent of n is left child of grandparent of n-----------------------
		else if (parent == grandparent->getLeft()) {

			Node* uncle = grandparent->getRight();

			//if uncle is red then only need to fix color
			if (uncle != NULL && uncle->getColor() == 1) {
				grandparent->setColor(1);
				parent->setColor(0);
				uncle->setColor(0);
				n = grandparent;
			}
			else {
				//if n is right child of parent, rotate left
				if (n == parent->getRight()) {
					rotate_left(root, parent);
					n = parent;
					parent = n->getParent();
				}
				//if n is left child of parent, rotate right
				rotate_right(root, grandparent);
				int parent_color = parent->getColor();
				int grandparent_color = grandparent->getColor();
				parent->setColor(grandparent_color); //swap
				grandparent->setColor(parent_color); //swap
				n = parent;
			}

		} //end of if-statement

	} //end of while loop

	root->setColor(0); //make root black
	return;

} //end of fix_tree()





//function to print tree (root on left, branches out towards the right)
void display_tree(Node* current, int num_spaces) {

	if (current != NULL) {
		num_spaces = num_spaces + 10;
		display_tree(current->getRight(), num_spaces);
		cout << endl;

		for (int i = 10; i < num_spaces; i++) {
			cout << " ";
		}

		//RED: 1
		//BLACK: 0
		//if node is red then print out data in red text
		if (current->getColor() == 1) {
			//cout << "blah ";
			cout << "\033[1;31m" << current->getData() << "\033[0m";
		}
		else {
			cout << current->getData();
		}
		
		display_tree(current->getLeft(), num_spaces);
	}

	return;

}

