#include <iostream>
using namespace std;

int neighbours[1000000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, ans = 0;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        neighbours[u]++;
        neighbours[v]++;
    }
    for (int i = 0; i < n; i++) {
        if (neighbours[i] > 1) ans++;
    }
    cout << ans;
    return 0;
}
