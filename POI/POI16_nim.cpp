#include <iostream>

int main() {
    int n;
    std::cin >> n;
    long long c = 1;
    for (int i = 0; i < n; i++) {
        int a;
        std::cin >> a;
        while (a) a >>= 1, c += 2;
    }
    std::cout << c;
}