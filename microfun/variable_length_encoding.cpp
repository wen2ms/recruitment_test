#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

// 编码规则总结：
// 每个字节占 8 位
// 最高位（MSB）是标志位：
// 如果是 1，表示后面还有字节。
// 如果是 0，表示当前是最后一个字节。
// 后7位用于存储数据，即每个字节最多提供 7 位的有效数据。
// 多个字节拼接起来就是一个整数，低位在前，高位在后（小端顺序）。
// 示例分析
// 示例1：输入是 100 → 输出是 0x64
// 100 的二进制：0110 0100
// 只需一个字节存储，因为它小于 128。
// 因此构造：
// 最高位 = 0（这是最后一个字节）
// 后7位 = 1100100
// 拼起来 = 0 1100100 = 01100100 = 0x64
// 示例2：输入是 0xE7 0x07 → 输出是 999
// 拆解过程：
// 0xE7 = 1110 0111
// 最高位是 1，说明后面还有一个字节。
// 后7位是 1100111 = 0x67
// 0x07 = 0000 0111
// 最高位是 0，这是最后一个字节。
// 后7位是 0000111 = 0x07

std::vector<uint8_t> parse_string(const std::string& str) {
    std::vector<uint8_t> result;

    for (int i = 0; i < str.size(); i += 4) {
        std::string byte_str = str.substr(i + 2, 2);

        uint8_t byte = static_cast<uint8_t>(std::stoul(byte_str, nullptr, 16));

        result.push_back(byte);
    }

    return result;
}

std::vector<uint8_t> encode(uint64_t value) {
    std::vector<uint8_t> bytes;

    do {
        uint8_t byte = value & 0x7F;

        value >>= 7;

        if (value != 0) {
            byte |= 0x80;
        }

        bytes.push_back(byte);
    } while (value != 0);

    return bytes;
}

uint64_t decode(const std::vector<uint8_t>& bytes) {
    uint64_t result = 0;

    int i = 0;
    for (uint8_t byte : bytes) {
        result |= static_cast<uint64_t>(byte & 0x7F) << i;

        if ((byte & 0x80) == 0) {
            break;
        }

        i += 7;
    }

    return result;
}

int main() {
    uint64_t n;
    std::string s;

    std::cin >> n >> s;

    std::vector<uint8_t> encoded = encode(n);

    for (uint8_t byte : encoded) {
        std::cout << "0X" << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    std::cout << std::endl;

    std::vector<uint8_t> bytes = parse_string(s);
    uint64_t decoded = decode(bytes);

    std::cout << std::dec << decoded << std::endl;

    return 0;
}