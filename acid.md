# ACID

`ACID`是数据库事务的四个特性，包括原子性`Atomicity`，一致性`Consistency`，隔离性`Isolation`和持久性`Durability`。

## 1. 原子性

原子性是指事务是原子操作，要么全部成功，要么全部失败。它是通过`WAL (Write-Ahead Log)`机制实现的。

一个写请求的流程是：1. 数据库服务器层接收到客户端的写请求。2. `SQL`层解析`SQL`并生成执行计划。3. 生成此次写操作的`Redo Log`和`Undo Log`，然后调用`write`将`Redo Log`从数据库的内存缓冲池写入到内核缓冲区中。4. 修改内存缓冲池中的数据页，产生脏页。下一步就是根据不同的情况，一种情况是客户端主动发出`ROLLBACK`或者事务中途失败，另一种是客户端直接`COMMIT`。

### 1.1 ROLLBACK

客户端发出`ROLLBACK`或者事务中断，数据库利用`Undo Log`将数据库缓冲池中的脏数据页恢复到修改前的状态，相关的`Undo Log`被标记为可回收，事务结束，相当于未发生操作。

### 1.2 COMMIT

事务提交时，先通过`fsync`将内核缓冲区中的`Redo Log`同步持久化到磁盘中，然后异步的调用`write/fsync`将内存中的脏页刷到磁盘中，事务的最后标记`Undo Log`为可回收。

先写`WAL`并持久化首先保证安全性，其次修改先内存页保证高性能，最终异步刷盘减少了`I/O`瓶颈。

## 2. 一致性

一致性是指事务执行前后，数据库中的数据都必须按照定义好的约束和规则保持一致状态。

例如在一个转账场景下，转账前A有500，B有300，然后A给B转了100，此时A和B都是400，事务执行前后A和B的总和都是800。

对于约束，例如对于一个消费者购买产品的场景，可以给消费者购买的产品`product_key`定义一个**外键约束**`CONSTRAINT foreign_key_product_key FOREIGN KEY (product_key) REFERENCES Product(product_key)`，那么就不能插入一条购买不存在的产品的消费记录。同样可以给产品的`product_key`加入一个**唯一约束**`UNIQUE`，规定每一个产品不能重复。还可以做一些**检查**`CHECK`，比如限制产品名的长度等。

一致性是由多个机制保证的。原子性保证数据不会出现只修改一半的情况，隔离性防止事务之间互现干扰，中间状态的数据被误读，持久性确保提交的数据不会丢失，不会出现不一致的状态，以及数据库的约束和检查。

## 3. 隔离性

隔离性是保证多个并发事务执行的时候，一个事务对其他事务是透明的，彼此隔离。

事务的隔离级别就是定义这种可见性等级，`Mysql`支持的四种隔离级别包括读未提交`READ UNCOMMITTED`，读已提交`READ COMMITTED`，可重复读`REPREATABLE READ`（默认）和可串行化`SERIALIZABLE`。他们的并发程度由高到低，安全性由低到高。

并发事务执行会出现下面几种现象：

1. 脏读

    一个事务可以读取到另一个事务尚未提交的数据。例如，事务B执行了一条更新操作`UPDATE account SET money = money + 100 WHERE name = 'Foo'`，没有提交，但是此时事务A读取到了这个更新后的数据`SELECT money FROM account`。

2. 不可重复读

    一个事务中多次读取的数据不一致。例如，事务A第一次读取`SELECT money FROM account`，然后事务B提交了一条更新操作的事务，此时事务A再次查询数据，发现两次数据不一样。

3. 幻读

    一个事务查询结果和插入操作不一致。例如，事务A第一次读取`SELECT money FROM account`，然后事务B提交了一条插入操作的事务，此时事务A再次查询数据发现和第一次读取结果一样，然后插入数据，这时候发现出现主键重复的错误。

| 隔离级别 | 脏读 | 不可重复读 | 幻读 |
| :-----: | :-----: | :-----: | :-----: |
| READ UNCOMMITTED | :white_check_mark: | :white_check_mark: | :white_check_mark: |
| READ COMMITTED | :x: | :white_check_mark: | :white_check_mark: |
| REPEATABLE READ | :x: | :x: | :white_check_mark: |
| SERIALIZABLE | :x: | :x: | :x: |

## 4. 持久性

持久性是指事务一旦提交对数据库的影响是永久的，断电和系统崩溃也不会丢失数据。

当数据库意外崩溃的时候，内存中未刷盘的数据可能丢失，需要利用`WAL`来恢复。当数据库启动时首先会扫描`WAL`，在`Redo`阶段`Redo Log`保证已提交的事务重新落盘，`Undo`阶段`Undo Log`会将未提交事务的被脏页污染了磁盘数据回滚，最终数据库恢复到一致状态。



