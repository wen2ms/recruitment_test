## ✅ 一、创建索引的方法

### 1. 在创建表时添加索引

```sql
CREATE TABLE users (
    id INT PRIMARY KEY,
    name VARCHAR(100),
    email VARCHAR(100),
    INDEX idx_name (name),
    UNIQUE KEY idx_email (email)
);
```

### 2. 使用 `ALTER TABLE` 给已有表添加索引

```sql
-- 添加普通索引
ALTER TABLE users ADD INDEX idx_name (name);

-- 添加唯一索引
ALTER TABLE users ADD UNIQUE INDEX idx_email (email);

-- 添加多列复合索引
ALTER TABLE users ADD INDEX idx_name_email (name, email);
```

### 3. 使用 `CREATE INDEX`

```sql
CREATE INDEX idx_name ON users(name);

-- 多列索引
CREATE INDEX idx_name_email ON users(name, email);
```

---

## ✅ 二、索引类型解释

| 索引类型 | 关键字             | 说明                                                  |
| ---- | --------------- | --------------------------------------------------- |
| 普通索引 | `INDEX` / `KEY` | 提高查询效率                                              |
| 唯一索引 | `UNIQUE`        | 保证字段唯一                                              |
| 主键索引 | `PRIMARY KEY`   | 自动唯一+非空，通常用于主键                                      |
| 复合索引 | `INDEX(a, b)`   | 多列索引，注意顺序重要（最左前缀原则）                                 |
| 全文索引 | `FULLTEXT`      | 适用于 `CHAR`、`VARCHAR`、`TEXT`，用于全文搜索（MyISAM / InnoDB） |
| 空间索引 | `SPATIAL`       | 用于GIS空间数据（如 POINT、POLYGON）                          |

---

## ✅ 三、建索引的建议

1. **频繁作为查询条件（WHERE、JOIN、ORDER BY）的字段**应建立索引。
2. **避免在频繁更新的字段上建索引**，因为更新时也会维护索引。
3. **组合索引要符合最左前缀原则**，例如 `(a, b)` 的索引可以用于 `WHERE a = ...` 或 `WHERE a = ... AND b = ...`，但不能用于 `WHERE b = ...`。
4. **避免对低选择性的字段建索引**（如性别，只有“男/女”），因为优化作用不明显。

---

## ✅ 四、查看和删除索引

### 查看表索引：

```sql
SHOW INDEX FROM users;
```

### 删除索引：

```sql
-- 如果是通过 ALTER TABLE 添加的：
ALTER TABLE users DROP INDEX idx_name;

-- 删除主键（如果是主键索引）：
ALTER TABLE users DROP PRIMARY KEY;
```