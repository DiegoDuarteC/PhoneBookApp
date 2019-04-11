// PhoneBookApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

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
	void levelOrder();
};

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

