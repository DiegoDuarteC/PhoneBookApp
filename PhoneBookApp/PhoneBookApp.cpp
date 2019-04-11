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
	void insert(const int &n);
	void inorder();
	

	//Recursive functions to do level order traversal
	void inorderHelper(RecordInsert *root) {
		if (root == NULL) {
			return;
		}
		inorderHelper(root->left);
		cout << root->first_name << ', ' << root->last_name << ', '
			<< root->number << '/n';

		inorderHelper(root->right);
	}

	//Inserting a new record
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
     
}

