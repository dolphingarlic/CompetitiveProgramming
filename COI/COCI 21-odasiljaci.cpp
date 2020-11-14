#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

pair<int, int> p[1000];
vector<tuple<double, int, int>> edges;
int n, cmp[1000];

int find(int A) {
    while (cmp[A] != A) cmp[A] = cmp[cmp[A]], A = cmp[A];
    return A;
}

void onion(int A, int B) {
    if (find(A) != find(B)) n--;
    cmp[find(A)] = find(B);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p[i].first >> p[i].second;
        for (int j = 0; j < i; j++) {
            edges.push_back({hypot(p[i].first - p[j].first, p[i].second - p[j].second), i, j});
        }
    }
    sort(edges.begin(), edges.end());
    iota(cmp, cmp + n, 0);
    for (tuple<double, int, int> i : edges) {
        double cost;
        int a, b;
        tie(cost, a, b) = i;
        onion(a, b);
        if (n == 1) return cout << fixed << setprecision(8) << cost / 2, 0;
    }
    return 0;
}