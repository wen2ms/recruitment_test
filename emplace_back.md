### ✅ **`emplace_back` 和 `push_back` 有什么区别**

两者作用类似，都是向容器尾部插入元素，常用于 `std::vector`、`std::deque`、`std::list` 等。

| 函数             | 作用                             |
| -------------- | ------------------------------ |
| `push_back`    | **将一个已经构造好的对象** 拷贝或移动到容器末尾。    |
| `emplace_back` | **在容器内部原地直接构造对象**，避免不必要的拷贝或移动。 |

---

### ✅ **区别举例**

假设有如下类：

```cpp
struct Person {
    std::string name;
    int age;

    Person(std::string n, int a) : name(std::move(n)), age(a) {
        std::cout << "Constructed\n";
    }
};
```

#### `push_back` 示例：

```cpp
std::vector<Person> vec;
Person p("Tom", 30);
vec.push_back(p);         // 拷贝 p
vec.push_back(std::move(p));  // 移动 p
```

这里，`Person` 对象 `p` 先在外部构造好，再拷贝或移动到容器里。

---

#### `emplace_back` 示例：

```cpp
std::vector<Person> vec;
vec.emplace_back("Tom", 30);  // 直接在容器内构造，避免额外拷贝/移动
```

可以看到，`emplace_back` 直接传递构造函数参数，**对象直接在容器内部构造**。

---

### ✅ **为什么 `emplace_back` 有时候不好用？**

1. **代码可读性下降**

   `emplace_back` 直接传构造参数，如果参数多或者逻辑复杂，别人看代码时不容易立刻看出插入的是什么类型。

2. **容易意外构造临时对象**

   如果传入的参数不小心写错，可能构造了不期望的对象。

3. **与模板推导配合不好时可能出错**

   某些模板场景下，`emplace_back` 参数推导容易出问题，或者调用了错误的构造函数，导致编译失败。

4. **`emplace_back` 不一定总是更高效**

   对于简单类型（如 `int`、`double`），`emplace_back` 和 `push_back` 效率基本一样，甚至编译器最终生成的代码可能没有区别。

---

### ✅ **总结建议**

| 场景          | 推荐                      |
| ----------- | ----------------------- |
| 插入临时对象，直接构造 | 用 `emplace_back`        |
| 插入已有对象      | 用 `push_back`           |
| 参数多、容易混淆时   | 慎用 `emplace_back`，确保可读性 |
| 容器内类型很简单    | 两者随意，差别不大               |

---

### ✅ **Clang-Tidy 为什么建议 `emplace_back`**

Clang-Tidy 的 `modernize-use-emplace` 规则是为了鼓励更现代、更高效的 C++ 写法。但这不是强制的，有时你可以根据实际场景选择忽略这个建议。

---