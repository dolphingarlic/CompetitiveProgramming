#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<pair<int, int>> swaps[5000];

int swapsort(int l, int r) {
    if (l == r) return 0;

    int mid = (l + r) / 2;
    int depth = max(swapsort(l, mid), swapsort(mid + 1, r));

    for (int i = 0; i <= mid - l; i++) {
        for (int x = mid, y = r + (mid - l != r - mid - 1) - i; x >= l + i; x--, y--)
            if (y <= r) swaps[depth + 1 + i].push_back({x, y});
    }
    return depth + mid - l + 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    int depth = swapsort(1, n);
    cout << depth << '\n';
    for (int i = 1; i <= depth; i++) {
        for (pair<int, int> j : swaps[i]) if (j.second <= n)
            cout << "CMPSWP R" << j.first << " R" << j.second << ' ';
        cout << '\n';
    }
    return 0;
}
