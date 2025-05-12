## 🧱 vector 的内部结构与空间配置器的作用

在 GCC 的实现中，`std::vector` 继承自 `_Vector_base`，后者负责管理内存分配。

### `_Vector_base` 的关键成员：

* `_M_impl._M_start`：指向已分配内存的起始位置。
* `_M_impl._M_finish`：指向当前已使用元素的末尾。
* `_M_impl._M_end_of_storage`：指向已分配内存的末尾。

这些指针由空间配置器 `std::allocator<T>` 管理，后者封装了内存的分配与释放操作。

---

## ⚙️ vector 如何使用 allocator 分配空间

当您执行 `vec.push_back(x)` 时，vector 会检查是否有足够的空间：

* **有足够空间**：直接在 `_M_finish` 位置构造新元素，并将 `_M_finish` 向后移动。
* **空间不足**：调用 `_M_realloc_insert` 进行扩容。

### 扩容过程 `_M_realloc_insert`：

1. 计算新的容量（通常是当前容量的 1.5 倍或 2 倍）。
2. 使用 allocator 的 `allocate()` 方法分配新的内存空间。
3. 将旧元素移动或拷贝到新内存中。
4. 在新位置构造新元素。
5. 销毁旧元素并释放旧内存。
6. 更新 `_M_start`、`_M_finish` 和 `_M_end_of_storage` 指针。

---

## 🛠️ allocator 的关键函数

空间配置器 `std::allocator` 提供以下核心函数：

* **`allocate(n)`**：分配 `n` 个元素的原始内存。
* **`construct(p, args...)`**：在指针 `p` 指向的内存位置构造对象。
* **`destroy(p)`**：调用指针 `p` 指向对象的析构函数。
* **`deallocate(p, n)`**：释放之前分配的内存。

这些函数使得 `std::vector` 能够精细地控制内存的分配与释放，提高性能并减少不必要的开销。

---

## 📌 总结

* `std::vector` 使用空间配置器 `std::allocator` 管理内存。
* 内存分配与释放通过 `allocate` 和 `deallocate` 完成。
* 对象的构造与销毁通过 `construct` 和 `destroy` 实现。
* 扩容时，vector 会重新分配更大的内存，并迁移旧元素。

这种设计使得 `std::vector` 在提供动态数组功能的同时，具有高效的内存管理能力。