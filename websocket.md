相对于`HTPP`半双工的请求响应式协议，`WebSocket`是一个全双工协议，建立一次`TCP`连接后双方就可以互相发送数据。

### 1. 建立连接

`WebSocket`规定，首先客户端会向服务端发送一个`HTTP`请求，要求将协议升级到`WebSocket`，这个请求中还包括客户端生成的随机值`Sec-WebSocket-Key`，服务器收到收到后返回`101 Switching Protocols`和`Sec-WebSocket-Accept`，这个值是根据客户端发来的`Sec-WebSocket-Key`然后通过`SHA-1`加密，`Base64`编码生成的，客户端收到后然后验证是否和`Sec-WebSocket-Key`一致。然后`HTTP`升级为`WebSocket`，`TCP`连接持续保持，双方可以互相发送消息。

### 2. 报文格式

`WebSocket`的一条消息是由多个帧组成的，每个帧主要包含：

`FIN`表示是否为消息的最后一帧。

`Opcode`表示数据的类型，比如文本，二进制帧，`ping/pong`帧等，其中文本必须使用`UTF-8`编码。

`MASK`表示是否对`payload`进行掩码，客户端必须要为`1`，服务端一般为`0`。

`Payload len`表示`Payload data` 的长度。

`Masking key`，它和`MASK`对应，客户端必须有，将`Masking key`与`Payload data`异或，是为了防止原始消息中的一些二进制内容被中间设备当作`HTTP`流数据，从而根据某些针对`HTTP`的规则截断原本的二进制数据。

`Payload data`就是实际消息内容掩码后的数据，最后服务端再异或一次就可以得到原始数据。

### 3. 断开连接

`WebSocket`规定在连接断开的时候，客户端会发送一个`Close`帧，携带了状态码，例如`1000 Normal Closure`正常断开，`1001 Going Away`对端离开，`1006 Abnormal Closure`没有收到`Close`帧然后异常关闭。然后在服务端收到后，也返回自己`Close`帧作为应答，此时`WebSocket`层就断开连接了，随后`TCP`四次挥手也断开连接。

### 4. MQTT

`WebSocket`为了保持长连接，使用`ping/pong`维持心跳，需要占用更多的系统资源，而且它是1对1的。而`MQTT`协议的报文更加轻量，同时它是基于订阅者模式的，`broker`会自动进行消息转发，最重要的是`WebSocket`在网络不稳定的情况下，如果断开连接，需要程序维护订阅表，并且存储断开连接期间的消息，而`broker`会记住订阅关系，从而自动完成重接。