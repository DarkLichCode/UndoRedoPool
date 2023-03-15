#include <iostream>
#include "UndoRedoPool.h"

struct test{
	int id;
	std::string name;
};

void fun1(test& a, int x) {
	a.id += x;
	a.name = "world";
}

void fun2(test& a, int x) {
	a.id -= x;
	a.name = "hello";
}

void fun3(test& a) {
	a.id -= 1;
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

	std::shared_ptr<UndoRedoPool> undoRedoPool = UndoRedoPool::getInstance();


//	printTest(x);
	undoRedoClass.MakeUndo(fun1, std::ref(x), 5);
	undoRedoClass.MakeUndo(fun3, std::ref(x));
	undoRedoClass.MakeRedo(fun2, std::ref(x), 5);

	undoRedoPool->SaveUndoRedo(undoRedoClass);

//	undoRedoPool->Undo();
	std::cout<<undoRedoPool->Undo()<<std::endl;
	printTest(x);
//	undoRedoPool->Redo();
	std::cout<<undoRedoPool->Redo()<<std::endl;
	printTest(x);
	std::cout<<undoRedoPool->Redo()<<std::endl;
	return 0;
}
