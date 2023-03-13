/**
 * @author DarkLich
 * @date 2023.03.11
 */
#ifndef UNDOREDOPOOL_UNDOREDOCLASS_H
#define UNDOREDOPOOL_UNDOREDOCLASS_H

#include <functional>
#include <future>
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

	template<class F, class... Args>
	void MakeRedo(F&& f, Args&&... args);

};

void UndoRedoClass::Undo() {
	undoFunction();
}

void UndoRedoClass::Redo() {
	redoFunction();
}

template<class F, class... Args>
void UndoRedoClass::MakeUndo(F&& f, Args&&... args) {

	using return_type = typename std::result_of<F(Args...)>::type;

	auto task = std::function<return_type()>(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)
	);

	undoFunction = task;
}

template<class F, class... Args>
void UndoRedoClass::MakeRedo(F&& f, Args&&... args) {
	using return_type = typename std::result_of<F(Args...)>::type;

	auto task = std::function<return_type()>(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)
	);

	redoFunction = task;
}

#endif //UNDOREDOPOOL_UNDOREDOCLASS_H
