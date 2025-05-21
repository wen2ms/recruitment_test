MySQL 的事务隔离级别（Transaction Isolation Levels）定义了多个事务并发执行时彼此之间的可见性，以避免并发带来的数据问题（如脏读、不可重复读、幻读等）。MySQL 支持以下四种标准的事务隔离级别：

---

### 1. **READ UNCOMMITTED（读未提交）**

* **特点**：

  * 一个事务可以读取另一个事务**尚未提交**的数据。
* **可能的问题**：脏读（Dirty Read）
* **并发性**：最高
* **数据一致性**：最低

---

### 2. **READ COMMITTED（读已提交）**

* **特点**：

  * 只能读取已经提交的事务的数据。
* **可能的问题**：不可重复读（Non-repeatable Read）
* **防止**：脏读
* **允许**：不可重复读、幻读

---

### 3. **REPEATABLE READ（可重复读）**（MySQL **默认**隔离级别）

* **特点**：

  * 在一个事务中多次读取同一数据结果一致。
* **防止**：脏读、不可重复读
* **可能的问题**：幻读（Phantom Read）
* **MySQL InnoDB 实现**：通过 **间隙锁（Next-Key Locking）** 避免幻读

---

### 4. **SERIALIZABLE（可串行化）**

* **特点**：

  * 强制事务串行执行，锁住读过的行。
* **防止**：脏读、不可重复读、幻读
* **并发性**：最低，代价最高

---

## 设置/查看隔离级别

### 查看当前隔离级别：

```sql
SELECT @@transaction_isolation;  -- 在 MySQL 8.0 及以后推荐
```

### 设置当前会话的隔离级别：

```sql
SET SESSION TRANSACTION ISOLATION LEVEL READ COMMITTED;
```

### 设置全局隔离级别（重启失效）：

```sql
SET GLOBAL TRANSACTION ISOLATION LEVEL REPEATABLE READ;
```

---

## 总结对比表：

| 隔离级别             | 脏读 | 不可重复读 | 幻读 |
| ---------------- | -- | ----- | -- |
| READ UNCOMMITTED | ✅  | ✅     | ✅  |
| READ COMMITTED   | ❌  | ✅     | ✅  |
| REPEATABLE READ  | ❌  | ❌     | ✅  |
| SERIALIZABLE     | ❌  | ❌     | ❌  |

---

