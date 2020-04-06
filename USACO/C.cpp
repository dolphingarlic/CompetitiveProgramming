#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n;
vector<int> graph[8];
bool has[8];

bool is_valid(int mask, int base) {
    FOR(i, 0, 8) has[i] = false;
    mask <<= 3;
    FOR(i, 0, base) {
        mask >>= 3;
        if (has[mask & 7] || (mask & 7) >= n) return false;
        has[mask & 7] = true;
    }
    return true;
}

int cmp[823543], ans;

int find(int A) {
    while (A != cmp[A]) cmp[A] = cmp[cmp[A]], A = cmp[A];
    return A;
}

void onion(int A, int B) {
    A = find(A), B = find(B);
    if (A == B) return;
    ans--;
    cmp[A] = B;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ifstream cin("circus.in");
    ofstream cout("circus.out");
    cin >> n;
    FOR(i, 1, n) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int facto = 1, mx = 1;
    FOR(k, 1, n - 1) {
        facto *= (k + 1);
        mx <<= 3;

        ans = 0;
        FOR(i, 0, mx - 1) if (is_valid(i, k)) {
            ans++;
            cmp[i] = i;
        }
        FOR(i, 0, mx - 1) if (is_valid(i, k)) {
            FOR(j, 0, k) {
                int temp = (i & (7 << (3 * j))) >> (3 * j);
                for (int l : graph[temp]) {
                    int neighbour = i - (temp << (3 * j)) + (l << (3 * j));
                    if (is_valid(neighbour, k)) onion(i, neighbour);
                }
            }
        }
        cout << ans << '\n';
    }
    cout << facto << '\n' << facto * n << '\n';
    return 0;
}