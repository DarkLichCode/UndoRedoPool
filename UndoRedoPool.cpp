/**
 * @author DarkLich
 * @date 2023.03.11
 */
#include "UndoRedoPool.h"

void UndoRedoPool::SaveUndoRedo(UndoRedoClass undoredo) {
	this->undoStack.push(undoredo);
	while (!this->redoStack.empty()) {
		this->redoStack.pop();
	}
}

void UndoRedoPool::Undo() {
	UndoRedoClass save = this->undoStack.top();
	this->undoStack.pop();
	save.Undo();
	this->redoStack.push(save);
}
void UndoRedoPool::Redo() {
	UndoRedoClass save = this->redoStack.top();
	this->redoStack.pop();
	save.Redo();
	this->undoStack.push(save);
}
