#include <bits/stdc++.h>
using namespace std;

vector<int> pr[4] = {{3, 0, 1, 2}, {0, 1, 2, 3}, {1, 2, 3, 0}, {2, 3, 0, 1}};

int x[100005], y[100005];
pair<int, int> wall[200005];
vector<int> dot;
int to[4][100005];
set<int> in;
set<int> ans;
int last;

void remove(int id) {
    int v = wall[id].first, u = wall[id].second;
    for (int i = 0; i < 4; i++) {
        if (to[i][v] == id) to[i][v] = -1;
        if (to[i][u] == id) to[i][u] = -1;
    }
}

int change(int& v) {
    for (int x : pr[last]) {
        if (to[x][v] != -1) {
            int e = to[x][v];
            if (in.count(e))
                ans.insert(e);
            else
                in.insert(e);
            v = wall[e].first + wall[e].second - v;
            last = x;
            break;
        }
    }
    return v;
}

int main() {
    memset(to, -1, sizeof to);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        dot.push_back(i);
        dot.push_back(i);
    }
    sort(dot.begin(), dot.end(), [](const int& lhs, const int& rhs) {
        if (x[lhs] != x[rhs]) return x[lhs] < x[rhs];
        return y[lhs] < y[rhs];
    });

    int w;
    cin >> w;
    for (int i = 0; i < w; i++) {
        int v, u;
        cin >> v >> u;
        v--;
        u--;
        wall[i].first = v;
        wall[i].second = u;
        if (x[v] == x[u]) {
            if (y[v] < y[u]) swap(v, u);
            to[0][u] = i;
            to[2][v] = i;
        } else {
            if (x[v] < x[u]) swap(v, u);
            to[1][u] = i;
            to[3][v] = i;
        }
    }
    for (int a : dot) {
        if (to[0][a] + to[1][a] + to[2][a] + to[3][a] == -4) continue;
        last = 1;
        in.clear();
        int v = a;
        while (change(v) != a)
            ;
        for (int x : in) remove(x);
    }
    cout << ans.size() << '\n';
    for (int x : ans) cout << x + 1 << '\n';
}