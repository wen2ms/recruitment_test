#include <iostream>
#include <cmath>

int main() {
    double epsilon = 1e-6;

    double low = 0, high = 2;
    while (high - low > epsilon) {
        double mid = (low + high) / 2;
        if (mid * mid < 2) {
            low = mid;
        } else {
            high = mid;
        }
    }

    double result = (high + low) / 2;
    
    std::cout << "sqrt(2) = " << result << std::endl;
    std::cout << "epsilon = " << abs(result - sqrt(2)) << std::endl; 

    return 0;
} 