## ✅ 一、索引优化基本原则

1. **尽量使用**：`WHERE`、`JOIN`、`ORDER BY`、`GROUP BY` 中的列创建索引。
2. **避免在索引列上进行计算**：如 `WHERE YEAR(date_col) = 2023` 不走索引。
3. **使用覆盖索引**（Covering Index）：即 `SELECT` 的字段全在索引里，避免回表。
4. **避免模糊查询前缀**：`LIKE '%abc'` 无法使用索引，`LIKE 'abc%'` 可以。

---

## ✅ 二、联合索引列顺序：怎么排序？

假设你有一个联合索引 `(a, b, c)`，那排序规则通常如下：

### 🧠 原则：**最常用的、区分度高的放前面**

1. **WHERE 使用频率高的字段优先**
2. **区分度高的列优先**（区分度 = 唯一值/总记录）
3. **等值查询字段优先于范围查询字段**
4. **ORDER BY 也参考顺序，但不能违背 WHERE 优化**

### 举例分析：

```sql
CREATE INDEX idx_user ON user(age, gender, status);
```

* 查询1：

  ```sql
  SELECT * FROM user WHERE age = 30 AND gender = 'M' AND status = 1;
  ```

  ✅ 会完全命中索引（age → gender → status）

* 查询2：

  ```sql
  SELECT * FROM user WHERE gender = 'M' AND status = 1;
  ```

  ❌ 不会命中索引前缀（age 不在条件里），可能不走索引。

* 查询3：

  ```sql
  SELECT * FROM user WHERE age = 30 AND status = 1;
  ```

  ✅ 可能使用索引部分（age），跳过 gender

所以联合索引的原则是：**最左前缀原则（Left Most Prefix）**

---

## ✅ 三、`SELECT b FROM t WHERE a = 1 AND b = 2` 会不会走索引 `(a, b, c)`？

### 答：✅ **会走索引**

联合索引 `(a, b, c)` 能用于以下场景：

| 查询字段                              | 是否走索引 | 说明           |
| --------------------------------- | ----- | ------------ |
| `WHERE a = 1`                     | ✅     | 命中前缀 `a`     |
| `WHERE a = 1 AND b = 2`           | ✅     | 命中前缀 `a,b`   |
| `WHERE a = 1 AND b = 2 AND c = 3` | ✅     | 命中前缀 `a,b,c` |
| `WHERE b = 2`                     | ❌     | 不符合最左前缀      |

> `SELECT b` 只选择了 `b` 字段，不影响是否走索引，**只影响是否为覆盖索引**。
> 如果查询的字段都在索引里（比如 `(a, b, c)`），就会变成 **覆盖索引**，不需要回表，速度更快。

---

## 🔍 四、怎么确认“有没有走索引”？

使用 `EXPLAIN` 或 `EXPLAIN ANALYZE`：

```sql
EXPLAIN SELECT b FROM t WHERE a = 1 AND b = 2;
```

输出中：

* `key`: 使用的索引名
* `rows`: 扫描的行数，越少越好
* `Extra` 包含 `Using index` 表示使用了覆盖索引

---

## ✅ 总结

| 问题                 | 解答                               |
| ------------------ | -------------------------------- |
| 联合索引列顺序怎么排序？       | 高频使用、区分度高、等值优先，最左前缀原则            |
| `SELECT b` 会不会走索引？ | 会，如果 `WHERE` 命中联合索引前缀            |
| 怎么判断有没有走索引？        | 用 `EXPLAIN` 看 `key` 和 `Extra` 字段 |