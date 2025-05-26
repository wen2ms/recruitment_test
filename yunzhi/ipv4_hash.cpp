#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

uint32_t ip_to_uint32(const std::string& ip) {
    std::istringstream stream(ip);
    std::string segment;
    uint32_t result = 0;

    for (int i = 0; i < 4; ++i) {
        std::getline(stream, segment, '.');

        int part = std::stoi(segment);

        result = (result << 8 | static_cast<uint32_t>(part));
    }

    return result;
}

int main() {
    std::string ip = "192.168.0.1";

    uint32_t ip_num = ip_to_uint32(ip);

    std::cout << ip_num << std::endl;

    return 0;
}
