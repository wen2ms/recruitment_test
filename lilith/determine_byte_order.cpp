#include <iostream>

int main() {
    unsigned int num = 0x12345678;
    unsigned char* ptr = reinterpret_cast<unsigned char*>(&num);

    if (*ptr == 0x78) {
        std::cout << "Little End" << std::endl;
    } else if (*ptr == 0x12) {
        std::cout << "Big End" << std::endl;
    } else {
        std::cout << "Unkonwn" << std::endl;
    }

    return 0;
}