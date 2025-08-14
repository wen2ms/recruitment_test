# emplace

`emplace, emplace_back`相对与`push, insert, push_back`最大的区别就是`emplace`直接在容器内部原地构造对象，而`push_back`是通过拷贝或者移动到容器中。

例如向`std::unordered_map`中插入一个对组，可以不需要构造一个临时变量`std::make_pair(1, "judy")`。

```cpp
    std::unordered_map<int, std::string> hash;
    hash.emplace(1, "judy");
```

但是传参可能导致可读性下降。

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

