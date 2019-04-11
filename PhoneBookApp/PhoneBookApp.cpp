// PhoneBookApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>

using namespace std;
enum Color {RED, BLACK};

//Node to reprecent a record insert
struct RecordInsert {
	string first_name;
	string last_name;
	string number;

	bool color;
	RecordInsert *left, *right, *parent;

	//Constructor
	RecordInsert(string first, string last, string num) {
		this->first_name = first;
		this->last_name = last;
		this->number = num;

		left = right = parent = { nullptr };
	}
	
};

//Record implemented using a red-black tree data structure 
class Record {
private:
	//root node
	RecordInsert *root;

public:
	//rotational functions for balancing
	void rotateLeft(RecordInsert *&, RecordInsert *&);
	void rotateRight(RecordInsert *&, RecordInsert *&);
	void fixViolation(RecordInsert *&, RecordInsert *&);

	//Constructor
	Record() { root={ nullptr }; }

	//method skeletons
	void insert(const string &first, const string &last, const string &number);
	void print_record();
	

	//Recursive functions to do level order traversal
	void inorderHelper(RecordInsert *root) {
		if (root == NULL) {
			return;
		}
		//print out format
		inorderHelper(root->left);
		cout << root->first_name << ", " << root->last_name << ", "
			<< root->number << endl;

		inorderHelper(root->right);
	}

	//Inserting a new record with given key
	RecordInsert* new_insert(RecordInsert* root, RecordInsert *pt) {
		//if tree is empty return the new insert
		if (root == NULL) { return pt; };

		//Compare the first letter of the last name to the first letter of the previous last name
		int arg = (pt->last_name).compare((root->last_name));
		//The last names are equal
		if (arg == 0) {
			cout << "Cant handel same last names";
			return NULL;
		}

		//The new last name comes before the previous
		if (arg == -1) {			
			root->left = new_insert(root->left, pt);
			root->left->parent = root;			
		}
		//The new name comes after the previous name
		else if (arg == 1) {
			root->right = new_insert(root->right, pt);
			root->right->parent = root;

		}
		else {
			cout << "Something went wrong";
			return NULL;
		}

		return root;
	}



};

//Rotation Functions implemented
void Record::rotateLeft(RecordInsert *&root, RecordInsert *&pt) {
	RecordInsert *pt_right = pt->right;
	pt->right = pt_right->left;

	if (pt->right != NULL) {
		pt->right->parent = pt;
	}

	pt_right->parent = pt->parent;

	if (pt->parent == NULL) {
		root = pt_right;
	}
	else if (pt == pt->parent->left) {
		pt->parent->left = pt_right;
	}
	else {
		pt->parent->right = pt_right;
	}

	pt_right->left = pt;
	pt->parent = pt_right;
}

void Record::rotateRight(RecordInsert *&root, RecordInsert *&pt) {
	RecordInsert *pt_left = pt->left;
	pt->left = pt_left->right;

	if (pt->left != NULL) {
		pt->left->parent = pt;
	}
	pt_left->parent = pt->parent;

	if (pt->parent == NULL) {
		root = pt_left;
	}
	else if (pt == pt->parent->left) {
		pt->parent->left = pt_left;
	}
	else {
		pt->parent->right = pt_left;
	}

	pt_left->right = pt;
	pt->parent = pt_left;
}

//Fix violations caused by insert
// Code from www.geeksforgeeks.org/c-program-red-black-tree-insertion/
void Record::fixViolation(RecordInsert *&root, RecordInsert *&pt) {
	RecordInsert *parent_pt{ nullptr };
	RecordInsert *grand_parent_pt{ nullptr };

	while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {
		parent_pt = pt->parent;
		grand_parent_pt = pt->parent->parent;

		//Parent of pt is left child of grandparent of pt
		if (parent_pt == grand_parent_pt->left) {
			RecordInsert *uncle_pt = grand_parent_pt->right;

			//Uncle of pt is also red therefore recolor
			if (uncle_pt != NULL && uncle_pt->color == RED) {
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}
			else {
				//pt is right child of its parent
				//rotation required
				if (pt == parent_pt->right) {
					rotateLeft(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				//pt is left child of its parent
				//right rotation required
				rotateRight(root, grand_parent_pt);
				swap(parent_pt->color, grand_parent_pt->color);
				pt = parent_pt;
			}
		}
		else {
			RecordInsert *uncle_pt = grand_parent_pt->left;

			//the uncle of pt is also red
			//recolor required
			if ((uncle_pt != NULL) && (uncle_pt->color == RED)) {
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}
			else {
				//pt is left child of its parent
				//Right rotation required
				rotateLeft(root, grand_parent_pt);
				swap(parent_pt->color, grand_parent_pt->color);
				pt = parent_pt;
			}
		}
	}

	root->color = BLACK;
}

//Insert a record with given data
void Record::insert(const string &first, const string &last, const string &number) {
	RecordInsert *pt = new RecordInsert(first, last, number);

	//Search tree insert
	root = new_insert(root, pt);

	//fix violations
	fixViolation(root, pt);
}

//Print records 
void Record::print_record() {
	inorderHelper(root);
}

//Interface for the phonebook
class Phonebook {
public:
	//Adds a new record into the phonebook
	void add() {

	}

	//Display all records that contain a specific last name
	//Return number of records found
	int search(string name) {

	}

	//Remove an existing contact containing given last name
	void remove(string name) {
		//Search if record exists
	}

	//Read data from a text file containing records
	void read(string file) {

	}

	//Write the records to a file
	void wrtie() {

	}

	//Sort all records in ascending order based on last name
	void sort() {

	}
};

int main()
{
	//Create a new record
	Record record;

	//hardcoded inserts
	record.insert("Diego", "Duarte", "905002374");
	record.insert("Bob", "Bourne", "3627371842");
	record.insert("Mike", "Donaldson", "3718318192");
	record.insert("Steve", "Auric", "3718318192");
	record.insert("Josh", "Tylor", "3718318192");
	record.insert("Lisa", "Bettio", "3718318192");
	record.insert("Amy", "Gray", "3718318192");

	record.print_record();
}

