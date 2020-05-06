/*
Baltic 2019 Olympiads
- First, we construct the best team
    - For each event, choose the best person for that event that hasn't already been chosen
- We can then split the search space into several disjoint subspaces
    - Subspace i = Forced to have first (i - 1) members from the current best team and don't have member i
    - Notice how this just works
    - We can use a priority queue to keep track of which subspace is the best
- Since all bounds are really small, straight brute force works
- Complexity: O(NK^2C log C)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Frag {
    int score;
    vector<int> best, forced;
    vector<bool> forbidden;
};

bool operator<(Frag A, Frag B) { return A.score < B.score; }

int n, k, c, stud[500][6];

Frag fill_best(Frag init) {
    init.best = init.forced;
    init.score = 0;
    FOR(i, init.best.size(), k) {
        init.best.push_back(-1);
        FOR(j, 0, n)
            if (!init.forbidden[j] && find(init.best.begin(), init.best.end(), j) == init.best.end())
                if (init.best[i] == -1 || stud[init.best[i]][i] < stud[j][i])
                    init.best.pop_back(), init.best.push_back(j);
    }
    vector<int> event_best(k, 0);
    FOR(i, 0, k) if (~init.best[i]) FOR(j, 0, k) event_best[j] = max(event_best[j], stud[init.best[i]][j]);
    FOR(i, 0, k) init.score += event_best[i];
    return init;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k >> c;
    FOR(i, 0, n) FOR(j, 0, k) cin >> stud[i][j];
    priority_queue<Frag> pq;
    pq.push(fill_best({0, {}, {}, vector<bool>(n, false)}));
    while (c--) {
        Frag curr = pq.top();
        pq.pop();

        if (!c) cout << curr.score;
        FOR(i, curr.forced.size(), k) {
            curr.forbidden[curr.best[i]] = true;
            Frag nxt = fill_best(curr);
            if (find(nxt.best.begin(), nxt.best.end(), -1) == nxt.best.end())
                pq.push(nxt);
            curr.forbidden[curr.best[i]] = false;
            curr.forced.push_back(curr.best[i]);
        }
    }
    return 0;
}