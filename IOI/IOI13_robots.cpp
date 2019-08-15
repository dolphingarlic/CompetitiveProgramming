#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for(int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int a, b, t, x[50000], y[50000];
pair<int, pair<int, int>> by_weight[1000000], by_size[1000000];
bool visited[1000000];

bool check(int s) {
    fill(visited, visited + t, false);
    
    int cnt = 0;

    priority_queue<pair<int, int>> light_enough_toys;
    int ptr = 0;
    FOR(i, 0, a) {
        while (ptr < t && by_weight[ptr].first < x[i]) {
            light_enough_toys.push(by_weight[ptr].second);
            ptr++;
        }

        for (int j = 0; j < s && !light_enough_toys.empty(); j++) {
            visited[light_enough_toys.top().second] = true;
            cnt++;
            light_enough_toys.pop();
        }
    }

    priority_queue<pair<int, int>> small_enough_toys;
    ptr = 0;
    FOR(i, 0, b) {
        while (ptr < t && by_size[ptr].first < y[i]) {
            if (!visited[by_size[ptr].second.second]) small_enough_toys.push(by_size[ptr].second);
            ptr++;
        }
        
        for (int j = 0; j < s && !small_enough_toys.empty(); j++) {
            visited[small_enough_toys.top().second] = true;
            cnt++;
            small_enough_toys.pop();
        }
    }

    return (cnt == t);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> a >> b >> t;

    FOR(i, 0, a) cin >> x[i];
    FOR(i, 0, b) cin >> y[i];
    sort(x, x + a), sort(y, y + b);

    FOR(i, 0, t) {
        int n, m;
        cin >> n >> m;
        if (n >= x[a - 1] && m >= y[b - 1]) return cout << "-1\n", 0;
        by_size[i] = {m, {n, i}};
        by_weight[i] = {n, {m, i}};
    }
    sort(by_size, by_size + t), sort(by_weight, by_weight + t);

    // Binary search for answer
    int l = 1, r = t;
    while (l != r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << l << '\n';
    return 0;
}