# UndoRedoPool
C++实现的撤销重做函数管理池

原理是设计模式中的命令模式，将撤销时要做的操作和重做时的操作存好，并用栈存储。分为撤销栈和重做栈，执行撤销时，从撤销栈中取栈顶，执行后放入重做栈中。执行重做时同样，从重做栈中取栈顶，执行后放入撤销栈中。如果有新的撤销重做对放入重做栈中，那么会清空重做栈。

管理池使用带锁的懒汉式单例模式

```c++

// 创建管理池
std::shared_ptr<UndoRedoPool> undoRedoPool = UndoRedoPool::getInstance();
// 创建新的撤销重做对象
UndoRedoClass undoRedoClass;

// 撤销和重做函数放到对象中，如果要使用引用参数，使 std::ref将参数包裹
undoRedoClass.MakeUndo(fun1, std::ref(x), 5);
undoRedoClass.MakeUndo(fun3, std::ref(x));
undoRedoClass.MakeRedo(fun2, std::ref(x), 5);

// 将对象存入管理池中，由管理池来执行撤销和重做
undoRedoPool->SaveUndoRedo(undoRedoClass);

// 执行撤销
undoRedoPool->Undo();
// 执行重做
undoRedoPool->Redo();
```
具体用法请看main函数，也可以用于类的成员函数
