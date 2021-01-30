#include <bits/stdc++.h>

int main() {
    int n;
    scanf("%d", &n);
    long long ans = 0;
    std::priority_queue<int> slope_change;
    while (n--) {
        int a;
        scanf("%d", &a);
        slope_change.push(a); slope_change.push(a);
        ans += slope_change.top() - a;
        slope_change.pop();
    }
    printf("%lld", ans);
    return 0;
}
