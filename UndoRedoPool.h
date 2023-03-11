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
	void Undo();
	void Redo();
};


#endif //UNDOREDOPOOL_UNDOREDOPOOL_H
