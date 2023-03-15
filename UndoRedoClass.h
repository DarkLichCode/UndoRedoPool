/**
 * @author DarkLich
 * @date 2023.03.11
 */
#ifndef UNDOREDOPOOL_UNDOREDOCLASS_H
#define UNDOREDOPOOL_UNDOREDOCLASS_H

#include <vector>
#include <functional>
#include <future>
#include <memory>

// 撤销和重做的对象
class UndoRedoClass {
private:
	// 撤销执行的函数
	std::vector<std::function<void()>> undoFunction;

	// 重做执行的函数
	std::vector<std::function<void()>> redoFunction;

public:
	void Undo();
	void Redo();

	template<class F, class... Args>
	void MakeUndo(F&& f, Args&&... args);

	template<class F, class... Args>
	void MakeRedo(F&& f, Args&&... args);

};

void UndoRedoClass::Undo() {
	for (int i = 0; i < undoFunction.size(); ++i) {
		std::function<void()> temp = undoFunction[i];
		temp();
	}
}

void UndoRedoClass::Redo() {
	for (int i = 0; i < redoFunction.size(); ++i) {
		std::function<void()> temp = redoFunction[i];
		temp();
	}
}

template<class F, class... Args>
void UndoRedoClass::MakeUndo(F&& f, Args&&... args) {

	using return_type = typename std::result_of<F(Args...)>::type;

	auto task = std::function<return_type()>(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)
	);
	undoFunction.push_back(task);
}

template<class F, class... Args>
void UndoRedoClass::MakeRedo(F&& f, Args&&... args) {
	using return_type = typename std::result_of<F(Args...)>::type;

	auto task = std::function<return_type()>(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)
	);
	redoFunction.push_back(task);
}

#endif //UNDOREDOPOOL_UNDOREDOCLASS_H
