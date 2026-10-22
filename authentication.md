## 1. OAuth2协议

OAuth2用来在不同应用中的授权，可以不通过密码，直接通过token来进行授权。

经典的授权方式包括：

| 授权模式   | 是否需要用户交互 |
| :--------:  | :----------------: |
| Authorization Code | 首次需要         |
| Client Credentials | 服务端到服务端的应用级授权，但是一般是应用级token         |
| Refresh Token | 用之前获得的刷新令牌换取新的 Access Token，解决续期问题 |
| Token Exchange | 将一种安全令牌交换为另一种符合目标系统要求的令牌 |

## 2. UUID

通用唯一标识符（Universally Unique Identifier，UUID）是一个128位的标识符，通常为32个16进制字符，每个16进制字符代表4位，共128位。

```python
id = uuid.uuid4().hex
```