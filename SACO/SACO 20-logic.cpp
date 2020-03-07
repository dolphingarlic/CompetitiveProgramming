#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

vector<int> graph[2000001];
int type[2000001], res[2000001];
bool visited[2000001];
vector<int> stck;

void dfs(int node) {
    visited[node] = true;
    for (int i : graph[node]) if (!visited[i]) dfs(i);
    stck.push_back(node);
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int s, w, g, q;
    cin >> s >> w >> g >> q;
    FOR(i, 1, g + 1) {
        string t;
        cin >> t;
        if (t == "AND") type[i + s] = 0;
        if (t == "NOT") type[i + s] = 1;
        if (t == "OR") type[i + s] = 2;
        if (t == "XOR") type[i + s] = 3;
    }
    FOR(i, 0, w) {
        int x, y;
        cin >> x >> y;
        graph[x + s].push_back(y + s);
    }

    FOR(i, 0, s + g + 1) if (!visited[i]) dfs(i);
    reverse(stck.begin(), stck.end());

    while (q--) {
        FOR(i, 0, s + g + 1) {
            if (i >= s && !type[i]) res[i] = 1;
            else res[i] = 0;
        }
        FOR(i, 0, s) {
            int x;
            cin >> x;
            res[s - i - 1] = x;
        }
        for (int i : stck) {
            for (int j : graph[i]) {
                if (j == s) res[j] &= res[i];
                else {
                    switch (type[j]) {
                        case 0:
                            res[j] &= res[i];
                            break;
                        case 1:
                            res[j] = !res[i];
                            break;
                        case 2:
                            res[j] |= res[i];
                            break;
                        default:
                            res[j] ^= res[i];
                    }
                }
            }
        }
        cout << res[s] << '\n';
    }
    return 0;
}