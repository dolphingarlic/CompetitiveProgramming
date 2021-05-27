/*
APIO 2018 New Home
- Consider the case where all stores are always active
- We basically want the maximum of a bunch of "broken absolute value" graphs
- Consider the positive and negative slopes separately
- If we do this, then we get a bunch of line segments
- WLOG, extend the line segments into rays that go below the x-axis
- Since all slopes are equal, we only need to store the x-intersect of each ray
- Queries thus become prefix maximum queries (i.e. maximum ray that starts
  before the queried position)
- We can handle this using a simple segment tree
- To handle the general case, notice that there are O(N) possible rays, each
  with a period of relevance
- We can thus create a second segment tree indexed on time, where each leaf
  is a query, and DFS on that tree to update our first segment tree
- We can avoid an additional log N factor by keeping an array of sets that
  store "hidden" values at each point
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,fma,avx")
typedef long long ll;
using namespace std;

const int INF = 1e8;

vector<int> c_loc, c_time;
unordered_map<int, vector<pair<int, int>>> queries, toggle, ins, del;
vector<tuple<int, int, int>> stores[300001];
int ans[300001], segtree[1200001];
multiset<int> rays[300001];

int query(int loc, int node = 1, int l = 0, int r = c_loc.size() - 1) {
    if (r <= loc) return segtree[node];
    if (l > loc) return -INF;
    int mid = (l + r) / 2;
    return max(query(loc, node * 2, l, mid),
               query(loc, node * 2 + 1, mid + 1, r));
}

void update(int loc, int val, int node = 1, int l = 0,
            int r = c_loc.size() - 1) {
    if (l == r)
        segtree[node] = val;
    else {
        int mid = (l + r) / 2;
        if (loc > mid)
            update(loc, val, node * 2 + 1, mid + 1, r);
        else
            update(loc, val, node * 2, l, mid);
        segtree[node] = max(segtree[node * 2], segtree[node * 2 + 1]);
    }
}

void ins_ray(int loc, int val) {
    if (loc == c_loc.size()) return;
    rays[loc].insert(val);
    update(loc, *rays[loc].rbegin());
}

void del_ray(int loc, int val) {
    if (loc == c_loc.size()) return;
    rays[loc].erase(rays[loc].find(val));
    update(loc, *rays[loc].rbegin());
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k, q;
    cin >> n >> k >> q;
    for (int i = 1; i <= n; i++) {
        int loc, type, a, b;
        cin >> loc >> type >> a >> b;
        stores[type].push_back({a, loc, 0});
        stores[type].push_back({b + 1, loc, 1});
    }
    for (int i = 1; i <= q; i++) {
        int loc, time;
        cin >> loc >> time;
        c_loc.push_back(2 * loc);
        c_time.push_back(time);
        queries[time].push_back({i, loc});
        ans[i] = -1;
    }
    sort(c_loc.begin(), c_loc.end());
    c_loc.erase(unique(c_loc.begin(), c_loc.end()), c_loc.end());
    sort(c_time.begin(), c_time.end());
    c_time.erase(unique(c_time.begin(), c_time.end()), c_time.end());
    c_time.push_back(INF + 1);

    for (int _ : {0, 1}) {
        for (int i = 0; i < c_loc.size(); i++) {
            rays[i].clear();
            rays[i].insert(-INF);
        }
        for (int i = 1; i <= k; i++)
            for (auto& j : stores[i]) get<1>(j) = INF + 1 - get<1>(j);
        for (auto& i : queries)
            for (auto& j : i.second) j.second = INF + 1 - j.second;
        for (auto& i : c_loc) i = 2 * INF + 2 - i;
        reverse(c_loc.begin(), c_loc.end());
        toggle.clear();
        ins.clear();
        del.clear();

        for (int t = 1; t <= k; t++) {
            sort(stores[t].begin(), stores[t].end());
            map<int, int> active, ray_at;
            for (auto i : stores[t]) {
                int time, loc, close;
                tie(time, loc, close) = i;
                time = *lower_bound(c_time.begin(), c_time.end(), time);
                if (close) {
                    active[loc]--;
                    if (!active[loc]) {
                        active.erase(loc);
                        auto ub = active.upper_bound(loc);
                        del[time].push_back({ray_at[loc], loc});
                        if (ub != active.end()) {
                            del[time].push_back({ray_at[ub->first], ub->first});
                            if (ub != active.begin()) {
                                ins[time].push_back(
                                    {prev(ub)->first + ub->first, ub->first});
                                ray_at[ub->first] = prev(ub)->first + ub->first;
                            } else {
                                ins[time].push_back({0, ub->first});
                                ray_at[ub->first] = 0;
                            }
                        }
                    }
                } else {
                    if (!active.count(loc)) {
                        auto ub = active.upper_bound(loc);
                        if (ub != active.end()) {
                            del[time].push_back({ray_at[ub->first], ub->first});
                            ins[time].push_back({ub->first + loc, ub->first});
                            ray_at[ub->first] = ub->first + loc;
                        }
                        if (ub != active.begin()) {
                            ins[time].push_back({loc + prev(ub)->first, loc});
                            ray_at[loc] = loc + prev(ub)->first;
                        } else {
                            ins[time].push_back({0, loc});
                            ray_at[loc] = 0;
                        }
                    }
                    active[loc]++;
                }
                toggle[time].push_back({t, 1 - 2 * close});
            }
        }

        unordered_map<int, int> active;
        fill_n(segtree + 1, 4 * c_loc.size(), -INF);
        for (int t : c_time) {
            for (pair<int, int> i : ins[t])
                ins_ray(lower_bound(c_loc.begin(), c_loc.end(), i.first) -
                            c_loc.begin(),
                        i.second);
            for (pair<int, int> i : del[t])
                del_ray(lower_bound(c_loc.begin(), c_loc.end(), i.first) -
                            c_loc.begin(),
                        i.second);
            for (pair<int, int> i : toggle[t]) {
                active[i.first] += i.second;
                if (!active[i.first]) active.erase(i.first);
            }
            if (active.size() == k) {
                for (pair<int, int> i : queries[t]) {
                    int res = query(
                        lower_bound(c_loc.begin(), c_loc.end(), 2 * i.second) -
                        c_loc.begin());
                    ans[i.first] = max(ans[i.first], res - i.second);
                }
            }
        }
    }
    for (int i = 1; i <= q; i++) cout << ans[i] << '\n';
    return 0;
}
