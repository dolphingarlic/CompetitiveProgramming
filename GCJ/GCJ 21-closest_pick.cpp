#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    for (int test = 1; test <= t; test++) {
        cout << "Case #" << test << ": ";
        int n, k;
        cin >> n >> k;
        set<int> s;
        s.insert(0);
        s.insert(k + 1);
        for (int i = 1; i <= n; i++) {
            int p;
            cin >> p;
            s.insert(p);
        }
        int ans = 0;
        // Case 1: A single interval
        for (auto i = next(s.begin()); i != s.end(); i++) {
            ans = max(ans, *i - *prev(i) - 1);
        }
        // Case 2 - Two intervals
        s.erase(0); s.erase(k + 1);
        vector<int> gaps;
        gaps.push_back(*s.begin() - 1); gaps.push_back(k - *s.rbegin());
        for (auto i = next(s.begin()); i != s.end(); i++) {
            gaps.push_back((*i - *prev(i)) / 2);
        }
        sort(gaps.begin(), gaps.end(), greater<int>());
        ans = max(ans, gaps[0] + gaps[1]);

        cout << fixed << setprecision(6) << double(ans) / k << '\n';
    }
    return 0;
}
