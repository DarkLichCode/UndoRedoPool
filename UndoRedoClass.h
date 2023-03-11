/**
 * @author DarkLich
 * @date 2023.03.11
 */
#ifndef UNDOREDOPOOL_UNDOREDOCLASS_H
#define UNDOREDOPOOL_UNDOREDOCLASS_H

#include <functional>
#include <memory>

class UndoRedoClass {
private:
	std::function<void()> undoFunction;
	std::function<void()> redoFunction;

public:
	void Undo();

	void Redo();

	template<class F, class... Args>
	void MakeUndo(F&& f, Args&&... args);
};


#endif //UNDOREDOPOOL_UNDOREDOCLASS_H
