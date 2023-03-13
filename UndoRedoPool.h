/**
 * @author DarkLich
 * @date 2023.03.11
 */
#ifndef UNDOREDOPOOL_UNDOREDOPOOL_H
#define UNDOREDOPOOL_UNDOREDOPOOL_H

#include <stack>
#include <mutex>
#include "UndoRedoClass.h"



class UndoRedoPool {
private:
	std::stack<UndoRedoClass> undoStack;
	std::stack<UndoRedoClass> redoStack;
	static std::shared_ptr<UndoRedoPool> instance;
	static std::mutex mtx;

	UndoRedoPool() {}

public:

	static std::shared_ptr<UndoRedoPool> getInstance() {
		//两个NULL可以提高获取实例效率
		if (instance == nullptr) {
			mtx.lock();
			if (instance == nullptr) {
				instance = std::shared_ptr<UndoRedoPool>(new UndoRedoPool());
			}
			mtx.unlock();
		}
		return instance;
	}

	void SaveUndoRedo(UndoRedoClass undoredo);
	bool Undo();
	bool Redo();
	bool CanUndo();
	bool CanRedo();
};

std::mutex UndoRedoPool::mtx;
std::shared_ptr<UndoRedoPool> UndoRedoPool::instance = nullptr;

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
