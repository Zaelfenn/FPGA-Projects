#include "Stack.h"

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <string>
using std::string;

#include <crtdbg.h>
#include <conio.h>

#define _CRTDBG_MAP_ALLOC



const int NUM_SIZE = 5;
const int NUM_NAMES = 15;

const char* NAMES[] = { "Kyle", "Brit", "Seth", "Alex", "Josh", "Kian",
"Kate", "Terry", "Ann", "Elaine", "Stephanie", "Wanda", "Oscar",
"Oliver", "Tobey" };

typedef bool(*FunctionPointer)();  // Define a funtion pointer type
// Test function declaration
bool test_default_ctor();
bool test_copy_ctor();
bool test_value_ctor();
bool test_move_ctor();
bool test_op_assignment();
bool test_move_op_assignment();
bool test_push();
bool test_push_of();
bool test_pop();
bool test_pop_uf();
bool test_peek();
bool test_peek_uf();
bool test_peek_const();
bool test_peek_const_uf();
bool test_get_num();
bool test_get_num_const();
bool test_get_size();
bool test_get_size_const();
bool test_set_size_up();
bool test_set_size_down();
bool test_set_size_neg();
bool test_is_empty();
bool test_is_empty_const();
bool test_is_full();
bool test_is_full_const();

bool test_default_ctor_complex();
bool test_copy_ctor_complex();
bool test_value_ctor_complex();
bool test_move_ctor_complex();
bool test_op_assignment_complex();
bool test_move_op_assignment_complex();
bool test_push_complex();
bool test_push_of_complex();
bool test_pop_complex();
bool test_pop_uf_complex();
bool test_peek_complex();
bool test_peek_uf_complex();
bool test_peek_const_complex();
bool test_peek_const_uf_complex();
bool test_get_num_complex();
bool test_get_num_const_complex();
bool test_get_size_complex();
bool test_get_size_const_complex();
bool test_set_size_up_complex();
bool test_set_size_down_complex();
bool test_set_size_neg_complex();
bool test_is_empty_complex();
bool test_is_empty_const_complex();
bool test_is_full_complex();
bool test_is_full_const_complex();

Stack<int> ReturnIntList();
Stack<string> ReturnStringList();

FunctionPointer fun_point[] = { test_default_ctor, test_copy_ctor, test_value_ctor, test_move_ctor, test_op_assignment, test_move_op_assignment,
								test_push, test_push_of, test_pop, test_pop_uf, test_peek, test_peek_uf, test_peek_const, test_peek_const_uf,
								test_get_num, test_get_num_const, test_get_size, test_get_size_const, test_set_size_up, test_set_size_down,
								test_set_size_neg, test_is_empty, test_is_empty_const, test_is_full, test_is_full_const,
								
								test_default_ctor_complex, test_copy_ctor_complex, test_value_ctor_complex, test_move_ctor_complex, 
								test_op_assignment_complex, test_move_op_assignment_complex, test_push_complex, test_push_of_complex, test_pop_complex, 
								test_pop_uf_complex, test_peek_complex, test_peek_uf_complex, test_peek_const_complex, test_peek_const_uf_complex,
								test_get_num_complex, test_get_num_const_complex, test_get_size_complex, test_get_size_const_complex, 
								test_set_size_up_complex, test_set_size_down_complex, test_set_size_neg_complex, 
								test_is_empty_complex, test_is_empty_const_complex, test_is_full_complex, test_is_full_const_complex };
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


bool test_default_ctor() {
	Stack<int> test;
	bool retVal = false;
	if (test.getNumElements() == 0 && test.getSize() == 0) {
		retVal = true;
	}
	cout << "Default ctor test ";
	return retVal;
}

bool test_copy_ctor() {
	Stack<int> test;
	bool retVal = true;
	test.setSize(NUM_SIZE);
	for (int i = 0; i < NUM_SIZE; ++i) {
		test.Push(i);
	}

	Stack<int> test2(test);

	for (int i = 0; i < NUM_SIZE; ++i) {
		if (test.Pop() != test2.Pop()) {
			retVal = false;
		}
	}
	cout << "Copy ctor test ";
	return retVal;
}

bool test_value_ctor() {
	Stack<int> test(NUM_SIZE);
	bool retVal = false;
	if (test.getSize() == NUM_SIZE) {
		retVal = true;
	}
	cout << "1 arg ctor test ";
	return retVal;
}

bool test_move_ctor() {
	Stack<int> test(ReturnIntList());
	
	bool retVal = true;

	if (test.getSize() == ReturnIntList().getSize()) {
		for (int i = NUM_SIZE - 1; i >= 0; --i) {
			if (test.Pop() != i)
				retVal = false;
		}
	}
	
	else
		retVal = false;

	cout << "Move ctor test: ";
	return retVal;
}

bool test_op_assignment() {
	Stack<int> test(NUM_SIZE);
	
	bool retVal = true;
	
	for (int i = 0; i < NUM_SIZE; ++i) {
		test.Push(i);
	}
	
	Stack<int> test2;
	
	test2 = test;
	
	if (test.getSize() == test2.getSize()) {
		
		for (int i = 0; i < NUM_SIZE; ++i) {
		
			if (test.Pop() != test2.Pop())
				retVal = false;
		
		}
	}

	else {
		retVal = false;
	}
	cout << "Assignment operator test: ";

	return retVal;
}

bool test_move_op_assignment() {
	Stack<int> test;

	test = ReturnIntList();

	bool retVal = true;

	if (test.getSize() == ReturnIntList().getSize()) {
		for (int i = NUM_SIZE - 1; i >= 0; --i) {
			if (test.Pop() != i)
				retVal = false;
		}
	}

	else
		retVal = false;

	cout << "Move operator test: ";
	return retVal;
}

bool test_push() {
	Stack<int> test(NUM_SIZE);
	bool retVal = true;
	for (int i = 0; i < NUM_SIZE; ++i) {
		test.Push(i);
	}

	for (int i = NUM_SIZE - 1; i >= 0; --i) {
		if (test.Pop() != i) {
			retVal = false;
		}
	}

	cout << "Push test: ";
	return retVal;
}

bool test_push_of() {
	Stack<int> test(NUM_SIZE);
	bool retVal = false;
	for (int i = 0; i < NUM_SIZE; ++i) {
		test.Push(i);
	}
	
	try {
		test.Push(0);
	}
	catch (Exception& e) {
		e.getMsg();
		retVal = true;
	}
	cout << "Push overflow test: ";
	
	return retVal;
}

bool test_pop() {
	Stack<int> test(NUM_SIZE);
	bool retVal = true;
	for (int i = 0; i < NUM_SIZE; ++i) {
		test.Push(i);
	}

	for (int i = NUM_SIZE - 1; i >= 0; --i) {
		if (test.Pop() != i)
			retVal = false;
	}
	if (test.getNumElements() != 0) {
		retVal = false;
	}

	cout << "Pop test: ";
	
	return retVal;
}

bool test_pop_uf() {
	Stack<int> test(NUM_SIZE);
	bool retVal = false;

	try {
		test.Pop();
	}
	catch (Exception& e) {
		e.getMsg();
		retVal = true;
	}
	cout << "Pop underflow test: ";
	return retVal;
}

bool test_peek(){
	Stack<int> test(NUM_SIZE);
	bool retVal = false;
	for (int i = 0; i < NUM_SIZE; ++i) {
		test.Push(i);
	}

	if (test.Peek() == NUM_SIZE - 1) {
		retVal = true;
	}

	cout << "Peek test: ";
	
	return retVal;
}

bool test_peek_uf() {
	Stack<int> test(NUM_SIZE);
	bool retVal = false;

	try {
		test.Peek();
	}
	catch (Exception& e) {
		e.getMsg();
		retVal = true;
	}
	cout << "Peek underflow test: ";
	
	return retVal;
}

bool test_peek_const() {
	Stack<int> test(NUM_SIZE);
	bool retVal = false;
	for (int i = 0; i < NUM_SIZE; ++i) {
		test.Push(i);
	}

	const Stack<int> test2(test);
	if (test2.Peek() == test.Peek()) {
		retVal = true;
	}
	cout << "Const peek test: ";
	return retVal;
}

bool test_peek_const_uf() {
	const Stack<int> test;
	bool retVal = false;
	try {
		test.Peek();
	}
	catch (Exception& e) {
		e.getMsg();
		retVal = true;
	}
	cout << "Const peek underflow test: ";
	return retVal;
}

bool test_get_num() {
	Stack<int> test(NUM_SIZE);
	bool retVal = false;
	for (int i = 0; i < NUM_SIZE; ++i) {
		test.Push(i);
	}
	if (test.getNumElements() == NUM_SIZE) {
		retVal = true;
	}

	cout << "GetNumElements test: ";
	return retVal;
}

bool test_get_num_const() {
	Stack<int> test(NUM_SIZE);
	bool retVal = false;
	for (int i = 0; i < NUM_SIZE; ++i) {
		test.Push(i);
	}
	const Stack<int> test2(test);
	if (test2.getNumElements() == NUM_SIZE)
		retVal = true;
	cout << "const GetNumElements test: ";
	return retVal;
}

bool test_get_size() {
	Stack<int> test(NUM_SIZE);
	bool retVal = false;
	if (test.getSize() == NUM_SIZE)
		retVal = true;

	cout << "getSize test: ";
	return retVal;
}

bool test_get_size_const() {
	const Stack<int> test(NUM_SIZE);
	bool retVal = false;
	if (test.getSize() == NUM_SIZE)
		retVal = true;

	cout << "const getSize test: ";
	return retVal;
}

bool test_set_size_up() {
	Stack<int> test;
	bool retVal = false;
	test.setSize(NUM_SIZE);
	if (test.getSize() == NUM_SIZE) {
		retVal = true;
	}

	cout << "Set size up test: ";
	return retVal;
}

bool test_set_size_down() {
	Stack<int> test(NUM_SIZE);
	bool retVal = false;
	test.setSize(2);
	if (test.getSize() == 2) {
		retVal = true;
	}

	cout << "Set size down test: ";
	return retVal;
}

bool test_set_size_neg() {
	Stack<int> test;
	bool retVal = false;
	try {
		test.setSize(-5);
	}
	catch (Exception& e) {
		e.getMsg();
		retVal = true;
	}
	cout << "Set size negative test: ";
	return retVal;
}

bool test_is_empty() {
	Stack<int> test;
	bool retVal = false;
	if (test.isEmpty()) {
		retVal = true;
	}

	cout << "isEmpty test: ";
	return retVal;
}

bool test_is_empty_const() {
	const Stack<int> test;
	bool retVal = false;
	if (test.isEmpty()) {
		retVal = true;
	}

	cout << "const isEmpty test: ";
	return retVal;
}

bool test_is_full() {
	Stack<int> test(NUM_SIZE);
	bool retVal = false;
	for (int i = 0; i < NUM_SIZE; ++i) {
		test.Push(i);
	}
	if (test.isFull()) {
		retVal = true;
	}

	cout << "isFull test: ";
	return retVal;
}

bool test_is_full_const() {
	Stack<int> test(NUM_SIZE);
	bool retVal = false;
	for (int i = 0; i < NUM_SIZE; ++i) {
		test.Push(i);
	}
	const Stack<int> test2(test);
	
	if (test2.isFull()) {
		retVal = true;
	}

	cout << "const isFull test: ";
	return retVal;
}

bool test_default_ctor_complex() {
	Stack<string> test;
	bool retVal = false;
	if (test.getNumElements() == 0 && test.getSize() == 0) {
		retVal = true;
	}
	cout << "complex Default ctor test ";
	return retVal;
}
bool test_copy_ctor_complex() {
	Stack<string> test;
	bool retVal = true;
	test.setSize(NUM_NAMES);
	for (int i = 0; i < NUM_NAMES; ++i) {
		test.Push(NAMES[i]);
	}

	Stack<string> test2(test);

	for (int i = 0; i < NUM_NAMES; ++i) {
		if (test.Pop() != test2.Pop()) {
			retVal = false;
		}
	}
	cout << "complex Copy ctor test ";
	return retVal;
}
bool test_value_ctor_complex() {
	Stack<string> test(NUM_NAMES);
	bool retVal = false;
	if (test.getSize() == NUM_NAMES) {
		retVal = true;
	}
	cout << "complex 1 arg ctor test ";
	return retVal;
}
bool test_move_ctor_complex() {
	Stack<string> test(ReturnStringList());

	bool retVal = true;

	if (test.getSize() == ReturnStringList().getSize()) {
		for (int i = NUM_NAMES - 1; i >= 0; --i) {
			if (test.Pop() != NAMES[i])
				retVal = false;
		}
	}

	else
		retVal = false;

	cout << "complex Move ctor test: ";
	return retVal;
}
bool test_op_assignment_complex() {
	Stack<string> test(NUM_NAMES);

	bool retVal = true;

	for (int i = 0; i < NUM_NAMES; ++i) {
		test.Push(NAMES[i]);
	}

	Stack<string> test2;

	test2 = test;

	if (test.getSize() == test2.getSize()) {

		for (int i = 0; i < NUM_NAMES; ++i) {

			if (test.Pop() != test2.Pop())
				retVal = false;

		}
	}

	else {
		retVal = false;
	}
	cout << "complex Assignment operator test: ";

	return retVal;
}
bool test_move_op_assignment_complex() {
	Stack<string> test;

	test = ReturnStringList();

	bool retVal = true;

	if (test.getSize() == ReturnStringList().getSize()) {
		for (int i = NUM_NAMES - 1; i >= 0; --i) {
			if (test.Pop() != NAMES[i])
				retVal = false;
		}
	}

	else
		retVal = false;

	cout << "complex Move operator test: ";
	return retVal;
}
bool test_push_complex() {
	Stack<string> test(NUM_NAMES);
	bool retVal = true;
	for (int i = 0; i < NUM_NAMES; ++i) {
		test.Push(NAMES[i]);
	}

	for (int i = NUM_NAMES - 1; i >= 0; --i) {
		if (test.Pop() != NAMES[i]) {
			retVal = false;
		}
	}

	cout << "complex Push test: ";
	return retVal;
}
bool test_push_of_complex() {
	Stack<string> test(NUM_NAMES);
	bool retVal = false;
	for (int i = 0; i < NUM_NAMES; ++i) {
		test.Push(NAMES[i]);
	}

	try {
		test.Push("Name");
	}
	catch (Exception& e) {
		e.getMsg();
		retVal = true;
	}
	cout << "copmlex Push overflow test: ";

	return retVal;
}
bool test_pop_complex() {
	Stack<string> test(NUM_NAMES);
	bool retVal = true;
	for (int i = 0; i < NUM_NAMES; ++i) {
		test.Push(NAMES[i]);
	}

	for (int i = NUM_NAMES - 1; i >= 0; --i) {
		if (test.Pop() != NAMES[i])
			retVal = false;
	}
	if (test.getNumElements() != 0) {
		retVal = false;
	}

	cout << "complex Pop test: ";

	return retVal;
}
bool test_pop_uf_complex() {
	Stack<string> test(NUM_NAMES);
	bool retVal = false;

	try {
		test.Pop();
	}
	catch (Exception& e) {
		e.getMsg();
		retVal = true;
	}
	cout << "complex Pop underflow test: ";
	return retVal;
}
bool test_peek_complex() {
	Stack<string> test(NUM_NAMES);
	bool retVal = false;
	for (int i = 0; i < NUM_NAMES; ++i) {
		test.Push(NAMES[i]);
	}

	if (test.Peek() == NAMES[NUM_NAMES - 1]) {
		retVal = true;
	}

	cout << "complex Peek test: ";

	return retVal;
}
bool test_peek_uf_complex() {
	Stack<string> test(NUM_NAMES);
	bool retVal = false;

	try {
		test.Peek();
	}
	catch (Exception& e) {
		e.getMsg();
		retVal = true;
	}
	cout << "complex Peek underflow test: ";

	return retVal;
}
bool test_peek_const_complex() {
	Stack<string> test(NUM_NAMES);
	bool retVal = false;
	for (int i = 0; i < NUM_NAMES; ++i) {
		test.Push(NAMES[i]);
	}

	const Stack<string> test2(test);
	if (test2.Peek() == test.Peek()) {
		retVal = true;
	}
	cout << "cpmplex Const peek test: ";
	return retVal;
}
bool test_peek_const_uf_complex() {
	const Stack<string> test;
	bool retVal = false;
	try {
		test.Peek();
	}
	catch (Exception& e) {
		e.getMsg();
		retVal = true;
	}
	cout << "complex Const peek underflow test: ";
	return retVal;
}
bool test_get_num_complex() {
	Stack<string> test(NUM_NAMES);
	bool retVal = false;
	for (int i = 0; i < NUM_NAMES; ++i) {
		test.Push(NAMES[i]);
	}
	if (test.getNumElements() == NUM_NAMES) {
		retVal = true;
	}

	cout << "complex GetNumElements test: ";
	return retVal;
}
bool test_get_num_const_complex() {
	Stack<string> test(NUM_NAMES);
	bool retVal = false;
	for (int i = 0; i < NUM_NAMES; ++i) {
		test.Push(NAMES[i]);
	}
	const Stack<string> test2(test);
	if (test2.getNumElements() == NUM_NAMES)
		retVal = true;
	cout << "complex const GetNumElements test: ";
	return retVal;
}
bool test_get_size_complex() {
	Stack<int> test(NUM_NAMES);
	bool retVal = false;
	if (test.getSize() == NUM_NAMES)
		retVal = true;

	cout << "copmlex getSize test: ";
	return retVal;
}
bool test_get_size_const_complex() {
	const Stack<string> test(NUM_NAMES);
	bool retVal = false;
	if (test.getSize() == NUM_NAMES)
		retVal = true;

	cout << "complex const getSize test: ";
	return retVal;
}
bool test_set_size_up_complex() {
	Stack<string> test;
	bool retVal = false;
	test.setSize(NUM_NAMES);
	if (test.getSize() == NUM_NAMES) {
		retVal = true;
	}

	cout << "complex Set size up test: ";
	return retVal;
}
bool test_set_size_down_complex() {
	Stack<string> test(NUM_SIZE);
	bool retVal = false;
	test.setSize(2);
	if (test.getSize() == 2) {
		retVal = true;
	}

	cout << "complex Set size down test: ";
	return retVal;
}
bool test_set_size_neg_complex() {
	Stack<string> test;
	bool retVal = false;
	try {
		test.setSize(-5);
	}
	catch (Exception& e) {
		e.getMsg();
		retVal = true;
	}
	cout << "complex Set size negative test: ";
	return retVal;
}
bool test_is_empty_complex() {
	 Stack<string> test;
	bool retVal = false;
	if (test.isEmpty()) {
		retVal = true;
	}

	cout << "complex isEmpty test: ";
	return retVal;
}
bool test_is_empty_const_complex() {
	const Stack<string> test;
	bool retVal = false;
	if (test.isEmpty()) {
		retVal = true;
	}

	cout << "const isEmpty test: ";
	return retVal;
}
bool test_is_full_complex() {
	Stack<string> test(NUM_NAMES);
	bool retVal = false;
	for (int i = 0; i < NUM_NAMES; ++i) {
		test.Push(NAMES[i]);
	}
	if (test.isFull()) {
		retVal = true;
	}

	cout << "complex isFull test: ";
	return retVal;
}
bool test_is_full_const_complex() {
	Stack<string> test(NUM_NAMES);
	bool retVal = false;
	for (int i = 0; i < NUM_NAMES; ++i) {
		test.Push(NAMES[i]);
	}
	const Stack<string> test2(test);

	if (test2.isFull()) {
		retVal = true;
	}

	cout << "complex const isFull test: ";
	return retVal;
}



Stack<int> ReturnIntList() {
	Stack<int> retVal(NUM_SIZE);
	
	for (int i = 0; i < NUM_SIZE; ++i)
		retVal.Push(i);

	return retVal;
}

Stack<string> ReturnStringList() {
	Stack<string> retVal(NUM_NAMES);
	for (int i = 0; i < NUM_NAMES; ++i) {
		retVal.Push(NAMES[i]);
	}
	return retVal;
}