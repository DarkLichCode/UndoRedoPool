/**
 * @author DarkLich
 * @date 2023.03.11
 */
#ifndef UNDOREDOPOOL_UNDOREDOPOOL_H
#define UNDOREDOPOOL_UNDOREDOPOOL_H

#include <stack>
#include "UndoRedoClass.h"

class UndoRedoPool {
private:
	std::stack<UndoRedoClass> undoStack;
	std::stack<UndoRedoClass> redoStack;

public:
	void SaveUndoRedo(UndoRedoClass undoredo);
	bool Undo();
	bool Redo();
	bool CanUndo();
	bool CanRedo();
};

// 添加UndoRedo的方法
void UndoRedoPool::SaveUndoRedo(UndoRedoClass undoredo) {
	this->undoStack.push(undoredo);
	while (!this->redoStack.empty()) {
		this->redoStack.pop();
	}
}

// 执行撤销
bool UndoRedoPool::Undo() {

	if (this->undoStack.empty()) {
		return false;
	}

	UndoRedoClass save = this->undoStack.top();
	this->undoStack.pop();
	save.Undo();
	this->redoStack.push(save);
	return true;
}

// 执行重做
bool UndoRedoPool::Redo() {
	if (this->redoStack.empty()) {
		return false;
	}

	UndoRedoClass save = this->redoStack.top();
	this->redoStack.pop();
	save.Redo();
	this->undoStack.push(save);
	return true;
}

// 能否撤销
bool UndoRedoPool::CanUndo() {
	if (this->undoStack.empty()) {
		return false;
	}
	return true;
}

// 能否重做
bool UndoRedoPool::CanRedo() {
	if (this->redoStack.empty()) {
		return false;
	}
	return true;
}

#endif //UNDOREDOPOOL_UNDOREDOPOOL_H
