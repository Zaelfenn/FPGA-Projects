#define _CRTDBG_MAP_ALLOC

#include "Graph.h"

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

void output(int data) {
	cout << data << endl;
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Graph<int, string> meow;
	meow.InsertVertex(5);
	meow.InsertArc(5, 5, "meow", 0);
	meow.InsertVertex(12);
	meow.InsertArc(5, 12, "woof", 12);
	//meow.BreadthFirst(output);
	meow.InsertVertex(14);
	meow.InsertVertex(15);
	meow.InsertArc(5, 15, "grrr", 10);
	meow.InsertArc(12, 14, "arf", 2);
	Graph<int, string> woof(meow);
	Graph<int, string> rawr;
	rawr = woof;
	//meow.DepthFirst(output);
	//meow.BreadthFirst(output);
	meow.DeleteVertex(15);
//	meow.BreadthFirst(output);
	meow.DeleteArc(12, 14);
	meow.BreadthFirst(output);
	woof.BreadthFirst(output);
	rawr.BreadthFirst(output);
	return 0;
}