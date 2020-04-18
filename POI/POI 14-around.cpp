/*
POI 2014 Around the World
- Firstly, notice that it's always optimal to fly as far as possible from any airport
    - Let the farthest reachable airport from V be idx[V]
- Next, notice that if we start flying from airport 0 no matter what, the result we get is at most 1 more than the optimal solution
- Consider the airports such that when we start on them, the result we get is equal to the optimal solution
    - Notice how if V is such an airport, so is idx[V]
- Next, notice that if we start on an arbitrary airport and keep flying to idx[V], then we will eventually land up on an "optimal" airport
    - By the pigeonhole principle, we only need to fly at most N times
- So just fly from airport 0 to idx[V] N times and we will land up on an "optimal" airport
- Then we can just simulate the process and find the answer
- Complexity: O(NS)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int l[1000000], idx[1000000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, s;
    cin >> n >> s;
    FOR(i, 0, n) cin >> l[i];

    FOR(i, 0, s) {
        int p;
        cin >> p;
        if (*max_element(l, l + n) > p) {
            cout << "NIE\n";
            continue;
        }

        int dist = 0;
        idx[0] = 0;
        while (dist + l[idx[0]] <= p) {
            dist += l[idx[0]++];
            if (idx[0] == n) idx[0] = 0;
        }
        FOR(j, 1, n) {
            dist -= l[j - 1];
            idx[j] = idx[j - 1];
            while (dist + l[idx[j]] <= p) {
                dist += l[idx[j]++];
                if (idx[j] == n) idx[j] = 0;
            }
        }

        int curr = 0, ans = 0, loop_cnt = 0;
        FOR(j, 0, n) curr = idx[curr];
        for (int j = curr; loop_cnt + (j >= curr) < 2; ans++) {
            if (idx[j] <= j) loop_cnt++;
            j = idx[j];
        }
        cout << ans << '\n';
    }
    return 0;
}