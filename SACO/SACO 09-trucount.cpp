#include <iostream>
#include <algorithm>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for(int i = x; i < y; i++)
typedef long long ll;

int a[100001];

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    std::cin >> n;
    FOR(i, 1, n + 1) std::cin >> a[i];
    std::sort(a + 1, a + n + 1);
    a[n + 1] = n + 1;
    FOR(i, a[1], n + 1) {
        while (a[i + 1] == a[i]) i++;
        if (i >= a[i] && a[i + 1] > i) return std::cout << i << '\n', 0;
    }
    return 0;
}