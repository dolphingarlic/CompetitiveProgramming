#include <bits/stdc++.h>
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,fma,avx")
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

struct Node {
    int id, region, low, high;
    vector<int> children;
};
struct Region {
    vector<int> ids;
    vector<pair<int, int>> ranges;
    int depth;
};

Node nodes[200001];
Region regions[25001];

map<int, int> cache;

void dfs(int node, int& id_pool) {
    int id = id_pool++;
    int r = nodes[node].region;
    regions[r].ids.push_back(id);
    regions[r].depth++;
    regions[r].ranges.push_back({id_pool, regions[r].depth});

    for (int i : nodes[node].children) dfs(i, id_pool);
    regions[r].depth--;
    regions[r].ranges.push_back({id_pool, regions[r].depth});
}

inline int query(Region a, Region b) {
    if (a.ranges.empty()) return 0;

    int ans = 0, id = 0;
    while (id != b.ids.size() && b.ids[id] < a.ranges[0].first) id++;

    for (int i = 0; i < a.ranges.size() - 1 && id != b.ids.size(); i++) {
        int pos2 = a.ranges[i + 1].first, depth = a.ranges[i].second;

        int old = id;
        while (id != b.ids.size() && b.ids[id] < pos2) id++;
        ans += depth * (id - old);
    }

    return ans;
}

int main() {
    int n, r, q;
    scanf("%d %d %d", &n, &r, &q);
    scanf("%d", &nodes[1].region);
    FOR(i, 2, n + 1) {
        int p;
        scanf("%d %d", &p, &nodes[i].region);
        nodes[p].children.push_back(i);
    }

    int id_pool = 1;
    dfs(1, id_pool);

    while (q--) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (cache.find(25000 * a + b) != cache.end())
            printf("%d\n", cache[25000 * a + b]);
        else {
            int q = query(regions[a], regions[b]);
            printf("%d\n", q);
            cache[25000 * a + b] = q;
        }
        fflush(stdout);
    }
    return 0;
}