## ✅ `auto` 能推导出哪些类型？

编译器可以从以下表达式中**推导出绝大多数合法类型**，包括但不限于：

### 1. **基本类型**（int、double、char、bool 等）

```cpp
auto a = 10;        // int
auto b = 3.14;      // double
auto c = 'x';       // char
auto d = true;      // bool
```

---

### 2. **指针类型**

```cpp
int x = 5;
auto p = &x;        // int*
```

---

### 3. **引用类型**

> ⚠️ `auto` **默认不保留引用类型**，需要用 `auto&` 或 `const auto&` 显式声明。

```cpp
int x = 10;
auto y = x;         // int（值拷贝）
auto& r = x;        // int&（引用）
const auto& cr = x; // const int&（常量引用）
```

---

### 4. **数组推导为指针**

```cpp
int arr[5] = {1, 2, 3, 4, 5};
auto p = arr;       // int*（数组退化为指针）
```

---

### 5. **容器类型（如 STL 容器）**

```cpp
std::vector<int> v = {1, 2, 3};
auto it = v.begin();        // std::vector<int>::iterator
```

---

### 6. **函数返回值**

```cpp
std::string get_name() { return "Tom"; }
auto name = get_name();     // std::string
```

---

### 7. **Lambda 表达式**

```cpp
auto func = [](int a, int b) { return a + b; }; // 匿名函数对象类型
```

---

### 8. **结构体/类类型**

```cpp
struct Point { int x, y; };
Point p = {1, 2};
auto q = p;   // Point（值拷贝）
```

---

### 9. **`decltype(auto)`（更精准的类型推导）**

* `auto`：丢失引用/const 修饰
* `decltype(auto)`：保留完整的类型信息

```cpp
int x = 5;
int& rx = x;

auto a = rx;            // int（拷贝）
decltype(auto) b = rx;  // int&（保留引用）
```

---

## ✅ 小结：`auto` 能推导哪些类型？

| 表达式类型           | `auto` 推导结果       |
| --------------- | ----------------- |
| 基本类型常量          | int、double、bool 等 |
| 引用类型变量          | 拷贝其值（非引用）         |
| 使用 `auto&`      | 保留引用类型            |
| 指针、数组           | 推导为指针             |
| STL 容器迭代器       | 迭代器类型             |
| 函数返回值           | 返回值类型             |
| Lambda 表达式      | 匿名闭包类型（不可打印）      |
| struct/class 对象 | 类型为该类的值           |

---

## ⚠️ 注意事项

1. `auto` **必须有初始值**，不能只声明不初始化：

   ```cpp
   auto x;  // ❌ 错误，编译器不知道类型
   ```

2. `auto` **不能用作函数参数的类型（非 C++20）**：

   ```cpp
   void f(auto x); // ❌ 非法（除非你用 C++20 的概念）  
   ```

3. 对模板 & STL 配合非常方便，简化代码：

   ```cpp
   for (auto it = v.begin(); it != v.end(); ++it) { ... }
   ```

---