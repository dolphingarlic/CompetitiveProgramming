#include <iostream>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int n, p[200001];
    std::cin >> n;
    for (int i = 0; i < n; i++) std::cin >> p[i];
    for (int x = 0; x <= n; x++) {
        int mn = 0, mx = n + 1, ans = 0;
        bool hi = false;
        for (int i = 0; i < n; i++) {
            if (p[i] > mx || p[i] < mn) continue;
            if (p[i] > x) {
                hi = true;
                mx = p[i];
            } else {
                ans += hi;
                hi = false;
                mn = p[i];
            }
        }
        std::cout << ans << '\n';
    }
    return 0;
}
