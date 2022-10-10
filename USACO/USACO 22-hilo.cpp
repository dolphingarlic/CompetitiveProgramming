#include <iostream>
#include <stack>

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int n, pos[200001], prv[200001];
    bool hilo[200001];
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        int p;
        std::cin >> p;
        pos[p] = i;
    }

    std::stack<int> stck;
    stck.push(0);
    for (int i = n; i > 0; i--) {
        while (stck.top() > pos[i]) stck.pop();
        prv[pos[i]] = stck.top();
        stck.push(pos[i]);
    }
    while (stck.size() != 1) stck.pop();

    std::cout << "0\n";
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        while (stck.top() > pos[i]) {
            cnt -= hilo[stck.top()];
            stck.pop();
        }
        hilo[pos[i]] = prv[pos[i]] != 0 &&
                       (stck.top() == 0 || prv[pos[i]] != prv[stck.top()]);
        stck.push(pos[i]);
        cnt += hilo[pos[i]];
        std::cout << cnt << '\n';
    }
    return 0;
}
