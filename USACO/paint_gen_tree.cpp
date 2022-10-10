#include <iostream>

int main() {
    std::cout << 100000 << ' ' << 2 << '\n';
    for (int i = 1; i <= 100000; i++) {
        std::cout << i << ' ' << i << ' ' << 200001 - i << ' ' << 200001 - i << '\n';
    }
}
