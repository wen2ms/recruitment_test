## ✅ 一、SQL 语法导致的索引失效

### 1. **使用函数或表达式操作索引列**

```sql
-- ❌ 索引失效：对索引列加函数
SELECT * FROM users WHERE LEFT(name, 3) = 'Tom';

-- ✅ 正确写法
SELECT * FROM users WHERE name LIKE 'Tom%';
```

> ✅ 原因：B-Tree 是按原始值建立索引，变成表达式就无法利用。

---

### 2. **使用 `!=` 或 `<>`**

```sql
-- ❌ 索引失效：不等查询
SELECT * FROM users WHERE age != 30;
```

> ✅ 原因：无法快速定位范围，只能全表遍历。

---

### 3. **使用 `OR` 且字段未全部建索引**

```sql
-- ❌ age 没有索引，整个条件失效
SELECT * FROM users WHERE name = 'Tom' OR age = 20;

-- ✅ 正确写法（两个字段都加索引，或改成 UNION）
SELECT * FROM users WHERE name = 'Tom'
UNION
SELECT * FROM users WHERE age = 20;
```

---

### 4. **`LIKE` 以通配符开头（前模糊匹配）**

```sql
-- ❌ 索引失效
SELECT * FROM users WHERE name LIKE '%Tom';

-- ✅ 正确
SELECT * FROM users WHERE name LIKE 'Tom%';
```

> ✅ 原因：B-Tree 索引无法跳过前缀 `%`，所以无法使用。

---

### 5. **隐式类型转换**

```sql
-- ❌ 假设 id 是 INT 类型
SELECT * FROM users WHERE id = '123';  -- 字符串，会隐式转换

-- ✅ 正确写法
SELECT * FROM users WHERE id = 123;
```

> ✅ 原因：隐式类型转换会让索引失效，特别是字符串和数字混用。

---

## ✅ 二、联合索引使用不当（最左前缀原则）

### 6. **未从最左列开始使用**

```sql
-- 有索引 (name, age)

-- ❌ 索引失效：跳过 name
SELECT * FROM users WHERE age = 20;

-- ✅ 正确：从最左列开始用
SELECT * FROM users WHERE name = 'Tom' AND age = 20;
```

### 7. **中间列缺失**

```sql
-- 有索引 (name, age, gender)

-- ❌ 只用 name 和 gender，中间 age 被跳过，索引失效
SELECT * FROM users WHERE name = 'Tom' AND gender = 'M';
```

---

## ✅ 三、数据分布或优化器原因

### 8. **小表优化器选择全表扫描**

* 如果表很小（几十行），MySQL 认为全表扫描比走索引快，会自动放弃索引。

---

### 9. **索引选择失误（选择度差）**

* 如果某列重复值太多（如 `gender` 只有 'M' 和 'F'），走索引的效率比全表扫描还差，优化器就放弃用索引。

---

### 10. **统计信息不准确**

* 如果执行计划失误，有可能是表分析数据过时。

```sql
-- 更新统计信息
ANALYZE TABLE users;
```

---

## ✅ 四、其他场景

### 11. **使用 `IS NULL` / `IS NOT NULL`**

* `IS NULL` 通常可以使用索引
* `IS NOT NULL` 有可能不走索引，视版本和优化器行为

---

### 12. **使用 `ORDER BY` 导致回表或排序失效**

```sql
-- 有索引 (name, age)

-- ✅ 可用索引
SELECT * FROM users WHERE name = 'Tom' ORDER BY age;

-- ❌ 如果 select 的字段不包含索引字段，就可能回表排序
SELECT id FROM users WHERE name = 'Tom' ORDER BY age;
```

---

## ✅ 建议：如何判断是否索引失效？

```sql
EXPLAIN SELECT * FROM users WHERE ...
```

* 查看 `type` 和 `key` 字段：

  * `type=ALL` 表示全表扫描
  * `key=NULL` 表示未使用索引

---

## ✅ 总结图表

| 场景                   | 是否失效 | 原因简述         |
| -------------------- | ---- | ------------ |
| 索引列上使用函数或表达式         | ✅    | 无法使用原始索引结构   |
| `!=` 或 `<>` 查询       | ✅    | 无法快速跳过值      |
| `LIKE '%abc'` 前缀模糊匹配 | ✅    | 无法定位开头位置     |
| 联合索引未遵守最左前缀          | ✅    | 索引是从最左列开始匹配的 |
| 使用 `OR` 混合有无索引字段     | ✅    | 优化器放弃使用索引    |
| 字段类型不匹配导致隐式转换        | ✅    | 触发转换，索引无法使用  |
| 表太小优化器认为不值得用索引       | ✅    | 优化器策略        |
| 字段选择度差（如性别字段）        | ✅    | 扫描行太多，反而慢    |

---