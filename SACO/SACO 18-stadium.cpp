#include <bits/stdc++.h>
using namespace std;

struct tree {
    int x, y;
};

struct compare_x {
    bool operator()(const tree &a, const tree &b) const { return a.x < b.x; }
};

struct compare_y {
    bool operator()(const tree &a, const tree &b) const {
        return tie(a.y, a.x) < tie(b.y, b.x);
    }
};

int main() {
    ios::sync_with_stdio(false);
    int N, W;
    cin >> N >> W;
    vector<tree> trees(N);
    for (int i = 0; i < N; i++) cin >> trees[i].x >> trees[i].y;

    sort(trees.begin(), trees.end(), compare_x());
    set<tree, compare_y> edges{tree{-1, 0}, tree{W + 1, W}};
    multiset<int> gaps{W};
    int ans = 0;
    int p = 0;
    for (int i = -1; i < N; i++) {
        int x0 = 0;
        if (i != -1) {
            const tree &t = trees[i];
            x0 = t.x;
            auto pos = edges.find(t);
            assert(pos != edges.end());
            auto a = prev(pos);
            auto b = next(pos);
            gaps.erase(gaps.find(t.y - a->y));
            gaps.erase(gaps.find(b->y - t.y));
            gaps.insert(b->y - a->y);
            edges.erase(pos);
        }
        if (p < i) p = i;
        int x1 = (p == N) ? W : trees[p].x;
        ans = max(ans, min(x1 - x0, *gaps.rbegin()));
        while (p < N && trees[p].x - x0 <= *gaps.rbegin()) {
            const tree &t = trees[p];
            auto b = edges.lower_bound(t);
            auto a = prev(b);
            gaps.erase(gaps.find(b->y - a->y));
            gaps.insert(t.y - a->y);
            gaps.insert(b->y - t.y);
            edges.insert(b, t);
            p++;
            x1 = (p == N) ? W : trees[p].x;
            ans = max(ans, min(x1 - x0, *gaps.rbegin()));
        }
    }
    cout << ans << '\n';
}