#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#pragma GCC Optimize("unroll-loops")
#pragma GCC target ("sse4")
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

const int c = 550;

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

int ans1[200000 / c][25001], ans2[25001][200000 / c], maps_to[25001];

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

    int ans = 0;
    vector<int>::iterator id = b.ids.begin();
    while (id != b.ids.end() && *id < a.ranges[0].first) id++;

    for (int i = 0; i < a.ranges.size() - 1 && id != b.ids.end(); i++) {
        int pos2 = a.ranges[i + 1].first, depth = a.ranges[i].second;

        vector<int>::iterator old = id;
        while (id != b.ids.end() && *id < pos2) id++;
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

    int cnt = 1;
    FOR(i, 1, r + 1) {
        if (regions[i].ids.size() > c) {
            FOR(j, 1, r + 1) {
                ans1[cnt][j] = query(regions[i], regions[j]);
                ans2[j][cnt] = query(regions[j], regions[i]);
            }
            maps_to[i] = cnt++;
        }
    }

    while (q--) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (regions[a].ids.size() > c) printf("%d\n", ans1[maps_to[a]][b]);
        else if (regions[b].ids.size() > c) printf("%d\n", ans2[a][maps_to[b]]);
        else printf("%d\n", query(regions[a], regions[b]));
        fflush(stdout);
    }
    return 0;
}