/*
Balkan 2019 Clear the Memory
- When we check a candidate pref, we do a reverse BFS
- Initially, we only process the programs with no 1s in [1, pref]
- We need a data structure that supports the following two operations:
    1) Set a 1 in [1, pref] to 0
    2) Push a program into the queue when all its 1s in [1, pref] have
       been set to 0s
- For the first operation, a simple std::set sufficies
- For the second operation, we use a min segtree
    - We try to run operation 2 each time a bit x has been set to 0
    - First, find l and r such that l <= x <= r and [l, r] is as large as possible
    - Next, we use the segtree to find all ranges completely contained in [l, r]
    - Finally, we can decrement a counter for each program of each range
    - When the counter reaches 0, we push the program into the queue
- pref works iff each bit in [1, pref] has been set to 0
- To avoid binsearch, we do magic greedy stuff that I'm too tired to explain
- Complexity: O(M log M)
*/

#include <bits/stdc++.h>
using namespace std;

const tuple<int, int, int> MN = make_tuple(INT_MAX, INT_MAX, 0);

int n, m, t;
vector<pair<int, int>> has_0[500001], has_1[500001];
tuple<int, int, int> segtree[2000001];
int cnt_1[500001], ptr[500001];
queue<int> q;

void update(int pos, tuple<int, int, int> val, int node = 1, int l = 1, int r = m) {
    if (l == r) segtree[node] = val;
    else {
        int mid = (l + r) / 2;
        if (pos > mid) update(pos, val, node * 2 + 1, mid + 1, r);
        else update(pos, val, node * 2, l, mid);
        segtree[node] = min(segtree[node * 2], segtree[node * 2 + 1]);
    }
}

tuple<int, int, int> query(int a, int b, int node = 1, int l = 1, int r = m) {
    if (l > b || r < a) return MN;
    if (l >= a && r <= b) return segtree[node];
    int mid = (l + r) / 2;
    return min(query(a, b, node * 2, l, mid), query(a, b, node * 2 + 1, mid + 1, r));
}

void queryupdate(int a, int b) {
    int r, l, p;
    tie(r, l, p) = query(a, b);
    while (r <= b) {
        cnt_1[p]--;
        if (!cnt_1[p]) q.push(p);
        if (ptr[l] < has_1[l].size()) {
            update(l, make_tuple(has_1[l][ptr[l]].first, l, has_1[l][ptr[l]].second));
            ptr[l]++;
        } else update(l, MN);
        tie(r, l, p) = query(a, b);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> t;
    while (t--) {
        int p, l, r, v;
        cin >> p >> l >> r >> v;
        if (v) {
            has_1[l].push_back({r, p});
            cnt_1[p]++;
        } else has_0[p].push_back({l, r});
    }
    
    set<int> unset; unset.insert(0), unset.insert(m + 1);
    for (int i = 1; i <= m; i++) {
        sort(has_1[i].begin(), has_1[i].end());
        unset.insert(i);
        if (has_1[i].size()) {
            ptr[i] = 1;
            update(i, make_tuple(has_1[i][0].first, i, has_1[i][0].second));
        } else update(i, MN);
    }

    for (int i = 1; i <= n; i++) if (!cnt_1[i]) q.push(i);
    for (int pref = m; ~pref;) {
        while (q.size()) {
            int curr = q.front();
            q.pop();
            for (pair<int, int> i : has_0[curr]) {
                set<int>::iterator lb = unset.lower_bound(i.first);
                while (*lb <= min(pref, i.second)) {
                    int a = *prev(lb) + 1, b = *next(lb) - 1;
                    queryupdate(a, b);
                    unset.erase(lb);
                    lb = unset.lower_bound(i.first);
                }
            }
        }

        if (!*next(unset.rbegin())) return cout << pref, 0;

        auto lb = next(unset.rbegin());
        int a = *next(lb) + 1, b = m;
        queryupdate(a, b);
        pref = *lb - 1;
        unset.erase(*lb);
    }
    return 0;
}