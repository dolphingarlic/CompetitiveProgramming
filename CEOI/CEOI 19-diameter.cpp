/*
CEOI 2019 Dynamic Diameter
- Let's consider the second-last subtask
- Precompute the distances from node 1 to each other node, and sort
  the nodes by DFS order
- When we update an edge, we change all distances in a subtree by a fixed
amount, so we can use a lazy segtree to handle updates
- The answer is simply the sum of the two best distances, which we can handle
with range maximum queries
- To solve the general case, use centroid decomposition
- Complexity: O(N log^2 N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Segtree {
    int sz;
    vector<ll> vals, lazy;

    void push_lazy(int node, int l, int r) {
        vals[node] += lazy[node];
        if (l != r) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }

    void update(int a, int b, ll val, int node, int l, int r) {
        push_lazy(node, l, r);
        if (l > b || r < a) return;
        if (l >= a && r <= b) {
            lazy[node] = val;
            push_lazy(node, l, r);
        } else {
            int mid = (l + r) / 2;
            update(a, b, val, node * 2, l, mid);
            update(a, b, val, node * 2 + 1, mid + 1, r);
            vals[node] = max(vals[node * 2], vals[node * 2 + 1]);
        }
    }

    ll query(int a, int b, int node, int l, int r) {
        push_lazy(node, l, r);
        if (l > b || r < a) return 0;
        if (l >= a && r <= b) return vals[node];
        int mid = (l + r) / 2;
        return max(query(a, b, node * 2, l, mid),
                   query(a, b, node * 2 + 1, mid + 1, r));
    }

    void build(vector<ll> &dists, int node, int l, int r) {
        if (l == r)
            vals[node] = dists[l];
        else {
            int mid = (l + r) / 2;
            build(dists, node * 2, l, mid);
            build(dists, node * 2 + 1, mid + 1, r);
            vals[node] = max(vals[node * 2], vals[node * 2 + 1]);
        }
    }

    void init(vector<ll> &dists) {
        sz = dists.size();
        vals.resize(4 * sz), lazy.resize(4 * sz);
        build(dists, 1, 1, sz);
    }
} segtree[100001];

ll e_weight[100001];
pair<int, int> e_nodes[100001];
vector<pair<int, int>> graph[100001];
bool processed[100001];
int subtree[100001], c_par[100001], c_level[100001];
int tin[18][100001], tout[18][100001], timer;
vector<int> c_timers[100001];
vector<ll> dists;
multiset<ll> ms_all, ms_centroid[100001];

void get_subtree_sizes(int node, int parent = 0) {
    subtree[node] = 1;
    for (pair<int, int> i : graph[node])
        if (i.first != parent && !processed[i.first]) {
            get_subtree_sizes(i.first, node);
            subtree[node] += subtree[i.first];
        }
}

int get_centroid(int node, int parent, int tree_size) {
    for (pair<int, int> i : graph[node])
        if (i.first != parent && !processed[i.first] &&
            subtree[i.first] > tree_size)
            return get_centroid(i.first, node, tree_size);
    return node;
}

ll get_dists(int node, int parent, int level, ll curr_dist) {
    tin[level][node] = ++timer;

    dists.push_back(curr_dist);
    ll ret = curr_dist;
    for (pair<int, int> i : graph[node])
        if (i.first != parent && !processed[i.first])
            ret = max(ret, get_dists(i.first, node, level,
                                     curr_dist + e_weight[i.second]));

    tout[level][node] = timer;

    return ret;
}

void centroid_decomp(int node = 1, int prv_centroid = 0, int level = 0) {
    get_subtree_sizes(node);
    int centroid = get_centroid(node, 0, subtree[node] / 2);
    c_par[centroid] = prv_centroid;
    c_level[centroid] = level;

    dists.clear();
    timer = 0;
    ms_centroid[centroid].insert(0), ms_centroid[centroid].insert(0);
    dists.push_back(0);
    for (pair<int, int> i : graph[centroid])
        if (!processed[i.first]) {
            ms_centroid[centroid].insert(
                get_dists(i.first, centroid, level, e_weight[i.second]));
            c_timers[centroid].push_back(timer);
        }
    tin[level][centroid] = 0, tout[level][centroid] = timer + 1;
    segtree[centroid].init(dists);
    ms_all.insert(*ms_centroid[centroid].rbegin() +
                  *next(ms_centroid[centroid].rbegin()));

    processed[centroid] = true;
    for (pair<int, int> i : graph[centroid])
        if (!processed[i.first]) centroid_decomp(i.first, centroid, level + 1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    ll w;
    cin >> n >> q >> w;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v >> e_weight[i];
        graph[u].push_back({v, i});
        graph[v].push_back({u, i});
        e_nodes[i] = {u, v};
    }
    centroid_decomp();

    ll last = 0;
    while (q--) {
        int d;
        ll e;
        cin >> d >> e;
        d = (d + last) % (n - 1), e = (e + last) % w;

        ll delta = e - e_weight[d];
        int u = e_nodes[d].first, v = e_nodes[d].second;
        int node = (c_level[u] < c_level[v] ? u : v);
        while (node) {
            auto lb = lower_bound(
                c_timers[node].begin(), c_timers[node].end(),
                min(tout[c_level[node]][u], tout[c_level[node]][v]));

            ms_all.erase(ms_all.find(*ms_centroid[node].rbegin() +
                                     *next(ms_centroid[node].rbegin())));
            ms_centroid[node].erase(ms_centroid[node].find(segtree[node].query(
                *prev(lb) + 1, *lb, 1, 1, segtree[node].sz)));
            segtree[node].update(
                max(tin[c_level[node]][u], tin[c_level[node]][v]),
                min(tout[c_level[node]][u], tout[c_level[node]][v]), delta, 1,
                1, segtree[node].sz);
            ms_centroid[node].insert(segtree[node].query(*prev(lb) + 1, *lb, 1,
                                                         1, segtree[node].sz));
            ms_all.insert(*ms_centroid[node].rbegin() +
                          *next(ms_centroid[node].rbegin()));

            node = c_par[node];
        }
        e_weight[d] = e;

        last = *ms_all.rbegin();
        cout << last << '\n';
    }
    return 0;
}
