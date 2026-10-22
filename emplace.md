# 1. emplace

`emplace, emplace_back`相对与`push, insert, push_back`最大的区别就是`emplace`直接在容器内部原地构造对象，而`push_back`是通过拷贝或者移动到容器中。

例如向`std::unordered_map`中插入一个对组，可以不需要构造一个临时变量`std::make_pair(1, "judy")`。

```cpp
std::unordered_map<int, std::string> hash;
hash.emplace(1, "judy");
```

但是传参可能导致可读性下降，同时`empalce`并不总是更加有效率，对于小对象`emplace`中的完美转发中的类型推导可能更加复杂。

## 底层的区别

`push_back`是调用拷贝构造或移动构造。

```cpp
void push_back(const T& value) {
    if (size_ == capacity_)
        grow();
    // placement new
    new (data_ + size_) T(value);
    ++size_;
}
```

`empalce_back`是原地构造。

```cpp
template<class... Args>
void emplace_back(Args&&... args) {
    if (size_ == capacity_)
        grow();
    new (data_ + size_) T(std::forward<Args>(args)...);
    ++size_;
}
```

# 2. vector

`std::vector<T>`本质就是一个动态数组，在运行期在堆上分配的连续内存。内部维护了三个成员`T* _start, T* _finish, T* _end_of_storage`，通过这三个元素可以计算当前的`size = _finish - _start`，当前的`capacity = _end_of_storage - _start`。在插入新元素时，如果`size < capacity`直接在`_finish`构造新元素，同时`++_finish`，否则就进行`reallocate`，分配一个原容量2倍的空间，然后移动到新内存，最后更新内部三个成员，然后插入新元素。

元素的构造和销毁都是通过空间配置器`std::allocator<T>`完成的，容器不直接调用`new/delete`，并且多个容器可以服用一个接口。

注意`std::vector<bool>`为了节省空间，将8个`bool`放在一个字节里，它是使用位运算来操作的，效率反而低。

# 3. array

`std::array<T, size>`是在栈上分配的连续内存，与原生数组一样，在编译器就固定了数组长度。

`std::array`本质上是一个聚合类型`aggregate`，而`std::vector`是一个类。聚合类型不能有自定义的构造函数，不能有私有成员，不能有虚函数，不能是子类，因此`std::array`不会默认初始化。

```cpp
template <class Tp, size_t Size>
struct array {
    Tp elements[Size];
};
```

