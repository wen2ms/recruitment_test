# 1 发展历史

从发展历史来看C++是在C的基础上发展来的。

# 2 程序设计思想

C是面向过程`Procedural Programming`，通过函数来组织程序，同时引入了结构体对应类，但是结构体中不能包含函数，因此函数指针对应类的成员函数，用组合实现继承和多态，因此也能实现`OOP (Oriented-Object Programging)`。而C++设计之初就是面向对象，包含类，继承，多态这样的`OOP`特性，同时也利用`template`和 `std::forward`实现较好的泛型编程。

C++是`OOP`语言，对于设计模式的实现更加简洁。

## 2.1 类的关系
1. 关联关系，例如计算机由鼠标组成，但计算机可以没有鼠标，鼠标也可以在计算机外单独存在。
2. 聚合关系，整体和部分的关系，例如班级由学生组成。
3. 组合关系，也是整体和部分的关系，但是这个部分离开了整体就不存在了，例如人体和心脏。
4. 依赖关系，是一种临时使用的关系，例如打印机和驱动程序。

## 2.2 单例模式

单例模式`Singleton pattern`的实现可以通过饿汉模式`Eager singleton`和懒汉模式`Lazy singleton`实现，饿汉模式在单例类定义时就进行分配堆内存。而懒汉模式有三种方式实现，前两种都通过分配堆内存，一种是返回静态局部变量的指针。

直接分配堆内存会出现线程安全。

第一种首先通过双重检查锁定，但因为机器指令的执行顺序有可能将分配内存，赋值，用指针指向内存，这三步颠倒，导致一个线程中指针已经不为空，而另一个线程中指针为空，这还会导致线程不安全，可以原子变量来解决。

第二种是直接通过`std::call_once`来保证只有一个线程执行`new`。

最后一种懒汉模式的实现就是`get_instance`直接返回静态局部变量的指针，也是线程安全的。

对于类中静态变量指向的堆内存，不释放会导致内存泄漏，最简单的方法就是在懒汉模式下直接返回静态局部变量的指针，或者就是通过`std::unqiue_ptr`和`std::call_once`实现。但一般来说，单例对象的生命周期和程序生命周期一致，所以最后手动`delete`即可。

## 2.3 观察者模式

观察者模式`Observer pattern`的双方一方是发布者，一方是观察者，观察者通过自己的`subscribe`来调用发布者`attach`，双方建立联系，发布者也获得了观察者列表。当发布者`notify`一条消息时调用观察者的`update`方法，此时观察者消息就获得了发布者推送的消息。

# 3 语言特性

C更接近底层，内存管理主要通过`malloc, calloc, realloc`和`free`。

## 3.1 RAII

现代C++通过`RAII (Resource Acquisition Is Initialization)`，资源获得即初始化，结合构造和析构的思想对资源进行安全的管理，例如`std::lock_guard`可以对`mutex`进行管理。

### 3.1.1 智能指针

智能指针通过引用计数进行堆内存的管理，当智能指针离开它的作用域后就会将管理的内存的引用计数减1，当引用计数为0时，就自动调用删除器释放这个内存，`std::weak_ptr`它只是用来监控`std::shared_ptr`，不增加引用计数，当需要使用它监控的`std::shared_ptr`，需要使用`lock`方法。

需要注意：

1. 循环引用。常见的就是两个类对象都保存的各自`std::shared_ptr`，然后又互相指向对方，导致引用计数永远不为0。解决方法就是在一个类中使用`std::weak_ptr`来监控另一个类对象。

2. 用一个原始地址初始化多个智能指针。

3. 用一个指向单个指针的智能指针管理了一个数组，`std::shared_ptr<int> arr(new int[10]);`，正确做法是`std::shared_ptr<int[]> arr(new int[10]);`

4. 函数返回指向`this`的智能指针。正确做法是类要继承`enbale_shared_from_this<T>`类，函数返回时返回`shared_from_this()`。这个父类有一个`std::weak_ptr`来监测指向子类对象的`std::shared_ptr`，此时再赋值就会让智能指针的引用计数加1。

5. `std::shared_ptr`中的引用计数机制是线程安全的，例如这样的值拷贝。

    ```cpp
    std::shared_ptr<int> ptr = std::make_shared<int>(42);
    std::thread thread1([ptr](){});
    std::thread thread2([ptr](){});
    ```

    但是`std::shared_ptr`本身和管理的对象不是线程安全的，例如下面这种情况就不是线程安全的。

    ```cpp
    std::shared_ptr<int> ptr = std::make_shared<int>(42);
    std::thread thread1([&ptr](){ ptr = std::make_shared<int>(3) });
    std::thread thread2([&ptr](){ ptr = std::make_shared<int>(4) });
    ```

    而`std::unique_ptr`是不能跨线程的，只能有一个线程拥有，必须通过移动语义来转移，因此它是线程安全的。

6. `std::unique_ptr` `delete`了拷贝构造函数，因此在向容器中插入的时候不能直接插入。

    ```cpp
    std::vector<std::unique_ptr<int>> vec;
    std::unique_ptr<int> ptr(new int(4));
    vec.push_back(std::move(ptr));
    vec.push_back(std::make_unique<int>(5));
    vec.emplace_back(new int(4));

## 3.2 **多态**

C++的多态分为两种：

### 3.2.1 编译时多态。

不影响运行速度，包括函数重载和模版。对于函数重载，编译器会将函数名+参数类型编码成一个内部符号名，编译时根据实参类型选择合适的函数。而模版会在编译时编译器根据实参类型生成对应的类或者函数，也就是模版实例化的过程，不同参数是互相独立的，结果就像编译器按照模版参数自动生成了多个重载函数。

#### 3.2.1.1 template

1. 函数模版可以避免重复定义多个重载函数，类模版可以让类内部使用的变量类型更加多样。相对于`#define`在预处理阶段直接进行的文本替换，`template`在编译时就会进行类型检查，可以调试。例如：

```cpp
#define ADD(a, b) ((a) + (b))

template <class T>
T add(T a, T b) {
    return a + b;
}

int main() {
    ADD(3, "hello");
    // error
    add(3, "hello");
    return 0;
}
```

​	但是，宏定义会有重复求值，没有类型检查，不可调试等缺点。例如：

```cpp
#define ABS(x) x > 0 ? x : -x

int main()  {
    int x = 1;
    ABS(x++);
  
    ABS("foo");
    return 0;
}
```



2. 在需要某些类型和其他模版类型不一样的行为时，就可以进行全特化实现。当需要某种类组合的行为和其他组合不一样时就可以使用偏特化。
3. 右值引用在传递时，由于已经具名化了，所以被对待成一个左值。例如：不允许将一个左值赋值给右值引用`int&& foo = 1; int&& bar = foo;`。
4. 在利用右值引用和`template`进行类型推导时，只有右值才能推导出右值引用，也就是`T&& foo = 3;`。其他情况都推导出的是左值引用`T&& foo = num;`。同时要注意`const T&&`本身就是一个右值引用，不需要进行类型推导。
5. 配合`std::forward`的时候要注意，它只会将左值引用转化为左值，其余情况都是转化为右值。

#### 3.2.1.2 auto

`auto`是自动类型推导关键字。它是在编译期完成的类型推导，它和`template`所用的类型推导规则是一致的，因此对于右值引用的规则是一致的，但是有几个注意事项：

1. `auto`声明的时候必须要有初始值。
2. `auto`不保留引用和`const`，需要显示声明，否则直接对引用的类型推导是值类型。例如：

```cpp
// const int
const num = 3;
// const int&
auto& foo = num;
// const int*
auto* foo = num;
```
3. 数组通过`auto`推导会退化为指针类型。

### 3.2.2 运行时多态。

通过继承和虚函数来实现的，只有在运行的时候才知道调用哪个函数。每个包含虚函数的类，编译器会为它生成一个虚函数表`vtable`，里面存储了虚函数的函数指针。每个对象内部在编译期就会构造一个指向虚函数表的虚表指针`vptr`位置，当运行时，对象构造期间`vptr`就会指向`vtable`的地址，然后指向子类对象的父类指针或者引用通过`vtable`中的函数指针就能实现多态了。需要注意：

- 析构函数往往也要定义为虚函数，避免父类指针直接调用父类的析构函数，而不调用真正指向的子类的析构函数。

- 构造函数不会调用子类的虚函数。vptr的初始化和对象的初始化是一致的，当子类对象构造时，先构造父类部分，再构造子类部分，当调用父类的构造函数的时候`vptr`指向是父类的虚函数。

  ```cpp
  struct Base {
      Base() {
          foo();
      }
      virtual void foo() {
          std::cout << "Base foo\n";
      }
  };
  
  struct Derived : Base {
      Derived() = default;
      void foo() override {
          std::cout << "Derived foo\n";
      }
  };
  
  int main() {
      Derived d;
  }
  ```
  
 - 虚函数不能带默认参数。默认参数是在编译期绑定的，而虚函数是在运行时确定要调用哪一个函数，因此会出现实际调用的虚函数的参数和默认参数不一致的情况。

 - 如果一个抽象类中只有纯虚函数，那么这个抽象类也被称为接口，这是和其他语言中定义关键字不一样的。

与虚函数相似的还有虚继承，虚继承是为了解决棱形继承的问题，它通过维护一个`vbtable (Virtual Base Table)`虚基类表，使得最派生类中只有一个虚基类实例，继承的中间类实例会有一个`vbptr`虚基类表指针，以此来使多个中间继承的类实例最终指向同一个虚基类实例，只有最派生类会调用虚基类的构造函数。例如：

```cpp
class Animal {
  public:
    explicit Animal(int num) {
        std::cout << "num = " << num << '\n';
    }

    static int age_;
};

class Sheep : virtual public Animal {
  public:
    Sheep() : Animal(1) {}
};

class Camel : virtual public Animal {
  public:
    Camel() : Animal(2) {}
};

class Llama : public Sheep, public Camel {
  public:
    Llama() : Sheep(), Camel(), Animal(3) {}
};
```

### 3.3.3 RTTI

`RTTI (Run-Time Type Information)`运行时类型信息。例如

```cpp
Base* base = new Derived;
Derived* derived = std::dynamic_cast<Derived*>(base);
```

如果`base`不是指向子类的话，`dynamic_cast`就会抛出`std::bad_cast`（引用）或`nullptr`（指针）。

`RTTI`依赖于`vtable`，虚函数表中一般除了存储函数指针还存储了对象所属类信息`type_info`。

### 3.3.4 函数指针

函数指针的调用方式以及参数是在编译期确定的，但它因为允许指向的函数地址可以改变，因此可以实现类似面向对象的运行时多态。最常用的方法有

1. 回调函数`callback`。例如：

```cpp
 using handle_func = std::function<int(void*)>;
 Channel(int fd, FDEvents events, handle_func read_func, void* arg);
```

2. 策略模式实现函数的动态选择。

  ```cpp
  int add(int op1, int op2) { return op1 + op2 };
  int sub(int op1, int op2) { return op1 - op2 };
  // int (*ops[])(int, int) = { op1, op2 };
  int (*select_operation(char operation))(int, int) {
      if (operation == '+') {
          return add;
      } else if (operation == '-') {
          return sub;
      }
  }
  ```

3. 通过结构体中定义的函数指针成员就可以实现多态。

  ```cpp
  struct Dispatcher {
      void* (*init)();
      int (*add)(struct Channel*, struct EventLoop*);
  };

  struct Dispatcher epoll_dispatcher = {epoll_init, epoll_add};
  ```

4. 可调用对象有四种：函数指针，仿函数，可以转化为函数指针的对象，类成员指针，而使用可调用对象绑定器`std::function`可以一次性包装这四种对象。对于类成员的非静态成员函数，可以通过`std::bind`绑定，它也可以被`std::function`包装。

# 4 标准库

C的数据结构往往要自己实现，例如链表，队列，哈希表等。例如通过存储`fd`的数组来实现哈希:

```cpp
struct ChannelMap {
    int size;
    struct Channel** list;
};
```

C++的STL中包含了这些数据类型，同时通过`RAII`自动内存管理。

C通过`POSIX`线程库`libpthread.so`来实现多线程，而C++11提供了`std::thread, std::mutex`等的封装。

C的事件驱动是有基于`POSIX`的`select, pool`，而在`linux`上通过` epoll`达到更高的性能。

# 5 C++新特性

C++新特性是为了更加安全`smart pointer, enum class, nullptr, namespace`，更高效`移动语义, emplace, thread, atomic`，更现代`auto, for-range, 结构化绑定, using, lambda, function`。

`namespace`可以隔离相同的变量名，函数名，类名。同时`namespace`也支持嵌套，配合`using`可以减少命名空间前缀的使用，同时可以起别名`namespace foo = origin;`。

`inline`可以建议编译器将内联函数展开，更重要的作用是可以将多个编译单元的实体合并。除了让包含头文件中的函数在多个编译单元出现，也使在静态成员变量在定义的时候就可以初始化。



