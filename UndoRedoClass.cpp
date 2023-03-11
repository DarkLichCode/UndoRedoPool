/**
 * @author DarkLich
 * @date 2023.03.11
 */
#include "UndoRedoClass.h"

void UndoRedoClass::Undo() {
	undoFunction();
}

void UndoRedoClass::Redo() {
	redoFunction();
}

template<class F, class... Args>
void UndoRedoClass::MakeUndo(F&& f, Args&&... args) {

	using return_type = typename std::result_of<F(Args...)>::type;

	auto task = std::make_shared<std::function<return_type()>>(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)
	);
}