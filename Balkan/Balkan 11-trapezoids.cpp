/*
Balkan 2011 Trapezoid
- First, compress the coordinates since that doesn't change anything
- This is very similar to the problem of finding the maximum number of line segments that don't intersect,
  so we will probably use LIS
- In the problem with line segments, we sort them by top coordinate and find the LIS of the bottom coordinates
- Here, we do a similar thing
    - Sort by the top corners
    - When we get to a top left corner, find the LIS up to that point
    - Instead of updating the LIS immediately though, we wait until we get to the top right corner
    - This means that the tops of trapezoids that intersect are not counted
- When we find the LIS, instead of just comparing bottom coordinates, we compare the bottom right corners with the
  bottom left of the current trapezoid
    - And when we update the LIS, we update using the bottom left corner
- We can use a BIT to find the number of LIS's
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const int MOD = 30013;

struct Trapezoid {
    int x1, x2, y1, y2;
} traps[100001];

int n, top[200001], bottom[200001];

int g_len[200001], g_num[200001];
int l_len[200001], l_num[200001];
pair<int, int> events[200001];

void update(int pos, int len, int num) {
    for (; pos < 2 * n; pos += (pos & (-pos))) {
        if (g_len[pos] == len) {
            g_num[pos] = (g_num[pos] + num) % MOD;
        } else if (g_len[pos] < len) {
            g_len[pos] = len;
            g_num[pos] = num;
        }
    }
}

pair<int, int> query(int pos) {
    pair<int, int> ans;
    for (; pos; pos -= (pos & (-pos))) {
        if (g_len[pos] == ans.first)
            ans.second = (ans.second + g_num[pos]) % MOD;
        else if (g_len[pos] > ans.first)
            ans = {g_len[pos], g_num[pos]};
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    FOR(i, 1, n + 1) {
        cin >> traps[i].x1 >> traps[i].x2 >> traps[i].y1 >> traps[i].y2;
        top[2 * i - 1] = traps[i].x1, top[2 * i] = traps[i].x2;
        bottom[2 * i - 1] = traps[i].y1, bottom[2 * i] = traps[i].y2;
    }
    sort(top + 1, top + 2 * n + 1);
    sort(bottom + 1, bottom + 2 * n + 1);
    FOR(i, 1, n + 1) {
        traps[i].x1 = lower_bound(top + 1, top + 2 * n + 1, traps[i].x1) - top;
        traps[i].x2 = lower_bound(top + 1, top + 2 * n + 1, traps[i].x2) - top;
        traps[i].y1 = lower_bound(bottom + 1, bottom + 2 * n + 1, traps[i].y1) - bottom;
        traps[i].y2 = lower_bound(bottom + 1, bottom + 2 * n + 1, traps[i].y2) - bottom;
    }

    FOR(i, 1, n + 1) {
        events[2 * i - 1] = {traps[i].x1, i};
        events[2 * i] = {traps[i].x2, -i};
    }
    sort(events + 1, events + 2 * n + 1);

    int b_len = 0, b_num = 0;
    FOR(i, 1, 2 * n + 1) {
        if (events[i].second > 0) {
            pair<int, int> lis = query(traps[events[i].second].y1);
            if (!lis.first) lis.second = 1;
            lis.first++;
            l_len[events[i].second] = lis.first;
            l_num[events[i].second] = lis.second;
            if (lis.first > b_len) {
                b_len = lis.first;
                b_num = 0;
            }
            if (lis.first == b_len) b_num = (b_num + lis.second) % MOD;
        } else update(traps[-events[i].second].y2, l_len[-events[i].second], l_num[-events[i].second]);
    }

    cout << b_len << ' ' << b_num;
    return 0;
}