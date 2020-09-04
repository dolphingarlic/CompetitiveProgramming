#include <iostream>

int main() {
    int n, m, sd = 0, ml = 0, mc = 0;
    std::cin >> n >> m;
    while (n--) {
        char c;
        std::cin >> c;
        switch (c) {
            case '(':
                sd++;
                break;
            case ')':
                if (sd) sd--;
                else if (ml > 1) ml--;
                else return std::cout << 0, 0;
                break;
            default:
                if (!mc) {
                    if (sd) mc = 1, ml = sd, sd = 0;
                    else return std::cout << 0, 0;
                } else if (ml > 1 || sd) mc++, ml = ml - 1 + sd, sd = 0;
                else return std::cout << 0, 0;
        }
    }
    for (int i = 0; i < m; i++) std::cout << "1\n";
    std::cout << ml;
    return 0;
}
