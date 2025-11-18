# 1. 信号与槽

当对象状态发生变化时，会发出一个信号`signal`，而用来接收处理这个信号的函数就是槽函数`slot`。信号可以通过`Qt`内部发射，也可以自定义`emit foo();`

信号槽机制的优点在于，首先保证了类型安全，信号和槽的参数类型必须匹配，同时函数指针也必须合法，否在会在编译期报错。其次信号和槽两者是松耦合，彼此之间没有关系，一个槽函数可以接收多个信号，一个信号也可以连接多个槽函数。

信号传递就是基于元对象系统`Meta-Object System`的。在编译期，每个`QObject`子类的`Q_OBJECT`宏通过`MOC (Meta-Object Compiler)`生成一个元对象`meta-object`。在运行期，当有一个`connect`连接时，`Qt`会在对象内部维护一个连接表，记录信号与槽的连接关系。当信号`emit`时，`Qt`调用`QObject::activate()`遍历连接表，把信号传递给槽。

需要注意的是如果当接收者对象被销毁时，`Qt`会自动断开连接。`lambda`作为槽函数在捕获对象的时候要注意，当对象已经被销毁了，此时在`lambda`中可能出现悬空的情况。例如: `connect(button, &QPushButton::clicked, nullptr, [this]() { foo(); });`

在信号发射`emit foo();`的时候，实际上`Qt`会定义一个空宏`#define emit`，编译器看到的是`foo();`而作为信号`signals: foo();`只是一个成员函数的声明，函数的实现是由`MOC`给每个信号生成`QMetaObject::activate `的调用。再通过`QOjbect`的连接表遍历所有监听这个信号的槽函数，然后调用加入事件队列中。控件可能是内部调用`emit`，例如`QPushButton::mouseReleaseEvent()`内部会调用`emit clicked();`。
