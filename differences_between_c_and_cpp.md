# C和C++

## 1 发展历史

从发展历史来看C++是在C的基础上发展来的。

## 2 程序设计思想

C是面向过程`Procedural Programming`，通过函数来组织程序，同时引入了结构体，联合体来实现`OOP (Oriented-Object Programging)`，但是结构体中不能包含函数，而C++设计之初就是面向对象，包含类，继承，多态这样的`OOP`特性，同时也利用`template`和 `std::forward`实现良好的泛型编程。

## 3 语言特性

C更接近底层，内存管理主要通过`malloc, calloc, realloc`和`free`。

### 3.1 RAII

现代C++通过`RAII (Resource Acquisition Is Initialization)`，资源获得即初始化，结合构造和析构的思想对资源进行安全的管理，例如通过`std::unique_ptr`对堆内存管理，`std::lock_guard`可以对`mutex`进行管理。

### 3.2 **多态**

C++的多态分为两种：

#### 3.2.1 编译时多态。

不影响运行速度，包括函数重载和模版。对于函数重载，编译器会将函数名+参数类型编码成一个内部符号名，编译时根据实参类型选择合适的函数。而模版会在编译时编译器根据实参类型生成对应的类或者函数，也就是模版实例化的过程，不同参数是互相独立的，结果就像编译器按照模版参数自动生成了多个重载函数。

#### 3.2.2 运行时多态。

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

#### 3.3.3 RTTI

`RTTI (Run-Time Type Information)`运行时类型信息。例如

```cpp
Base* base = new Derived;
Derived* derived = std::dynamic_cast<Derived*>(base);
```

如果`base`不是指向子类的话，`dynamic_cast`就会抛出`std::bad_cast`（引用）或`nullptr`（指针）。

`RTTI`依赖于`vtable`，虚函数表中一般除了存储函数指针还存储了对象所属类信息`type_info`。



## 4 标准库

C的数据结构往往要自己实现，例如链表，队列，哈希表等。C++的STL中包含了这些数据类型，同时通过`RAII`自动内存管理。

C通过`POSIX`线程库`libpthread.so`来实现多线程，而C++11提供了`std::thread, std::mutex`等的封装。

C的事件驱动是有基于`POSIX`的`select, pool`，而在`linux`上通过` epoll`达到更高的性能。