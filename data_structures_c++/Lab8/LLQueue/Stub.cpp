#include "Queue.h"

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

//Declare test function names
bool test_default_ctor();
bool test_copy_ctor();
bool test_move_ctor();
bool test_copy_op();
bool test_move_op();
bool test_enqueue();
bool test_dequeue();
bool test_dequeue_single();
bool test_dequeue_empty();
bool test_peek();
bool test_peek_single();
bool test_peek_empty();
bool test_peek_const();
bool test_peek_single_const();
bool test_peek_empty_const();
bool test_get();
bool test_get_const();
bool test_empty();
bool test_empty_not();
bool test_empty_const();
bool test_empty_not_const();

bool test_default_ctor_complex();
bool test_copy_ctor_complex();
bool test_move_ctor_complex();
bool test_copy_op_complex();
bool test_move_op_complex();
bool test_enqueue_complex();
bool test_dequeue_complex();
bool test_dequeue_single_complex();
bool test_dequeue_empty_complex();
bool test_peek_complex();
bool test_peek_single_complex();
bool test_peek_empty_complex();
bool test_peek_const_complex();
bool test_peek_single_const_complex();
bool test_peek_empty_const_complex();
bool test_get_complex();
bool test_get_const_complex();
bool test_empty_complex();
bool test_empty_not_complex();
bool test_empty_const_complex();
bool test_empty_not_const_complex();

Queue<int> returnIntQueue();
Queue<string> returnStringQueue();

FunctionPointer fun_point[] = { test_default_ctor, test_copy_ctor, test_move_ctor, test_copy_op, test_move_op,
								test_enqueue, test_dequeue, test_dequeue_empty, test_dequeue_single, test_peek, 
								test_peek_single, test_peek_empty, test_peek_const, test_peek_single_const, 
								test_peek_empty_const, test_get, test_get_const, test_empty, test_empty_not,
								test_empty_const, test_empty_not_const,

								test_default_ctor_complex, test_copy_ctor_complex, test_move_ctor_complex,
								test_copy_op_complex, test_move_op_complex, test_enqueue_complex, test_dequeue_complex,
								test_dequeue_single_complex, test_dequeue_empty_complex, test_peek_complex, test_peek_single_complex,
								test_peek_empty_complex, test_peek_const_complex, test_peek_single_const_complex,
								test_peek_empty_const_complex, test_get_complex,test_empty_complex, test_empty_not_complex,
								test_empty_const_complex, test_empty_not_const_complex };



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
	bool pass = false;

	Queue<int> test;

	if (test.isEmpty()) {
		pass = true;
	}
	cout << "Default ctor test ";
	return pass;
}
bool test_copy_ctor()
{
	bool pass = false;
	Queue<int> test1;
	for (int i = 0; i < NUM_SIZE; ++i) {
		test1.Enqueue(i);
	}

	Queue<int> test2(test1);
	if (!test2.isEmpty()) {
		pass = true;
		for (int i = 0; i < NUM_SIZE; ++i) {
			if (test1.Dequeue() != test2.Dequeue())
				pass = false;
		}
	}
	cout << "copy ctor test ";
	return pass;
}
bool test_move_ctor()
{
	bool pass = false;
	Queue<int> test(returnIntQueue());
	if (!test.isEmpty()) {
		pass = true;
		for (int i = 0; i < NUM_SIZE; ++i) {
			if (test.Dequeue() != i) {
				pass = false;
			}
		}
	}
	cout << "move ctor test ";
	return pass;
}
bool test_copy_op()
{
	bool pass = false;
	Queue<int> test1;
	for (int i = 0; i < NUM_SIZE; ++i) {
		test1.Enqueue(i);
	}

	Queue<int> test2;
	test2 = test1;

	if (!test2.isEmpty()) {
		pass = true;
		for (int i = 0; i < NUM_SIZE; ++i) {
			if (test1.Dequeue() != test2.Dequeue())
				pass = false;
		}
	}
	cout << "copy operator test ";
	return pass;
}
bool test_move_op()
{
	bool pass = false;
	Queue<int> test;
	test = returnIntQueue();
	if (!test.isEmpty()) {
		pass = true;
		for (int i = 0; i < NUM_SIZE; ++i) {
			if (test.Dequeue() != i) {
				pass = false;
			}
		}
	}
	cout << "move operator test ";
	return pass;
}
bool test_enqueue()
{
	bool pass = false;
	Queue<int> test;
	for (int i = 0; i < NUM_SIZE; ++i) {
		test.Enqueue(i);
	}
	
	if (!test.isEmpty()) {
		pass = true;
		for (int i = 0; i < NUM_SIZE; ++i) {
			if (test.Dequeue() != i) {
				pass = false;
			}
		}
	}
	cout << "enqueue test ";

	return pass;
}
bool test_dequeue()
{
	bool pass = true;
	Queue<int> test(returnIntQueue());

	for (int i = 0; i < NUM_SIZE; ++i) {
		if (test.Dequeue() != i) {
			pass = false;
		}
	}
	cout << "dequeue test ";

	return pass;
}
bool test_dequeue_single()
{
	bool pass = false;
	Queue<int> test;
	test.Enqueue(3);

	if (test.Dequeue() == 3)
		pass = true;
	if (!test.isEmpty())
		pass = false;
	cout << "single dequeue test ";

	return pass;
}
bool test_dequeue_empty()
{
	bool pass = false;
	Queue<int> test;

	try 
	{
		test.Dequeue();
	}
	catch (Exception& e) 
	{
		e.getMsg();
		pass = true;
	}
	cout << "empty dequeue test ";

	return pass;
}
bool test_peek()
{
	bool pass = true;
	Queue<int> test(returnIntQueue());

	for (int i = 0; i < NUM_SIZE; ++i) {
		if (test.Peek() != i)
			pass = false;
		test.Dequeue();
	}

	cout << "peek test ";

	return pass;
}
bool test_peek_single()
{
	bool pass = false;
	Queue<int> test;
	test.Enqueue(3);

	if (test.Peek() == 3)
		pass = true;

	cout << "single peek test ";

	return pass;
}
bool test_peek_empty()
{
	bool pass = false;

	Queue<int> test;
	try
	{
		test.Peek();
	}
	catch (Exception& e)
	{
		e.getMsg();
		pass = true;
	}
	cout << "empty peek test ";

	return pass;
}
bool test_peek_const()
{
	bool pass = false;
	const Queue<int> test(returnIntQueue());

	if (test.Peek() == 0)
		pass = true;
	cout << "const peek test ";

	return pass;
}
bool test_peek_single_const()
{
	bool pass = false;
	Queue<int> base;
	base.Enqueue(3);
	const Queue<int> test(base);
	if (test.Peek() == 3)
		pass = true;
	cout << "const single peek test ";

	return pass;
}
bool test_peek_empty_const()
{
	bool pass = false;
	const Queue<int> test;
	try {
		test.Peek();
	}
	catch (Exception& e) {
		e.getMsg();
		pass = true;
	}
	cout << "const empty peek test ";

	return pass;
}
bool test_get()
{
	bool pass = false;
	Queue<int> test1;
	if (test1.isEmpty()) {
		pass = true;
	}

	Queue<int> test2(returnIntQueue());

	if (test2.getNumElements() != NUM_SIZE) {
		pass = false;
	}
	cout << "getNumElements test ";

	return pass;
}
bool test_get_const()
{
	bool pass = false;
	const Queue<int> test1;
	if (test1.isEmpty()) {
		pass = true;
	}

	const Queue<int> test2(returnIntQueue());

	if (test2.getNumElements() != NUM_SIZE) {
		pass = false;
	}
	cout << "const getNumElements test ";

	return pass;

}
bool test_empty()
{
	bool pass = false;
	Queue<int> test;
	if (test.isEmpty())
		pass = true;
	cout << "empty test ";

	return pass;
}
bool test_empty_not()
{
	bool pass = false;
	Queue<int> test(returnIntQueue());
	if (!test.isEmpty())
		pass = true;
	cout << "not empty test ";
	return pass;
}
bool test_empty_const()
{
	bool pass = false;
	const Queue<int> test;
	if (test.isEmpty())
		pass = true;
	cout << "const empty test ";

	return pass;
}
bool test_empty_not_const()
{
	bool pass = false;
	const Queue<int> test(returnIntQueue());
	if (!test.isEmpty())
		pass = true;
	cout << "const not empty test ";
	return pass;
}

bool test_default_ctor_complex()
{
	bool pass = false;

	Queue<string> test;

	if (test.isEmpty()) {
		pass = true;
	}

	cout << "complex ctor test ";
	return pass;
}
bool test_copy_ctor_complex()
{
	bool pass = false;
	Queue<string> test1;
	for (int i = 0; i < NUM_NAMES; ++i) {
		test1.Enqueue(NAMES[i]);
	}

	Queue<string> test2(test1);
	if (!test2.isEmpty()) {
		pass = true;
		for (int i = 0; i < NUM_NAMES; ++i) {
			if (test1.Dequeue() != test2.Dequeue())
				pass = false;
		}
	}
	cout << "complex copy ctor test ";
	return pass;
}
bool test_move_ctor_complex()
{
	bool pass = false;
	Queue<string> test(returnStringQueue());
	if (!test.isEmpty()) {
		pass = true;
		for (int i = 0; i < NUM_NAMES; ++i) {
			if (test.Dequeue() != NAMES[i]) {
				pass = false;
			}
		}
	}
	cout << "complex move ctor test ";
	return pass;
}
bool test_copy_op_complex()
{
	bool pass = false;
	Queue<string> test1;
	for (int i = 0; i < NUM_NAMES; ++i) {
		test1.Enqueue(NAMES[i]);
	}

	Queue<string> test2;
	test2 = test1;

	if (!test2.isEmpty()) {
		pass = true;
		for (int i = 0; i < NUM_NAMES; ++i) {
			if (test1.Dequeue() != test2.Dequeue())
				pass = false;
		}
	}
	cout << "complex copy op test ";
	return pass;
}
bool test_move_op_complex()
{
	bool pass = false;
	Queue<string> test;
	test = returnStringQueue();
	if (!test.isEmpty()) {
		pass = true;
		for (int i = 0; i < NUM_NAMES; ++i) {
			if (test.Dequeue() != NAMES[i]) {
				pass = false;
			}
		}
	}
	cout << "complex move op test ";
	return pass;
}
bool test_enqueue_complex()
{
	bool pass = false;
	Queue<string> test;
	for (int i = 0; i < NUM_NAMES; ++i) {
		test.Enqueue(NAMES[i]);
	}

	if (!test.isEmpty()) {
		pass = true;
		for (int i = 0; i < NUM_NAMES; ++i) {
			if (test.Dequeue() != NAMES[i]) {
				pass = false;
			}
		}
	}
	cout << "complex enqueue test ";
	return pass;
}
bool test_dequeue_complex()
{
	bool pass = true;
	Queue<string> test(returnStringQueue());

	for (int i = 0; i < NUM_NAMES; ++i) {
		if (test.Dequeue() != NAMES[i]) {
			pass = false;
		}
	}
	cout << "complex dequeue test ";

	return pass;
}
bool test_dequeue_single_complex()
{
	bool pass = false;
	Queue<string> test;
	test.Enqueue(NAMES[3]);

	if (test.Dequeue() == NAMES[3])
		pass = true;
	if (!test.isEmpty())
		pass = false;
	cout << "complex single dequeue test ";

	return pass;
}
bool test_dequeue_empty_complex()
{
	bool pass = false;
	Queue<string> test;

	try
	{
		test.Dequeue();
	}
	catch (Exception& e)
	{
		e.getMsg();
		pass = true;
	}
	cout << "complex empty dequeue test ";
	return pass;
}
bool test_peek_complex()
{
	bool pass = true;
	Queue<string> test(returnStringQueue());

	for (int i = 0; i < NUM_NAMES; ++i) {
		if (test.Peek() != NAMES[i])
			pass = false;
		test.Dequeue();
	}
	cout << "complex peek test ";
	return pass;
}
bool test_peek_single_complex()
{
	bool pass = false;
	Queue<string> test;
	test.Enqueue(NAMES[3]);

	if (test.Peek() == NAMES[3])
		pass = true;
	cout << "complex single peek test ";
	return pass;
}
bool test_peek_empty_complex()
{
	bool pass = false;

	Queue<string> test;
	try
	{
		test.Peek();
	}
	catch (Exception& e)
	{
		e.getMsg();
		pass = true;
	}
	cout << "complex empty peek test ";
	return pass;
}
bool test_peek_const_complex()
{
	bool pass = false;
	const Queue<string> test(returnStringQueue());

	if (test.Peek() == NAMES[0])
		pass = true;
	cout << "complex const peek test ";

	return pass;
}
bool test_peek_single_const_complex()
{
	bool pass = false;
	Queue<string> base;
	base.Enqueue(NAMES[3]);
	const Queue<string> test(base);
	if (test.Peek() == NAMES[3])
		pass = true;

	cout << "complex const single peek test ";
	return pass;
}
bool test_peek_empty_const_complex()
{
	bool pass = false;
	const Queue<string> test;
	try {
		test.Peek();
	}
	catch (Exception& e) {
		e.getMsg();
		pass = true;
	}
	cout << "complex const empty peek test ";

	return pass;
}
bool test_get_complex()
{
	bool pass = false;
	Queue<string> test1;
	if (test1.isEmpty()) {
		pass = true;
	}

	Queue<string> test2(returnStringQueue());

	if (test2.getNumElements() != NUM_NAMES) {
		pass = false;
	}
	cout << "complex getNumElements test ";

	return pass;
}
bool test_get_const_complex()
{
	bool pass = false;
	const Queue<string> test1;
	if (test1.isEmpty()) {
		pass = true;
	}

	const Queue<string> test2(returnStringQueue());

	if (test2.getNumElements() != NUM_NAMES) {
		pass = false;
	}
	cout << "complex const getNumElements test ";

	return pass;

}
bool test_empty_complex()
{
	bool pass = false;
	Queue<string> test;
	if (test.isEmpty())
		pass = true;
	cout << "complex empty test ";
	return pass;
}
bool test_empty_not_complex()
{
	bool pass = false;
	Queue<string> test(returnStringQueue());
	if (!test.isEmpty())
		pass = true;
	cout << "complex not empty test ";
	return pass;
}
bool test_empty_const_complex()
{
	bool pass = false;
	const Queue<string> test;
	if (test.isEmpty())
		pass = true;
	cout << "complex const empty test ";
	return pass;
}
bool test_empty_not_const_complex()
{
	bool pass = false;
	const Queue<string> test(returnStringQueue());
	if (!test.isEmpty())
		pass = true;

	cout << "complex const not empty test ";

	return pass;
}


Queue<int> returnIntQueue() 
{
	Queue<int> retVal;
	for (int i = 0; i < NUM_SIZE; ++i)
		retVal.Enqueue(i);

	return retVal;
}

Queue<string> returnStringQueue() 
{
	Queue<string> retVal;
	for (int i = 0; i < NUM_NAMES; ++i)
		retVal.Enqueue(NAMES[i]);

	return retVal;
}