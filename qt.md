# 1. 信号与槽

## 1.1 元对象

当对象状态发生变化时，会发出一个信号`signal`，而用来接收处理这个信号的函数就是槽函数`slot`。信号可以通过`Qt`内部发射，也可以自定义`emit foo();`

信号槽机制的优点在于，首先保证了类型安全，信号和槽的参数类型必须匹配，同时函数指针也必须合法，否在会在编译期报错。其次信号和槽两者是松耦合，彼此之间没有关系，一个槽函数可以接收多个信号，一个信号也可以连接多个槽函数。同时如果当接收者对象被销毁时，`Qt`会自动断开连接。但是`lambda`作为槽函数在捕获对象的时候要注意，当对象已经被销毁了，此时在`lambda`中可能出现悬空的情况。例如: `connect(button, &QPushButton::clicked, nullptr, [this]() { foo(); });`

信号传递就是基于元对象系统`Meta-Object System`的。在编译期，每个`QObject`子类的`Q_OBJECT`宏通过`MOC (Meta-Object Compiler)`生成一个元对象`meta-object`。在运行期，当有一个`connect`连接时，`Qt`会在发送者对象内部维护一个连接表`connection lists`，添加一条连接记录，包含信号索引`signal index`，槽函数索引`method index`，连接类型`ConnectionType`，接收者对象指针`receiver`。

在信号发射`emit foo();`的时候，实际上`Qt`会定义一个空宏`#define emit`，编译器看到的是`foo();`而作为信号`signals: foo();`只是一个成员函数的声明，函数的实现是由`MOC`给每个信号生成`QMetaObject::activate `的调用。`activate`会首先根据`meta-object`的连接表和`signal index`找到所有连接信号的槽，对每一个`receiver`根据连接类型做处理。控件可能是内部调用`emit`，例如`QPushButton::mouseReleaseEvent()`内部会调用`emit clicked();`。

## 1.2 跨线程连接

如果是同步调用连接使用`Qt::DirectionConnection`，如果是信号发送者线程连接接收者线程，槽函数在接收者线程执行，则使用`Qt::QueuedConnection`。默认的`connect`是`Qt::AutoConnection`，如果两个对象在同一个线程使用`Qt::DirectionConnection`，否则使用`Qt::QueuedConnection`。

```cpp
QObject::connect(const QObject *sender,
                 PointerToMemberFunction signal,
                 const QObject *receiver,
                 PointerToMemberFunction method,
                 Qt::ConnectionType type = Qt::AutoConnection)
```

当跨线程连接时，发射信号时，`Qt::activate`首先会构造一个事件对象`QMetaCallEvent`加入接收者线程的事件队列中，最后在接收者线程的`EventLoop`中调用它，然后执行槽函数。如果是`Qt::DirectionConnection`，`Qt::activate`就会直接调用槽函数。

## 1.3 事件驱动

发生在线程中的所有事件都会被放入到这个线程的事件队列中，例如鼠标事件，定时器事件， `QMetaCallEvent`等等。执行事件队列就是通过事件循环`EventLoop`机制的。循环的从事件队列中取事件，分发给相应的`reveiver`，然后调用对象的事件处理函数。

一个线程必须通过`exec`创建一个`EventLoop`才能处理事件。
