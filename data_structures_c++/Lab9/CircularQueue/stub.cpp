/**********************************************************************
* 
* 
* 
* Author: Zaelfenn Sandow
* 
* 
* Project Name: Circular Queue
* 
* 
* 
* Project Purpose: Create a circular queue class. This circular queue 
* should make use of a preestablished array class, which contains
* the proper amount of space for the items in the queue. This class
* should throw exceptions when accessing out of bounds, both overflow
* and underflow. The class should be able to return its own size. The 
* class should be able to tell when it is full or empty. The class 
* should have all regular manager functions, and a manager function which
* takes an integer argument for the size.
* 
* Date created: April 26th, 2024
* 
* 
************************************************************************/

#include "CircularQueue.h"

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
bool test_full();
bool test_full_not();
bool test_full_const();
bool test_full_not_const();

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
bool test_full_complex();
bool test_full_not_complex();
bool test_full_const_complex();
bool test_full_not_const_complex();



FunctionPointer fun_point[] = { test_default_ctor, test_copy_ctor,test_move_ctor, test_copy_op ,test_move_op ,test_enqueue ,test_dequeue ,
								test_dequeue_single ,test_dequeue_single, test_dequeue_empty,test_peek, test_peek_single,test_peek_empty,
								test_peek_const, test_peek_single_const, test_peek_empty_const, test_get, test_get_const,test_empty, test_empty_not,
								test_empty_const,test_empty_not_const , test_full ,test_full_not,test_full_const, test_full_not_const,

								test_default_ctor_complex, test_copy_ctor_complex, test_move_ctor_complex, test_copy_op_complex , test_move_op_complex,
								test_enqueue_complex, test_dequeue_complex, test_dequeue_single_complex, test_dequeue_empty_complex, test_peek_complex,
								test_peek_single_complex ,test_peek_empty_complex, test_peek_const_complex, test_peek_single_const_complex,test_peek_empty_const_complex,
								test_get_complex , test_get_const_complex ,test_empty_complex, test_empty_not_complex, test_empty_const_complex,  test_empty_not_const_complex,
								test_full_complex ,test_full_not_complex, test_full_const_complex, test_full_not_const_complex };

Queue<int> returnIntQueue();
Queue<string> returnStringQueue();


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
	if (test.isEmpty() && test.getSize() == 0) {
		pass = true;
	}
	cout << "Default Ctor test: ";
	return pass;
}
bool test_copy_ctor()
{
	bool pass = false;
	Queue<int> copy(NUM_SIZE);
	for (int i = 0; i < NUM_SIZE; ++i) {
		copy.Enqueue(i);
	}
	Queue<int> test(copy);
	if (test.getSize() == copy.getSize()) {
		pass = true;
		for (int i = 0; i < NUM_SIZE; ++i) {
			if (test.Dequeue() != copy.Dequeue())
				pass = false;
		}
	}

	cout << "Copy Ctor test: ";
	return pass;
}
bool test_move_ctor()
{
	bool pass = false;
	Queue<int> test(returnIntQueue());
	if (test.getSize() == returnIntQueue().getSize()) {
		pass = true;
		for (int i = 0; i < NUM_SIZE; ++i) {
			if (test.Dequeue() != i)
				pass = false;
		}
	}
	cout << "Move Ctor test: ";
	return pass;
}
bool test_copy_op()
{
	bool pass = false;
	Queue<int> copy(NUM_SIZE);
	for (int i = 0; i < NUM_SIZE; ++i) {
		copy.Enqueue(i);
	}
	Queue<int> test;
	test = copy;
	if (test.getSize() == copy.getSize()) {
		pass = true;
		for (int i = 0; i < NUM_SIZE; ++i) {
			if (test.Dequeue() != copy.Dequeue())
				pass = false;
		}
	}

	cout << "Copy Operator test: ";
	return pass;
}
bool test_move_op()
{
	bool pass = false;
	Queue<int> test;
	test = returnIntQueue();

	if (test.getSize() == returnIntQueue().getSize()) {
		pass = true;
		for (int i = 0; i < NUM_SIZE; ++i) {
			if (test.Dequeue() != i)
				pass = false;
		}
	}
	cout << "Move Operator test: ";
	return pass;
}
bool test_enqueue()
{
	bool pass = false;
	Queue<int> test(NUM_SIZE);
	for (int i = 0; i < NUM_SIZE; ++i) {
		test.Enqueue(i);
	}

	if (test.isFull()) {
		pass = true;
		for (int i = 0; i < NUM_SIZE; ++i) {
			if (test.Dequeue() != i) {
				pass = false;
			}
		}
	}
	cout << "Enqueue test: ";
	return pass;
}
bool test_dequeue()
{
	bool pass = false;
	Queue<int> test(NUM_SIZE);
	for (int i = 0; i < NUM_SIZE; ++i) {
		test.Enqueue(i);
	}

	if (test.isFull()) {
		pass = true;
		for (int i = 0; i < NUM_SIZE; ++i) {
			if (test.Peek() != i) {
				pass = false;
			}
			test.Dequeue();
		}
	}
	if (!test.isEmpty())
		pass = false;
	
	cout << "Dequeue test: ";
	return pass;
}
bool test_dequeue_single()
{
	bool pass = false;
	Queue<int> test(1);
	test.Enqueue(1);
	if (test.isFull() && test.Dequeue() == 1) {
		pass = true;
	}
	if (!test.isEmpty()) {
		pass = false;
	}
	cout << "Dequeue single test: ";
	return pass;
}
bool test_dequeue_empty()
{
	bool pass = false;
	Queue<int> test;
	try {
		test.Dequeue();
	}
	catch (Exception& e) {
		e.getMsg();
		pass = true;
	}
	bool pass1 = false;
	Queue<int> test1(5);
	try {
		test1.Dequeue();
	}
	catch (Exception& e) {
		e.getMsg();
		pass1 = true;
	}
	cout << "Dequeu empty test: ";
	return pass && pass1;
}
bool test_peek()
{
	bool pass = false;
	Queue<int> test(NUM_SIZE);
	for (int i = 0; i < NUM_SIZE; ++i) {
		test.Enqueue(i);
	}
	if (test.isFull()) {
		pass = true;
		for (int i = 0; i < NUM_SIZE; ++i) {
			if (test.Peek() != i)
				pass = false;
			test.Dequeue();
		}
	}

	cout << "Peek test: ";
	return pass;
}
bool test_peek_single()
{
	bool pass = false;
	Queue<int> test(1);
	test.Enqueue(1);
	if (test.Peek() == 1) {
		pass = true;
	}
	cout << "Single Peek test: ";
	return pass;
}
bool test_peek_empty()
{
	bool pass = false;
	Queue<int> test;

	try {
		test.Peek();
	}
	catch (Exception& e) {
		e.getMsg();
		pass = true;
	}

	bool pass1 = false;
	Queue<int> test1(NUM_SIZE);

	try {
		test.Peek();
	}
	catch (Exception& e) {
		e.getMsg();
		pass1 = true;
	}

	cout << "Empty Peek test: ";
	return pass && pass1;
}
bool test_peek_const()
{
	bool pass = false;
	const Queue<int> test(returnIntQueue());

	if (test.Peek() == 0)
		pass = true;

	cout << "const Peek test: ";
	return pass;
}
bool test_peek_single_const()
{
	bool pass = false;
	Queue<int> copy(1);
	copy.Enqueue(1);
	const Queue<int> test(copy);

	if (test.Peek() == 1)
		pass = true;
	cout << "const Single Peek test: ";
	return pass;
}
bool test_peek_empty_const()
{
	bool pass = false;
	bool pass1 = false;
	const Queue<int> test;
	const Queue<int> test1(NUM_SIZE);

	try {
		test.Peek();
	}
	catch (Exception& e) {
		e.getMsg();
		pass = true;
	}

	try {
		test1.Peek();
	}
	catch (Exception& e) {
		e.getMsg();
		pass1 = true;
	}
	cout << "Peek Empty Test: ";
	return pass && pass1;
}
bool test_get()
{
	bool pass = false;

	Queue<int> test(NUM_SIZE);

	if (test.getSize() == NUM_SIZE)
		pass = true;

	cout << "getSize test: ";
	return pass;
}
bool test_get_const()
{
	bool pass = false;

	const Queue<int> test(NUM_SIZE);

	if (test.getSize() == NUM_SIZE)
		pass = true;
	cout << "const getSize test: ";

	return pass;
}
bool test_empty()
{
	bool pass = false;

	Queue<int> test(NUM_SIZE);

	if (test.isEmpty())
		pass = true;

	cout << "Empty test: ";
	return pass;
}
bool test_empty_not()
{
	bool pass = false;

	Queue<int> test(returnIntQueue());

	test.Dequeue();
	test.Dequeue();
	test.Enqueue(0);
	test.Enqueue(1);
	if (!test.isEmpty())
		pass = true;

	cout << "Not Empty test: ";
	return pass;
}
bool test_empty_const()
{
	bool pass = false;

	const Queue<int> test;

	if (test.isEmpty())
		pass = true;

	cout << "const Empty test: ";
	return pass;
}
bool test_empty_not_const()
{
	bool pass = false;

	const Queue<int> test(returnIntQueue());

	if (!test.isEmpty())
		pass = true;

	cout << "const Not Empty test: ";
	return pass;
}
bool test_full()
{
	bool pass = false;

	Queue<int> test(returnIntQueue());

	test.Dequeue();
	test.Dequeue();
	test.Enqueue(0);
	test.Enqueue(1);
	if (test.isFull())
		pass = true;

	cout << "isFull test: ";
	return pass;
}
bool test_full_not()
{
	bool pass = false;

	Queue<int> test(returnIntQueue());

	test.Dequeue();
	test.Dequeue();
	if (!test.isFull())
		pass = true;

	cout << "Not Full test: ";
	return pass;
}
bool test_full_const()
{
	bool pass = false;

	const Queue<int> test(returnIntQueue());


	if (test.isFull())
		pass = true;

	cout << "const isFull test: ";
	return pass;
}
bool test_full_not_const()
{
	bool pass = false;

	const Queue<int> test(4);

	if (!test.isFull())
		pass = true;

	cout << "const Not Full test: ";
	return pass;
}

bool test_default_ctor_complex()
{
	bool pass = false;
	Queue<string> test;
	if (test.isEmpty() && test.getSize() == 0) {
		pass = true;
	}
	cout << "complex Default Ctor test: ";
	return pass;
}
bool test_copy_ctor_complex()
{
	bool pass = false;
	Queue<string> copy(NUM_NAMES);
	for (int i = 0; i < NUM_NAMES; ++i) {
		copy.Enqueue(NAMES[i]);
	}
	Queue<string> test(copy);
	if (test.getSize() == copy.getSize()) {
		pass = true;
		for (int i = 0; i < NUM_NAMES; ++i) {
			if (test.Dequeue() != copy.Dequeue())
				pass = false;
		}
	}
	cout << "complex Copy Ctor test: ";
	return pass;
}
bool test_move_ctor_complex()
{
	bool pass = false;
	Queue<string> test(returnStringQueue());
	if (test.getSize() == returnStringQueue().getSize()) {
		pass = true;
		for (int i = 0; i < NUM_NAMES; ++i) {
			if (test.Dequeue() != NAMES[i])
				pass = false;
		}
	}
	cout << "complex Move Ctor test: ";
	return pass;
}
bool test_copy_op_complex()
{
	bool pass = false;
	
	Queue<string> copy(NUM_NAMES);
	for (int i = 0; i < NUM_NAMES; ++i) {
		copy.Enqueue(NAMES[i]);
	}
	Queue<string> test;
	test = copy;
	if (test.getSize() == copy.getSize()) {
		pass = true;
		for (int i = 0; i < NUM_NAMES; ++i) {
			if (test.Dequeue() != copy.Dequeue())
				pass = false;
		}
	}

	cout << "complex Copy Operator test: ";
	return pass;
}
bool test_move_op_complex()
{
	bool pass = false;
	Queue<string> test;
	test = returnStringQueue();

	if (test.getSize() == returnStringQueue().getSize()) {
		pass = true;
		for (int i = 0; i < NUM_NAMES; ++i) {
			if (test.Dequeue() != NAMES[i])
				pass = false;
		}
	}
	cout << "complex Move Operator test: ";
	return pass;
}
bool test_enqueue_complex()
{
	bool pass = false;
	Queue<string> test(NUM_NAMES);
	for (int i = 0; i < NUM_NAMES; ++i) {
		test.Enqueue(NAMES[i]);
	}

	if (test.isFull()) {
		pass = true;
		for (int i = 0; i < NUM_SIZE; ++i) {
			if (test.Dequeue() != NAMES[i]) {
				pass = false;
			}
		}
	}
	cout << "complex Enqueue test: ";
	return pass;
}
bool test_dequeue_complex()
{
	bool pass = false;
	Queue<string> test(NUM_NAMES);
	for (int i = 0; i < NUM_NAMES; ++i) {
		test.Enqueue(NAMES[i]);
	}

	if (test.isFull()) {
		pass = true;
		for (int i = 0; i < NUM_NAMES; ++i) {
			if (test.Dequeue() != NAMES[i]) {
				pass = false;
			}
		}
	}
	cout << "complex Dequeue test: ";
	return pass;
}
bool test_dequeue_single_complex()
{
	bool pass = false;
	Queue<string> test(1);
	test.Enqueue(NAMES[1]);
	if (test.isFull() && test.Dequeue() == NAMES[1]) {
		pass = true;
	}
	if (!test.isEmpty()) {
		pass = false;
	}
	cout << "complex Dequeue single test: ";
	return pass;
}
bool test_dequeue_empty_complex()
{
	bool pass = false;
	Queue<string> test;
	try {
		test.Dequeue();
	}
	catch (Exception& e) {
		e.getMsg();
		pass = true;
	}
	bool pass1 = false;
	Queue<string> test1(5);
	try {
		test1.Dequeue();
	}
	catch (Exception& e) {
		e.getMsg();
		pass1 = true;
	}
	cout << "complex Dequeue empty test: ";

	return pass && pass1;
}
bool test_peek_complex()
{
	bool pass = false;
	Queue<string> test(returnStringQueue());

	if (test.isFull()) {
		pass = true;
		for (int i = 0; i < NUM_NAMES; ++i) {
			if (test.Peek() != NAMES[i]) {
				pass = false;
			}
			test.Dequeue();
		}
	}
	cout << "complex Peek test: ";
	return pass;
}
bool test_peek_single_complex()
{
	bool pass = false;
	Queue<string> test(1);
	test.Enqueue(NAMES[1]);
	if (test.Peek() == NAMES[1]) {
		pass = true;
	}

	cout << "complex Single Peek test: ";
	return pass;
}
bool test_peek_empty_complex()
{
	bool pass = false;
	Queue<string> test;

	try {
		test.Peek();
	}
	catch (Exception& e) {
		e.getMsg(); 
		pass = true;
	}

	bool pass1 = false;
	Queue<string> test1(NUM_SIZE);

	try {
		test.Peek();
	}
	catch (Exception& e) {
		e.getMsg();
		pass1 = true;
	}

	cout << "complex Empty Peek test: ";
	return pass;
}
bool test_peek_const_complex()
{
	bool pass = false;
	const Queue<string> test(returnStringQueue());

	if (test.Peek() == NAMES[0])
		pass = true;

	cout << "complex const Peek test: ";
	return pass;
}
bool test_peek_single_const_complex() 
{
	bool pass = false;
	Queue<string> copy(1);
	copy.Enqueue(NAMES[1]);
	const Queue<string> test(copy);

	if (test.Peek() == NAMES[1])
		pass = true;
	cout << "complex const Single Peek test: ";
	return pass;
}
bool test_peek_empty_const_complex()
{
	bool pass = false;
	bool pass1 = false;
	const Queue<string> test;
	const Queue<string> test1(NUM_NAMES);

	try {
		test.Peek();
	}
	catch (Exception& e) {
		e.getMsg();
		pass = true;
	}

	try {
		test1.Peek();
	}
	catch (Exception& e) {
		e.getMsg();
		pass1 = true;
	}
	cout << "complex const Peek Empty test: ";
	return pass && pass1;
}
bool test_get_complex()
{
	bool pass = false;

	Queue<string> test(NUM_NAMES);

	if (test.getSize() == NUM_NAMES)
		pass = true;

	cout << "complex getSize test: ";
	return pass;
}
bool test_get_const_complex()
{
	bool pass = false;

	const Queue<string> test(NUM_NAMES);

	if (test.getSize() == NUM_NAMES)
		pass = true;
	cout << "const complex getSize test: ";

	return pass;
}
bool test_empty_complex()
{
	bool pass = false;

	Queue<string> test(NUM_NAMES);

	if (test.isEmpty())
		pass = true;

	cout << "complex Empty test: ";
	return pass;
}
bool test_empty_not_complex()
{
	bool pass = false;

	Queue<string> test(returnStringQueue());

	test.Dequeue();
	test.Dequeue();
	test.Enqueue(NAMES[3]);
	test.Enqueue(NAMES[4]);
	if (!test.isEmpty())
		pass = true;

	cout << "complex Not Empty test: ";
	return pass;
}
bool test_empty_const_complex()
{
	bool pass = false;

	const Queue<string> test;

	if (test.isEmpty())
		pass = true;

	cout << "complex const Empty test: ";
	return pass;
}
bool test_empty_not_const_complex()
{
	bool pass = false;

	const Queue<string> test(returnStringQueue());

	if (!test.isEmpty())
		pass = true;

	cout << "complex const Not Empty test: ";
	return pass;
}
bool test_full_complex() 
{
	bool pass = false;

	Queue<string> test(returnStringQueue());

	test.Dequeue();
	test.Dequeue();
	test.Enqueue(NAMES[3]);
	test.Enqueue(NAMES[4]);
	if (test.isFull())
		pass = true;

	cout << "complex isFull test: ";
	return pass;
}
bool test_full_not_complex()
{
	bool pass = false;

	Queue<string> test(returnStringQueue());

	test.Dequeue();
	test.Dequeue();
	if (!test.isFull())
		pass = true;

	cout << "complex Not Full test: ";
	return pass;
}
bool test_full_const_complex()
{
	bool pass = false;

	const Queue<string> test(returnStringQueue());


	if (test.isFull())
		pass = true;

	cout << "const complex isFull test: ";
	return pass;
}
bool test_full_not_const_complex()
{
	bool pass = false;

	const Queue<string> test(4);

	if (!test.isFull())
		pass = true;

	cout << "const complex Not Full test: ";
	return pass;
}



Queue<int> returnIntQueue() 
{
	Queue<int> retVal(NUM_SIZE);
	for (int i = 0; i < NUM_SIZE; ++i) {
		retVal.Enqueue(i);
	}

	return retVal;
}
Queue<string> returnStringQueue()
{
	Queue<string> retVal(NUM_NAMES);
	for (int i = 0; i < NUM_NAMES; ++i) {
		retVal.Enqueue(NAMES[i]);
	}

	return retVal;
}