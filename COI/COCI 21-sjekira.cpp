#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<pair<int, int>> edges;
ll hardness[100001], ans = 0;
int cmp[100001];

int find(int A) {
    while (cmp[A] != A) cmp[A] = cmp[cmp[A]], A = cmp[A];
    return A;
}

void onion(int A, int B) {
    A = find(A), B = find(B);
    if (A == B) return;
    ans += hardness[A] + hardness[B];
    hardness[B] = max(hardness[B], hardness[A]);
    cmp[A] = B;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> hardness[i];
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        if (hardness[a] < hardness[b]) swap(a, b);
        edges.push_back({a, b});
    }
    sort(edges.begin(), edges.end(), [](pair<int, int> A, pair<int, int> B) { return hardness[A.first] < hardness[B.first]; });
    iota(cmp + 1, cmp + n + 1, 1);
    for (pair<int, int> i : edges) onion(i.first, i.second);
    cout << ans;
    return 0;
}