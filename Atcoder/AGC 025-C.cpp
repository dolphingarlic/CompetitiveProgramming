#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
using namespace std;
typedef long long ll;

int l[100000], r[100000];
bool visited[100000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> l[i] >> r[i];
    ll ans = 0;
    for (int _ : {0, 1}) {
        priority_queue<pair<int, int>> lb, ub;
        for (int i = 0; i < n; i++) {
            visited[i] = false;
            lb.push({l[i], i});
            ub.push({-r[i], i});
            swap(l[i], r[i]);
            l[i] *= -1, r[i] *= -1;
        }
        ll cand = 0;
        int curr = 0;
        for (bool incr = true;; incr = !incr) {
            if (incr) {
                while (lb.size() && visited[lb.top().second]) lb.pop();
                if (!lb.size()) break;
                cand += max(0, lb.top().first - curr);
                curr = max(curr, lb.top().first);
                visited[lb.top().second] = true;
                lb.pop();
            } else {
                while (ub.size() && visited[ub.top().second]) ub.pop();
                if (!ub.size()) break;
                cand += max(0, ub.top().first + curr);
                curr = min(curr, -ub.top().first);
                visited[ub.top().second] = true;
                ub.pop();
            }
        }
        ans = max(ans, cand + abs(curr));
    }
    cout << ans;
    return 0;
}
