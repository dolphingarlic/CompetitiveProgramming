/*
CEOI 2013 Tram
- We only really care about the occupied rows
    - In those rows, the answer is either one of the endpoints or the median
- Since each insertion/deletion changes at most 2 intervals, we can just keep
  a std::set of the intervals and update accordingly
- Complexity: O(M log M)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, m;
bool used[150001][3];
set<int> hmmst;

ll dist(pair<int, int> A, pair<int, int> B) {
    return ll(B.first - A.first) * ll(B.first - A.first) +
           ll(B.second - A.second) * ll(B.second - A.second);
}

struct Interval {
    int l, r;
    ll best_dist;
    pair<int, int> best_pos;

    void update() {
        best_dist = -1;
        int mid1 = (l + r) / 2, mid2 = (l + r + 1) / 2;
        vector<pair<int, int>> cand = {{l, 1},    {l, 2},    {mid1, 1}, {mid1, 2},
                                       {mid2, 1}, {mid2, 2},  {r, 1},   {r, 2}};
        for (pair<int, int> j : cand) {
            if (!used[j.first][j.second]) {
                ll d = LLONG_MAX;
                for (pair<int, int> k : cand) {
                    if (used[k.first][k.second]) {
                        d = min(d, dist(j, k));
                    }
                }
                if (d > best_dist && (d != LLONG_MAX || hmmst.size() == 2)) {
                    best_dist = d;
                    best_pos = j;
                }
            }
        }
    }
};
bool operator<(Interval A, Interval B) {
    return (A.best_dist == B.best_dist ? A.best_pos < B.best_pos : A.best_dist > B.best_dist);
}

pair<int, int> pos[30001];
set<Interval> intervals;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    hmmst.insert(1);
    hmmst.insert(n);
    Interval i = {1, n, LLONG_MAX, {1, 1}};
    intervals.insert(i);

    for (int i = 1; i <= m; i++) {
        char c;
        cin >> c;
        if (c == 'E') {
            Interval opt = *intervals.begin();
            intervals.erase(opt);
            pos[i] = opt.best_pos;
            used[pos[i].first][pos[i].second] = true;
            hmmst.insert(pos[i].first);
            if (pos[i].first != opt.l && pos[i].first != opt.r) {
                used[pos[i].first][pos[i].second] = true;
                Interval A = {opt.l, pos[i].first, 0, {0, 0}}, B = {pos[i].first, opt.r, 0, {0, 0}};
                A.update(), B.update();
                intervals.insert(A), intervals.insert(B);
            } else {
                if (pos[i].first == 1) {
                    int r = *next(hmmst.find(1));
                    Interval A = {1, r, 0, {0, 0}};
                    A.update();
                    intervals.erase(A);
                    used[pos[i].first][pos[i].second] = true;
                    A.update();
                    intervals.insert(A);
                } else if (pos[i].first == n) {
                    int l = *prev(hmmst.find(n));
                    Interval A = {l, n, 0, {0, 0}};
                    A.update();
                    intervals.erase(A);
                    used[pos[i].first][pos[i].second] = true;
                    A.update();
                    intervals.insert(A);
                } else {
                    int l = *prev(hmmst.find(pos[i].first)), r = *next(hmmst.find(pos[i].first));
                    Interval A = {l, pos[i].first, 0, {0, 0}}, B = {pos[i].first, r, 0, {0, 0}};
                    A.update(), B.update();
                    intervals.erase(A), intervals.erase(B);
                    used[pos[i].first][pos[i].second] = true;
                    if (!used[pos[i].first][1] && !used[pos[i].first][2]) {
                        hmmst.erase(pos[i].first);
                        Interval C = {l, r, 0, {0, 0}};
                        C.update();
                        intervals.insert(C);
                    } else {
                        A.update(), B.update();
                        intervals.insert(A), intervals.insert(B);
                    }
                }
            }
            cout << pos[i].first << ' ' << pos[i].second << '\n';
        } else {
            int idx;
            cin >> idx;
            if (pos[idx].first == 1) {
                int r = *next(hmmst.find(1));
                Interval A = {1, r, 0, {0, 0}};
                A.update();
                intervals.erase(A);
                used[pos[idx].first][pos[idx].second] = false;
                A.update();
                intervals.insert(A);
            } else if (pos[idx].first == n) {
                int l = *prev(hmmst.find(n));
                Interval A = {l, n, 0, {0, 0}};
                A.update();
                intervals.erase(A);
                used[pos[idx].first][pos[idx].second] = false;
                A.update();
                intervals.insert(A);
            } else {
                int l = *prev(hmmst.find(pos[idx].first)), r = *next(hmmst.find(pos[idx].first));
                Interval A = {l, pos[idx].first, 0, {0, 0}}, B = {pos[idx].first, r, 0, {0, 0}};
                A.update(), B.update();
                intervals.erase(A), intervals.erase(B);
                used[pos[idx].first][pos[idx].second] = false;
                if (!used[pos[idx].first][1] && !used[pos[idx].first][2]) {
                    hmmst.erase(pos[idx].first);
                    Interval C = {l, r, 0, {0, 0}};
                    C.update();
                    intervals.insert(C);
                } else {
                    A.update(), B.update();
                    intervals.insert(A), intervals.insert(B);
                }
            }
        }
    }
    return 0;
}