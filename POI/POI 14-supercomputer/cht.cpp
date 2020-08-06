/*
POI 2014 Supercomputer
- First, do a DFS and find the number of nodes at each depth
- Let cnt[i] = Number of nodes with depth > i
- Notice how the series of operations if going to look like
  (Spend D time units processing the nodes with depth <= D) + (Spend ceil(cnt[D] / K[i]) time units processing the rest)
    - i.e. There is a bottleneck
- Clearly, the answer for some K[i] is the maximum of these for all D
- Let f(i, x) = i * x + cnt[i]
- Since these functions are linear, we can use CHT to quickly find the maximum at any given point
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Line {
    bool type;
    double x;
    ll m, c;
};

bool operator<(Line l1, Line l2) {
    if (l1.type || l2.type) return l1.x < l2.x;
    return l1.m < l2.m;
}

int k[1000001], cnt[1000001], mx_depth = 0;
vector<int> graph[1000001];
set<Line> cht;

void dfs(int node = 1, int depth = 1) {
    cnt[depth]++;
    mx_depth = max(mx_depth, depth);
    for (int i : graph[node]) dfs(i, depth + 1);
}

bool has_prev(set<Line>::iterator it) { return it != cht.begin(); }
bool has_next(set<Line>::iterator it) { return it != cht.end() && next(it) != cht.end(); }

double intersect(set<Line>::iterator l1, set<Line>::iterator l2) {
    return (double)(l1->c - l2->c) / (l2->m - l1->m);
}

void calc_x(set<Line>::iterator it) {
    if (has_prev(it)) {
        Line l = *it;
        l.x = intersect(prev(it), it);
        cht.insert(cht.erase(it), l);
    }
}

bool bad(set<Line>::iterator it) {
    if (has_next(it) && next(it)->c >= it->c) return true;
    return (has_prev(it) && has_next(it) && intersect(prev(it), next(it)) <= intersect(prev(it), it));
}

void add_line(ll m, ll c) {
    set<Line>::iterator it;
    
    it = cht.lower_bound({0, 0, m, c});
    if (it != cht.end() && it->m == m) {
        if (it->c >= c) return;
        else cht.erase(it);
    }

    it = cht.insert({0, 0, m, c}).first;
    if (bad(it)) cht.erase(it);
    else {
        while (has_prev(it) && bad(prev(it))) cht.erase(prev(it));
        while (has_next(it) && bad(next(it))) cht.erase(next(it));

        if (has_next(it)) calc_x(next(it));
        calc_x(it);
    }
}

ll query(ll x) {
    Line l = *prev(cht.upper_bound({1, (double)x, 0, 0}));
    return l.m * x + l.c;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    FOR(i, 0, q) cin >> k[i];
    FOR(i, 1, n) {
        int p;
        cin >> p;
        graph[p].push_back(i + 1);
    }
    dfs();

    for (int i = mx_depth, deeper = 0; i; deeper += cnt[i--])
        add_line(i, deeper);
    
    FOR(i, 0, q) {
        ll f = query(k[i]);
        cout << f / k[i] + (f % k[i] != 0) << ' ';
    }
    return 0;
}