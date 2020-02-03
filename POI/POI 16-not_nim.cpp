#include <iostream>
#include <queue>

int l2(int a) { return (a ? 1 + l2(a >> 1) : -1); }

int leading(int a) {
    int ans = 0;
    for (int i = 29; ~i; i--) {
        if (a & (1 << i))
            ans++;
        else if (ans)
            return ans;
    }
    return ans;
}

int main() {
    int n;
    std::cin >> n;
    long long c = 4 * n - 1;
    std::priority_queue<int> leadingset;
    for (int i = 0; i < n; i++) {
        int a;
        std::cin >> a;
        c += 2 * l2(a);
        leadingset.push(leading(a));
    }

    leadingset.pop();
    while (leadingset.size()) {
        int curr = leadingset.top();
        leadingset.pop();
        if (curr == 1)
            c -= 2;
        else {
            leadingset.push(curr - 1);
            leadingset.pop();
        }
    }

    std::cout << c;
}