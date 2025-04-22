## 🌐 一、HTTP vs HTTPS 的核心区别

| 对比点 | HTTP | HTTPS |
|--------|------|--------|
| 安全性 | ❌ 明文传输，容易被窃听/篡改 | ✅ 加密传输，数据私密性强 |
| 使用端口 | 80 | 443 |
| 加密机制 | 无 | 使用 TLS（或原来的 SSL）加密 |
| 证书支持 | 无 | 需要服务器有 SSL/TLS 证书（如 HTTPS 证书） |
| 数据完整性 | 无验证 | 可验证数据未被篡改 |
| 性能 | 稍快（无加密） | 稍慢（多一次握手）但现在几乎无感知差异 |

---

## 🤝 二、握手环节的区别

### ✅ 1. HTTP 握手：

HTTP 是 **基于 TCP 的** 协议，它的通信流程大致是这样的：

```
Client --TCP 3次握手--> Server
Client --发送 HTTP 请求--> Server
Server --返回 HTTP 响应--> Client
```

👉 只要 TCP 连接建立好，HTTP 请求就直接发出，没有任何加密，也没有额外的握手过程。

---

### ✅ 2. HTTPS 握手：

HTTPS = HTTP + TLS

在进行 HTTP 请求之前，必须 **先完成一轮 TLS 握手**，过程如下（简化版）：

```
Client --TCP 3次握手--> Server
Client --发送 ClientHello（包含随机数、支持的加密算法）-->
Server --发送 ServerHello（随机数、数字证书、公钥）-->
Client --验证证书、生成 pre-master key、用公钥加密发给服务器-->
Server --用私钥解密 pre-master key-->
Client & Server --计算出 Session Key-->
双方发送 Finished（表示握手结束）-->

✅ TLS 握手完成！
➡️ 然后才能走正常的 HTTP 请求过程（此时是加密的）
```

---

## 🔐 握手差异小结：

| 步骤 | HTTP | HTTPS（含 TLS） |
|------|------|----------------|
| 是否加密 | ❌ 无 | ✅ 有 |
| 需要证书吗 | ❌ 不需要 | ✅ 需要服务端证书（数字签名） |
| 握手过程 | 只有 TCP 三次握手 | TCP + TLS 握手（含证书、公钥加密） |
| 成功后 | 直接发送明文 HTTP 请求 | 在加密通道中发送 HTTP 请求 |

---