
#include "BSTree.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <string>
using std::string;

#include <crtdbg.h>
#include <conio.h>

#define _CRTDBG_MAP_ALLOC




const int NUM_NAMES = 20;
string TREE_NAMES[NUM_NAMES];

const char* NAMES[] = {"Mop", "Golden", "Job", "Dread", "Fried", "Eggs", "Raw", "Octopus", "Hot", "Inclusive",  
						"Long", "Kled", "New", "Popped", "Quest", "Test", "Stationery", "Wawawa", "Xmas", "United"};
	


const int NUM_SIZE = 9;
int TREE_NUMS[NUM_SIZE];

const int INT_PLACE[] = {5,8,3,1,4,2,6,9,7};

const char* NAME_IN_ORDER[] = {"Dread", "Eggs", "Fried", "Golden", "Hot", "Inclusive", "Job", "Kled", "Long", "Mop", "New", "Octopus", "Popped", "Quest", "Raw", "Stationery", "Test", "United", "Wawawa", "Xmas"};
const char* NAME_PRE_ORDER[] = {"Mop", "Golden", "Dread", "Fried", "Eggs", "Job", "Hot", "Inclusive", "Long", "Kled", "Raw", "Octopus", "New", "Popped", "Quest", "Test", "Stationery", "Wawawa", "United", "Xmas"};
const char* NAME_POST_ORDER[] = { "Eggs", "Fried", "Dread", "Inclusive", "Hot", "Kled", "Long", "Job", "Golden", "New", "Quest", "Popped", "Octopus", "Stationery", "United", "Xmas", "Wawawa", "Test", "Raw", "Mop"};
const char* NAME_BREADTH[] = {"Mop", "Golden", "Raw", "Dread", "Job", "Octopus", "Test", "Fried", "Hot", "Long", "New", "Popped", "Stationery", "Wawawa", "Eggs", "Inclusive", "Kled", "Quest", "United", "Xmas"};
const int INT_IN_ORDER[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
const int INT_PRE_ORDER[] = {5, 3, 1, 2, 4, 8, 6, 7, 9};
const int INT_POST_ORDER[] = {2, 1, 4, 3, 7, 6, 9, 8, 5};
const int INT_BREADTH[] = {5, 3, 8, 1, 4, 6, 9, 2, 7};
int INDEX = 0;


typedef bool(*FunctionPointer)();  // Define a function pointer type

bool test_default_ctor();
bool test_value_ctor();
bool test_copy_ctor();
bool test_move_ctor();
bool test_copy_op();
bool test_move_op();
bool test_insert_empty();
bool test_insert();
bool test_height();
bool test_height_one();
bool test_height_empty();
bool test_delete();
bool test_delete_empty();
bool test_delete_wrong();
bool test_purge();
bool test_purge_empty();
bool test_in_order();
bool test_pre_order();
bool test_post_order();
bool test_breadth_first();


bool test_default_ctor_complex();
bool test_value_ctor_complex();
bool test_copy_ctor_complex();
bool test_move_ctor_complex();
bool test_copy_op_complex();
bool test_move_op_complex();
bool test_insert_empty_complex();
bool test_insert_complex();
bool test_height_complex();
bool test_height_one_complex();
bool test_height_empty_complex();
bool test_delete_complex();
bool test_delete_empty_complex();
bool test_delete_wrong_complex();
bool test_purge_complex();
bool test_purge_empty_complex();
bool test_in_order_complex();
bool test_pre_order_complex();
bool test_post_order_complex();
bool test_breadth_first_complex();


BSTree<int> returnIntTree();
BSTree<string> returnStringTree();

void copy(int data)
{
	TREE_NUMS[INDEX] = data;
	++INDEX;
	if (INDEX > NUM_SIZE)
		INDEX = NUM_SIZE;
}
void copy(string data)
{
	TREE_NAMES[INDEX] = data;
	++INDEX;
	if (INDEX > NUM_NAMES)
		INDEX = NUM_NAMES;
}


FunctionPointer fun_point[] = { test_default_ctor, test_value_ctor, test_copy_ctor,test_move_ctor, test_copy_op ,test_move_op, test_insert_empty, test_insert, 
								test_height, test_height_one, test_height_empty, test_delete, test_delete_empty, test_delete_wrong, test_purge, test_purge_empty,
								test_in_order, test_pre_order, test_post_order, test_breadth_first,


								test_default_ctor_complex, test_value_ctor_complex, test_copy_ctor_complex, test_move_ctor_complex, test_copy_op_complex , test_move_op_complex,
								test_insert_empty_complex, test_insert_complex, test_height_complex, test_height_one_complex, test_height_empty_complex, test_delete_complex,
								test_delete_empty_complex, test_delete_wrong_complex, test_purge_complex, test_purge_empty_complex, test_in_order_complex, test_pre_order_complex,
								test_post_order_complex, test_breadth_first_complex };

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	int failed_tests = 0;

	// Run the test functions
	for (FunctionPointer func : fun_point)
	{
		if (func())
		{
			cout << "passed\n";
		}
		else
		{
			failed_tests++;
			cout << "***** failed *****\n";
		}
	}


	if (failed_tests > 0)
		cout << "\nYou have " << failed_tests << " failed tests";
	else
		cout << "\nAll tests passed! Good job!";

	cout << "\nPress Any Key to Exit";
	cin.get();

	return 0;
}

bool test_default_ctor()
{
	BSTree<int> test;
	bool pass = false;
	if (test.getRoot() == nullptr) {
		pass = true;
	}
	cout << "Default ctor test: ";
	return pass;
}
bool test_value_ctor()
{
	BSTree<int> test(5);
	bool pass = false;
	if (test.getRootData() == 5) {
		pass = true;
	}
	cout << "Value ctor test: ";
	return pass;
}
bool test_copy_ctor()
{
	BSTree<int> copy;
	bool pass = false;
	for (int i = 0; i < NUM_SIZE; ++i) {
		copy.Insert(INT_PLACE[i]);
	}
	BSTree<int>test(copy);
	if (test.getRoot() != nullptr) {
		if (test.getRoot() != copy.getRoot() &&
			test.getRootData() == copy.getRootData() &&
			test.Height() == copy.Height()) {
			pass = true;
		}
	}
	cout << "Copy ctor test: ";
	return pass;
}
bool test_move_ctor()
{
	BSTree<int> test(returnIntTree());
	bool pass = false;
	if (test.getRoot() != nullptr) {
		if (test.getRootData() == returnIntTree().getRootData() &&
			test.Height() == returnIntTree().Height()) {
			pass = true;
		}
	}
	cout << "Move ctor test: ";
	return pass;
}
bool test_copy_op()
{
	BSTree<int> copy(returnIntTree());
	bool pass = false;
	BSTree<int> test;
	test = copy;
	if (test.getRoot() != nullptr) {
		if (test.getRoot() != copy.getRoot() &&
			test.getRootData() == copy.getRootData() &&
			test.Height() == copy.Height()) {
			pass = true;
		}
	}
	cout << "Copy operator test: ";
	return pass;
}
bool test_move_op()
{
	BSTree<int> test;
	test = returnIntTree();
	bool pass = false;
	if (test.getRoot() != nullptr) {
		if (test.getRootData() == returnIntTree().getRootData() &&
			test.Height() == returnIntTree().Height()) {
			pass = true;
		}
	}
	cout << "Move operator test: ";
	return pass;
}
bool test_insert_empty()
{
	BSTree<int> test;
	bool pass = false;
	test.Insert(4);
	if (test.getRoot() != nullptr) {
		if (test.getRootData() == 4) {
			pass = true;
		}
	}
	cout << "empty Insert test: ";
	return pass;
}
bool test_insert()
{
	BSTree<int> test;
	bool pass = true;
	for (int i = 0; i < NUM_SIZE; ++i) {
		test.Insert(INT_PLACE[i]);
	}
	INDEX = 0;
	test.InOrder(copy);

	for (int i = 0; i < NUM_SIZE; ++i) {
		if (TREE_NUMS[i] != INT_IN_ORDER[i]) {
			pass = false;
		}
	}

	cout << "Insert test: ";
	return pass;
}
bool test_height()
{
	BSTree<int> test(returnIntTree());
	bool pass = false;
	if (test.Height() == 3)
		pass = true;
	cout << "Height test: ";
	return pass;
}
bool test_height_one()
{
	BSTree<int> test(0);
	bool pass = false;
	if (test.Height() == 0) {
		pass = true;
	}
	cout << "Height of one test: ";
	return pass;
}
bool test_height_empty()
{
	BSTree<int> test;
	bool pass = false;
	try {
		test.Height();
	}
	catch (Exception& e) {
		e.getMsg();
		pass = true;
	}
	cout << "empty Height test: ";
	return pass;
}
bool test_delete()
{
	BSTree<int> test(returnIntTree());
	test.Delete(5);
	bool pass = false;
	if (test.getRootData() == 4) {
		pass = true;
	}
	cout << "Delete test: ";
	return pass;
}
bool test_delete_empty()
{
	BSTree<int> test;
	bool pass = false;
	try {
		test.Delete(10);
	}
	catch (Exception& e) {
		e.getMsg();
		pass = true;
	}
	cout << "empty Delete test: ";
	return pass;
}
bool test_delete_wrong()
{
	BSTree<int> test(returnIntTree());
	bool pass = false;
	try {
		test.Delete(10);
	}
	catch (Exception& e) {
		e.getMsg();
		pass = true;
	}
	cout << "wrong Delete test: ";
	return pass;
}
bool test_purge()
{
	BSTree<int> test(returnIntTree());
	test.Purge();
	bool pass = false;
	if (test.getRoot() == nullptr) {
		pass = true;
	}
	cout << "complex Purge test: ";
	return pass;
}
bool test_purge_empty()
{
	BSTree<int> test;
	bool pass = false;
	try {
		test.Purge();
	}
	catch (Exception& e){
		e.getMsg();
		pass = true;
	}
	cout << "empty Purge test: ";
	return pass;
}
bool test_in_order()
{
	INDEX = 0;
	bool pass = true;
	returnIntTree().InOrder(copy);
	for (int i = 0; i < NUM_SIZE; ++i) {
		if (TREE_NUMS[i] != INT_IN_ORDER[i])
			pass = false;
	}
	cout << "inOrder test: ";
	return pass;
}
bool test_pre_order()
{
	INDEX = 0;
	bool pass = true;
	returnIntTree().PreOrder(copy);
	for (int i = 0; i < NUM_SIZE; ++i) {
		if (TREE_NUMS[i] != INT_PRE_ORDER[i])
			pass = false;
	}
	cout << "preOrder test: ";
	return pass;
}
bool test_post_order()
{
	INDEX = 0;
	bool pass = true;
	returnIntTree().PostOrder(copy);
	for (int i = 0; i < NUM_SIZE; ++i) {
		if (TREE_NUMS[i] != INT_POST_ORDER[i])
			pass = false;
	}
	cout << "postOrder test: ";
	return pass;
}
bool test_breadth_first()
{
	INDEX = 0;
	bool pass = true;
	returnIntTree().BreadthFirst(copy);
	for (int i = 0; i < NUM_SIZE; ++i) {
		if (TREE_NUMS[i] != INT_BREADTH[i])
			pass = false;
	}
	cout << "BreadthFirst test: ";
	return pass;
}



bool test_default_ctor_complex()
{
	BSTree<string> test;
	bool pass = false;
	if (test.getRoot() == nullptr) {
		pass = true;
	}
	cout << "complex Default ctor test: ";
	return pass;
}
bool test_value_ctor_complex()
{
	BSTree<string> test("Meow");
	bool pass = false;
	if (test.getRootData() == "Meow") {
		pass = true;
	}
	cout << "Value ctor test: ";
	return pass;
}
bool test_copy_ctor_complex()
{
	BSTree<string> copy;
	bool pass = false;
	for (int i = 0; i < NUM_NAMES; ++i) {
		copy.Insert(NAMES[i]);
	}
	BSTree<string>test(copy);
	if (test.getRoot() != nullptr) {
		if (test.getRoot() != copy.getRoot() &&
			test.getRootData() == copy.getRootData() &&
			test.Height() == copy.Height()) {
			pass = true;
		}
	}
	cout << "complex Copy ctor test: ";
	return pass;
}
bool test_move_ctor_complex()
{
	BSTree<string> test(returnStringTree());
	bool pass = false;
	if (test.getRoot() != nullptr) {
		if (test.getRoot() != returnStringTree().getRoot() &&
			test.getRootData() == returnStringTree().getRootData() &&
			test.Height() == returnStringTree().Height()) {
			pass = true;
		}
	}
	cout << "complex Move ctor test: ";
	return pass;
}
bool test_copy_op_complex()
{
	BSTree<string> copy;
	bool pass = false;
	for (int i = 0; i < NUM_NAMES; ++i) {
		copy.Insert(NAMES[i]);
	}
	BSTree<string>test;
	test = copy;
	if (test.getRoot() != nullptr) {
		if (test.getRoot() != copy.getRoot() &&
			test.getRootData() == copy.getRootData() &&
			test.Height() == copy.Height()) {
			pass = true;
		}
	}
	cout << "complex Copy operator test: ";
	return pass;
}
bool test_move_op_complex()
{
	BSTree<string> test;
	test = returnStringTree();
	bool pass = false;
	if (test.getRoot() != nullptr) {
		if (test.getRoot() != returnStringTree().getRoot() &&
			test.getRootData() == returnStringTree().getRootData() &&
			test.Height() == returnStringTree().Height()) {
			pass = true;
		}
	}
	cout << "complex Move operator test: ";
	return pass;
}
bool test_insert_empty_complex()
{
	BSTree<string> test;
	bool pass = false;
	if (test.getRoot() == nullptr) {
		test.Insert(NAMES[0]);
		if (test.getRootData() == NAMES[0]) {
			pass = true;
		}
	}
	cout << "complex Insert Empty test: ";
	return pass;
}
bool test_insert_complex()
{
	BSTree<string> test;
	bool pass = true;
	for (int i = 0; i < NUM_NAMES; ++i) {
		test.Insert(NAMES[i]);
	}
	INDEX = 0;
	test.InOrder(copy);

	for (int i = 0; i < NUM_NAMES; ++i) {
		if (NAME_IN_ORDER[i] != TREE_NAMES[i]) {
			pass = false;
		}
	}

	cout << "complex insert test: ";
	return pass;
}
bool test_height_complex() {
	cout << "complex Height test: ";
	return (returnStringTree().Height() == 4);
}
bool test_height_one_complex()
{
	BSTree<string> test("Meow");
	bool pass = false;
	if (test.Height() == 0) {
		pass = true;
	}
	cout << "complex Height of one test: ";
	return pass;
}
bool test_height_empty_complex()
{
	BSTree<string> test;
	bool pass = false;
	try {
		test.Height();
	}
	catch (Exception& e) {
		e.getMsg();
		pass = true;
	}
	cout << "complex Empty Height test: ";
	return pass;
}
bool test_delete_complex()
{
	BSTree<string> test(returnStringTree());
	bool pass = false;
	test.Delete(NAMES[0]);
	if (test.getRootData() == NAMES[10]) {
		pass = true;
	}
	cout << "complex Delete test: ";
	return pass;
}
bool test_delete_empty_complex()
{
	BSTree<string> test;
	bool pass = false;
	try {
		test.Delete("Meow");
	}
	catch (Exception& e) {
		e.getMsg();
		pass = true;
	}
	cout << "complex Empty Delete test: ";
	return pass;
}
bool test_delete_wrong_complex()
{
	BSTree<string> test(returnStringTree());
	bool pass = false;
	try {
		test.Delete("Meow");
	}
	catch (Exception& e) {
		e.getMsg();
		pass = true;
	}
	cout << "complex Wrong Delete test: ";
	return pass;
}
bool test_purge_complex()
{
	BSTree<string> test(returnStringTree());
	test.Purge();
	bool pass = false;
	if (test.getRoot() == nullptr) {
		pass = true;
	}
	cout << "complex Purge test: ";
	return pass;
}
bool test_purge_empty_complex()
{
	BSTree<string> test;
	bool pass = false;
	try {
		test.Purge();
	}
	catch (Exception& e) {
		e.getMsg();
		pass = true;
	}
	cout << "complex Empty Purge test: ";
	return pass;
}
bool test_in_order_complex()
{
	INDEX = 0;
	returnStringTree().InOrder(copy);
	bool pass = true;
	for (int i = 0; i < NUM_NAMES; ++i) {
		if (TREE_NAMES[i] != NAME_IN_ORDER[i]) {
			pass = false;
		}
	}
	cout << "complex inOrder test: ";
	return pass;
}
bool test_pre_order_complex()
{
	INDEX = 0;
	returnStringTree().PreOrder(copy);
	bool pass = true;
	for (int i = 0; i < NUM_NAMES; ++i) {
		if (TREE_NAMES[i] != NAME_PRE_ORDER[i]) {
			pass = false;
		}
	}
	cout << "complex preOrder test: ";
	return pass;
}
bool test_post_order_complex()
{
	INDEX = 0;
	returnStringTree().PostOrder(copy);
	bool pass = true;
	for (int i = 0; i < NUM_NAMES; ++i) {
		if (TREE_NAMES[i] != NAME_POST_ORDER[i]) {
			pass = false;
		}
	}
	cout << "complex posOrder test: ";
	return pass;
}
bool test_breadth_first_complex()
{
	INDEX = 0;
	returnStringTree().BreadthFirst(copy);
	bool pass = true;
	for (int i = 0; i < NUM_NAMES; ++i) {
		if (TREE_NAMES[i] != NAME_BREADTH[i]) {
			pass = false;
		}
	}
	cout << "complex BreadthFirst test: ";
	return pass;
}


BSTree<int> returnIntTree()
{
	BSTree<int> retVal;
	for (int i = 0; i < NUM_SIZE; ++i) {
		retVal.Insert(INT_PLACE[i]);
	}
	return retVal;
}
BSTree<string> returnStringTree()
{
	BSTree<string> retVal;
	for (int i = 0; i < NUM_NAMES; ++i) {
		retVal.Insert(NAMES[i]);
	}
	return retVal;
}