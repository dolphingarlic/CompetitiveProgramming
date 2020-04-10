#include <bits/stdc++.h>

using namespace std;

struct tree {
    int x, y;
};

struct compare_x {
    bool operator()(const tree &a, const tree &b) const {
        return tie(a.x, a.y) < tie(b.x, b.y);
    }
};

struct compare_y {
    bool operator()(const tree &a, const tree &b) const { return a.y < b.y; }
};

int main() {
    ios::sync_with_stdio(false);
    int N, W;
    cin >> N >> W;
    vector<tree> trees(N);
    for (int i = 0; i < N; i++) cin >> trees[i].x >> trees[i].y;

    sort(trees.begin(), trees.end(), compare_y());
    set<tree, compare_x> edges{tree{0, -1}, tree{W, W + 1}};
    multiset<int> gaps{W};
    int ans = 0;
    int p = 0;
    for (int i = -1; i < N; i++) {
        int y0 = 0;
        if (i != -1) {
            const tree &t = trees[i];
            y0 = t.y;
            auto pos = edges.find(t);
            assert(pos != edges.end());
            auto a = prev(pos);
            auto b = next(pos);
            gaps.erase(gaps.find(t.x - a->x));
            gaps.erase(gaps.find(b->x - t.x));
            gaps.insert(b->x - a->x);
            edges.erase(pos);
        }
        if (p < i) p = i;
        int y1 = (p == N) ? W : trees[p].y;
        ans = max(ans, min(y1 - y0, *gaps.rbegin()));
        while (p < N && trees[p].y - y0 <= *gaps.rbegin()) {
            const tree &t = trees[p];
            auto b = edges.lower_bound(t);
            auto a = prev(b);
            gaps.erase(gaps.find(b->x - a->x));
            gaps.insert(t.x - a->x);
            gaps.insert(b->x - t.x);
            edges.insert(b, t);
            p++;
            y1 = (p == N) ? W : trees[p].y;
            ans = max(ans, min(y1 - y0, *gaps.rbegin()));
        }
    }
    cout << ans << '\n';
}