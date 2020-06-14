/*
POI 2009 The Code
- https://github.com/thecodingwizard/competitive-programming/blob/master/POI/POI09-Code.cpp
- Basically, you have a binary tree and you do magic DFS stuff
- Complexity: O(N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const int N = 3e6;

int n, l[N], r[N], id[N];
bool leaf[N], important[N], sync[N], visited[N];
queue<int> to_process;

void dfs1(int x, int y) {
    if (leaf[x]) return;
    if (leaf[y]) important[x] = true;
    else dfs1(l[x], l[y]), dfs1(r[x], r[y]);
}

void dfs2(int x, int y) {
    if (leaf[x]) return dfs2(0, y);
    if (!x) {
        if (visited[y]) return;
        visited[y] = true;
    }
    if (leaf[y]) {
        if (!important[x]) {
            important[x] = true;
            to_process.push(x);
        }
    } else dfs2(l[x], l[y]), dfs2(r[x], r[y]);
}

void dfs3(int x, int y) {
    if (leaf[y]) {
        if (!leaf[x]) sync[y] = false;
    } else {
        if (leaf[x]) {
            if (visited[y]) return;
            visited[y] = true;
            dfs3(0, y);
        } else dfs3(l[x], l[y]), dfs3(r[x], r[y]);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;

    int idx = 1, cnt = 1;
    stack<int> stck;
    stck.push(0);
    while (n--) {
        char c;
        cin >> c;
        if (c == 'B') stck.pop();
        else if (c == 'X') {
            leaf[stck.top()] = true;
            id[stck.top()] = cnt++;
        } else {
            if (c == '0') l[stck.top()] = idx;
            else r[stck.top()] = idx;
            stck.push(idx++);
        }
    }

    fill(sync, sync + idx, true);
    important[0] = true;

    FOR(i, 0, idx) dfs1(0, i);

    FOR(i, 0, idx) if (!leaf[i] && important[i])
        to_process.push(i);

    while (to_process.size()) {
        int node = to_process.front(); to_process.pop();
        dfs2(node, 0);
    }

    fill(visited, visited + idx, false);
    FOR(i, 0, idx) if (!leaf[i] && important[i])
        dfs3(i, 0);

    vector<int> ans;
    FOR(i, 0, idx) if (leaf[i] && sync[i])
        ans.push_back(i);
    cout << ans.size() << '\n';
    for (int i : ans) cout << id[i] << '\n';
    return 0;
}