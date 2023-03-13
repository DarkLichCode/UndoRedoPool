#include <iostream>
#include "UndoRedoPool.h"

struct test{
	int id;
	std::string name;
};

void fun1(test& a) {
	a.id = 1;
	a.name = "world";
}

void fun2(test& a) {
	a.id = 0;
	a.name = "hello";
}

void printTest(test& a) {
	std::cout<<a.id<<std::endl;
	std::cout<<a.name<<std::endl;
}

int main() {
	UndoRedoClass undoRedoClass;

	test x = {
			0, "hello"
	};

	UndoRedoPool undoRedoPool;


	printTest(x);
	undoRedoClass.MakeUndo(fun1, std::ref(x));
	undoRedoClass.MakeRedo(fun2, std::ref(x));

	undoRedoPool.SaveUndoRedo(undoRedoClass);

	std::cout<<undoRedoPool.Undo()<<std::endl;
	printTest(x);
	std::cout<<undoRedoPool.Redo()<<std::endl;
	printTest(x);
	std::cout<<undoRedoPool.Redo()<<std::endl;
//	std::cout<<x<<std::endl;
	return 0;
}
