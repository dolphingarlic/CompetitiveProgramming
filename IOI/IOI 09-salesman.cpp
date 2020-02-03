#include <bits/stdc++.h>
using namespace std;
#define N 500005
#define inf 2000000005
set<pair<int, int>> in;
int n, u, d, s, t, l, m;

vector<pair<int, int>> fair[N];

int dis(int f, int t) { return f <= t ? (t - f) * d : (f - t) * u; }

int query(int loc) {
    int res1, res2;
    auto it = in.lower_bound({loc, -inf});
    res1 = it == in.end() ? -inf : it->second - dis(it->first, loc);
    res2 = it == in.begin() ? -inf : (--it)->second - dis(it->first, loc);
    return max(res1, res2);
}

void update(int loc, int val) {
    if (query(loc) >= val) return;
    auto it = in.insert({loc, val}).first;
    it++;
    while (it != in.end() && it->second <= val - dis(loc, it->first))
        it = in.erase(it);
    it--;
    while (it != in.begin() && (--it)->second <= val - dis(loc, it->first))
        it = in.erase(it);
}

vector<pair<int, int>> tmp;

int main() {
    scanf("%d%d%d%d", &n, &u, &d, &s);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &t, &l, &m);
        fair[t].push_back({l, m});
    }
    update(s, 0);
    int sz;
    for (int i = 1; i < N; i++) {
        sz = fair[i].size();
        if (sz == 0) continue;
        tmp.clear();
        sort(fair[i].begin(), fair[i].end());

        for (int j = 0; j < sz; j++) {
            int res = fair[i][j].second + query(fair[i][j].first);
            tmp.push_back({res, res});
        }

        for (int j = 1; j < sz; j++)
            tmp[j].first =
                max(tmp[j].first, tmp[j - 1].first -
                                   dis(fair[i][j - 1].first, fair[i][j].first) +
                                   fair[i][j].second);
        for (int j = sz - 2; j >= 0; j--)
            tmp[j].second =
                max(tmp[j].second, tmp[j + 1].second -
                                   dis(fair[i][j + 1].first, fair[i][j].first) +
                                   fair[i][j].second);

        for (int j = 0; j < sz; j++)
            update(fair[i][j].first, max(tmp[j].first, tmp[j].second));
    }
    printf("%d", query(s));
}