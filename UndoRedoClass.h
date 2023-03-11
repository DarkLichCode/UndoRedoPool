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
	void Undo() {
		undoFunction();
	}

	void Redo() {
		redoFunction();
	}

	template<class F, class... Args>
	void MakeUndo(F&& f, Args&&... args) {

		using return_type = typename std::result_of<F(Args...)>::type;

		auto task = std::make_shared<std::function<return_type()>>(
				std::bind(std::forward<F>(f), std::forward<Args>(args)...)
		);
	}
};


#endif //UNDOREDOPOOL_UNDOREDOCLASS_H
