HTTP 报文是 **客户端和服务器之间通信时交换的数据单位**。它分为两类：

* **请求报文（Request）**：客户端 → 服务器
* **响应报文（Response）**：服务器 → 客户端

---

## 一、HTTP 请求报文结构

```
<请求行>
<请求头部>
<空行>
<请求体>
```

### 示例：

```
GET /index.html HTTP/1.1
Host: www.example.com
User-Agent: Mozilla/5.0
Accept: text/html

(请求体为空)
```

### 各部分说明：

1. **请求行**

   * 格式：`<方法> <URL路径> <协议版本>`
   * 如：`GET /index.html HTTP/1.1`

2. **请求头（Header）**

   * 提供客户端信息、期望内容类型等
   * 常见字段：

     * `Host`: 目标主机
     * `User-Agent`: 客户端信息
     * `Accept`: 接受的内容类型
     * `Content-Type`: 发送数据格式（POST/PUT）

3. **空行**

   * 分隔头部和正文（请求体）

4. **请求体**

   * 可选。用于 POST、PUT 方法，包含表单数据、JSON、文件等。

---

## 二、HTTP 响应报文结构

```
<状态行>
<响应头部>
<空行>
<响应体>
```

### 示例：

```
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 137

<html>
  <body>Hello, world!</body>
</html>
```

### 各部分说明：

1. **状态行**

   * 格式：`<协议版本> <状态码> <状态描述>`
   * 如：`HTTP/1.1 200 OK`

2. **响应头（Header）**

   * 提供服务器信息、返回内容类型等
   * 常见字段：

     * `Content-Type`: 返回内容类型
     * `Content-Length`: 响应体长度
     * `Set-Cookie`: 设置 cookie

3. **空行**

   * 分隔头部和正文

4. **响应体**

   * 实际返回的数据，如 HTML、JSON、图像等。

---

## 三、常见状态码

* **200 OK**：请求成功
* **301 Moved Permanently**：永久重定向
* **302 Found**：临时重定向
* **400 Bad Request**：客户端请求错误
* **401 Unauthorized**：未授权
* **403 Forbidden**：禁止访问
* **404 Not Found**：找不到资源
* **500 Internal Server Error**：服务器内部错误

---
