// PhoneBookApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>

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
	void print_all_records();
	void find_record(string &name);
	void remove_record(string &name);
	void load();

	//Helper to retrieve record
	void retreiveHelper(RecordInsert *root, string name) {
		if (root == NULL) {			
			return;
		}	
		//Compare last names
		int arg = name.compare(root->last_name);

		//inorder traversal of tree to find the last name	
		//name matches
		if (arg == 0) {
			cout << "\n";
			cout << "Records found: " << "\n";
			cout << root->first_name << ", " << root->last_name << ", "
				<< root->number << endl;
			return;
		}
		//keep traversing through the tree
		retreiveHelper(root->left, name);
		retreiveHelper(root->right, name);
	}	

	//Helper to print all records
	void inorderHelper(RecordInsert *root) {
		if (root == NULL) {
			return;
		}
		//print out format
		inorderHelper(root->left);
		cout << root->first_name << "  " << root->last_name << "  "
			<< root->number << endl;

		inorderHelper(root->right);
	}	

	//Deleting a record given last name
	//Helper to retrieve record
	void removeHelper(RecordInsert *root, string name) {		
		if (root == NULL) {			
			return;
		}
		//record insert for swapping pointers

		//Compare last names
		int arg = name.compare(root->last_name);

		//inorder traversal of tree to find the last name	
		//name matches
		if (arg == 0) {			
			root->first_name = "";
			root->last_name = "";
			root->number = "";
			
			//print out new list of records
			cout << "\n";
			Record::print_all_records();

			return;
		}
		//keep traversing through the tree
		removeHelper(root->left, name);
		removeHelper(root->right, name);
		
	}

	//Inserting a new record with given key
	RecordInsert* new_insert(RecordInsert* root, RecordInsert *pt) {
		//if tree is empty return the new insert
		if (root == NULL) { return pt; };

		//Compare the last names based on alphabetical order
		int arg = (pt->last_name).compare((root->last_name));
		//The last names are equal
		if (arg == 0) {
			cout << "Cant handel same last names";
			return NULL;
		}

		//The new name comes before the previous
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
void Record::print_all_records() {
	cout << "List of All Records: " << "\n""\n";
	inorderHelper(root);
}
//Print record given last name
void Record::find_record(string &name) {	
	retreiveHelper(root, name);
}
//remove a record
void Record::remove_record(string &name) {
	removeHelper(root, name);
	
}
//Load a file
void Record::load() {
	char data[100];

	// open a file in write mode.
	ofstream outfile;
	outfile.open("phonebook.txt");

	cout << "Writing to the file" << endl;
	cout << "Enter your first name: " << endl;
	cin.getline(data, 100);

	// write inputted data into the file.
	outfile << data << endl;

	cout << "Enter your last name: " << endl;
	cin.getline(data, 100);

	// again write inputted data into the file.
	outfile << data << endl;

	cout << "Enter your phone number: " << endl;
	cin.getline(data, 100);
	cin.ignore();

	// again write inputted data into the file.
	outfile << data << endl;

	// close the opened file.
	outfile.close();

	// open a file in read mode.
	ifstream infile;
	infile.open("phonebook.txt");

	cout << "Reading from the file" << endl;
	infile >> data;

	// write the data at the screen.
	cout << data << endl;

	// again read the data from the file and display it.
	infile >> data;
	cout << data << endl;

	// close the opened file.
	infile.close();
}


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

	//Start interface
	int choice = 0;
	string fName;
	string lName;
	string phNumber;

	while (choice != 6) {
		cout << "\nWhat would you like to do?: " << endl;
		cout << "1. Add a contact " << endl;
		cout << "2. Retrieve contact " << endl;
		cout << "3. Delete a Contact " << endl;
		cout << "4. Load file " << endl;
		cout << "5. Display the sorted contact list " << endl;
		cout << "6. Exit " << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "\nEnter first name: ";
			cin >> fName;
			cout << "\nEnter last name: ";
			cin >> lName;
			cout << "\nEnter number: ";
			cin >> phNumber;
			cout << endl;
			record.insert(fName, lName, phNumber);
			cout << endl;
			break;
		case 2:
			cout << "Enter last name: " << endl;
			cin >> lName;
			record.find_record(lName);
			break;
		case 3:
			cout << "Enter last name: ";
			cin >> lName;
			record.remove_record(lName);
			break;
		case 4:
			record.load();
			break;

		case 5:
			record.print_all_records();
			break;

		case 6:
			cout << "Goodbye";
			break;

		default:
			cout << "\n" << choice << " is not an option. Please select a valid option." << endl;
			cin >> choice;
			break;
		}
	}

	return 0;

	
	
}

