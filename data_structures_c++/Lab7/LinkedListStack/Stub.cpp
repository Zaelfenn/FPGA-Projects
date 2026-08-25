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

typedef bool(*FunctionPointer)();  // Define a function pointer type
// Test function declaration
bool test_default_ctor();
bool test_copy_ctor();
bool test_move_ctor();
bool test_op_assignment();
bool test_move_op_assignment();
bool test_push();
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
bool test_is_empty();
bool test_is_empty_const();


bool test_default_ctor_complex();
bool test_copy_ctor_complex();
bool test_move_ctor_complex();
bool test_op_assignment_complex();
bool test_move_op_assignment_complex();
bool test_push_complex();
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
bool test_is_empty_complex();
bool test_is_empty_const_complex();

Stack<int> ReturnIntList();
Stack<string> ReturnStringList();

FunctionPointer fun_point[] = { test_default_ctor, test_copy_ctor, test_move_ctor, test_op_assignment, test_move_op_assignment,
								test_push,  test_pop, test_pop_uf, test_peek, test_peek_uf, test_peek_const, test_peek_const_uf,
								test_get_num, test_get_num_const, test_get_size, test_get_size_const, test_is_empty, test_is_empty_const,
								
								test_default_ctor_complex, test_copy_ctor_complex, test_move_ctor_complex, 
								test_op_assignment_complex, test_move_op_assignment_complex, test_push_complex, test_pop_complex, 
								test_pop_uf_complex, test_peek_complex, test_peek_uf_complex, test_peek_const_complex, test_peek_const_uf_complex,
								test_get_num_complex, test_get_num_const_complex, test_get_size_complex, test_get_size_const_complex, 
								test_is_empty_complex, test_is_empty_const_complex};
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
	if (test.isEmpty()) {
		retVal = true;
	}
	cout << "Default ctor test ";
	return retVal;
}

bool test_copy_ctor() {
	Stack<int> test;
	bool retVal = true;
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

bool test_move_ctor() {
	Stack<int> test(ReturnIntList());
	
	bool retVal = true;

	if (test.getNumElements() == ReturnIntList().getNumElements()) {
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
	Stack<int> test;
	bool retVal = true;
	for (int i = 0; i < NUM_SIZE; ++i) {
		test.Push(i);
	}
	
	Stack<int> test2;
	
	test2 = test;
	
	if (test.getNumElements() == test2.getNumElements()) {
		
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

	if (test.getNumElements() == ReturnIntList().getNumElements()) {
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
	Stack<int> test;
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


bool test_pop() {
	Stack<int> test;
	bool retVal = true;
	for (int i = 0; i < NUM_SIZE; ++i) {
		test.Push(i);
	}

	for (int i = NUM_SIZE - 1; i >= 0; --i) {
		if (test.Pop() != i)
			retVal = false;
	}
	if (!test.isEmpty()) {
		retVal = false;
	}

	cout << "Pop test: ";
	
	return retVal;
}

bool test_pop_uf() {
	Stack<int> test;
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
	Stack<int> test;
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
	Stack<int> test;
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
	Stack<int> test;
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
	Stack<int> test;
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
	Stack<int> test;
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
	Stack<int> test;
	bool retVal = false;
	for (int i = 0; i < NUM_SIZE; ++i) {
		test.Push(i);
	}
	if (test.getNumElements() == NUM_SIZE)
		retVal = true;

	cout << "getSize test: ";
	return retVal;
}

bool test_get_size_const() {
	Stack<int> test;
	bool retVal = false;
	for (int i = 0; i < NUM_SIZE; ++i) {
		test.Push(i);
	}

	const Stack<int> test2(test);
	
	if (test.getNumElements() == NUM_SIZE)
		retVal = true;

	cout << "const getSize test: ";
	return retVal;
}


bool test_is_empty() {
	Stack<int> test;
	bool retVal = false;
	if (test.isEmpty()) {
		retVal = true;
	}

	test.Push(0);
	if (test.isEmpty())
		retVal = false;

	cout << "isEmpty test: ";
	return retVal;
}

bool test_is_empty_const() {
	const Stack<int> test;
	bool retVal = false;
	if (test.isEmpty()) {
		retVal = true;
	}
	Stack<int> test2;
	test2.Push(9);
	const Stack<int> test3(test2);
	if (test3.isEmpty()) {
		retVal = false;
	}

	cout << "const isEmpty test: ";
	return retVal;
}

bool test_default_ctor_complex() {
	Stack<string> test;
	bool retVal = false;
	if (test.getNumElements() == 0) {
		retVal = true;
	}
	cout << "complex Default ctor test ";
	return retVal;
}
bool test_copy_ctor_complex() {
	Stack<string> test;
	bool retVal = true;
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

bool test_move_ctor_complex() {
	Stack<string> test(ReturnStringList());

	bool retVal = true;

	if (test.getNumElements() == ReturnStringList().getNumElements()) {
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
	Stack<string> test;

	bool retVal = true;

	for (int i = 0; i < NUM_NAMES; ++i) {
		test.Push(NAMES[i]);
	}

	Stack<string> test2;

	test2 = test;

	if (test.getNumElements() == test2.getNumElements()) {

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

	if (test.getNumElements() == ReturnStringList().getNumElements()) {
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
	Stack<string> test;
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

bool test_pop_complex() {
	Stack<string> test;
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
	Stack<string> test;
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
	Stack<string> test;
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
	Stack<string> test;
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
	Stack<string> test;
	bool retVal = false;
	for (int i = 0; i < NUM_NAMES; ++i) {
		test.Push(NAMES[i]);
	}

	const Stack<string> test2(test);
	if (test2.Peek() == test.Peek()) {
		retVal = true;
	}
	cout << "complex Const peek test: ";
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
	Stack<string> test;
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
	Stack<string> test;
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
	Stack<string> test;
	for (int i = 0; i < NUM_NAMES; ++i) {
		test.Push(NAMES[i]);
	}
	bool retVal = false;
	if (test.getNumElements() == NUM_NAMES)
		retVal = true;

	cout << "complex getSize test: ";
	return retVal;
}
bool test_get_size_const_complex() {
	Stack<string> test2;
	for (int i = 0; i < NUM_NAMES; ++i) {
		test2.Push(NAMES[i]);
	}
	const Stack<string> test(test2);
	
	bool retVal = false;
	if (test.getNumElements() == NUM_NAMES)
		retVal = true;

	cout << "complex const getSize test: ";
	return retVal;
}

bool test_is_empty_complex() {
	 Stack<string> test;
	bool retVal = false;
	if (test.isEmpty()) {
		retVal = true;
	}
	test.Push("Meow");
	if (test.isEmpty())
		retVal = false;

	cout << "complex isEmpty test: ";
	return retVal;
}

bool test_is_empty_const_complex() {
	const Stack<string> test;
	bool retVal = false;
	if (test.isEmpty()) {
		retVal = true;
	}
	
	Stack<string> test2;
	test2.Push("Meow");
	const Stack<string>test3(test2);
	
	if (test3.isEmpty())
		retVal = false;
	
	cout << "complex const isEmpty test: ";
	return retVal;
}




Stack<int> ReturnIntList() {
	Stack<int> retVal;
	
	for (int i = 0; i < NUM_SIZE; ++i)
		retVal.Push(i);

	return retVal;
}

Stack<string> ReturnStringList() {
	Stack<string> retVal;
	for (int i = 0; i < NUM_NAMES; ++i) {
		retVal.Push(NAMES[i]);
	}
	return retVal;
}