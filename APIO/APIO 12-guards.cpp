#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int pref[100001], diff[100002];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    vector<pair<int, int>> yes;
    cin >> n >> k >> m;
    FOR(i, 0, m) {
        int a, b, x;
        cin >> a >> b >> x;
        if (x) yes.push_back({a, b});
        else diff[a]++, diff[b + 1]--;
    }

    int active = 0;
    FOR(i, 1, n + 1) {
        active += diff[i];
        pref[i] = pref[i - 1] + (active == 0);
    }

    if (pref[n] == k) {
        FOR(i, 1, n + 1) if (pref[i] - pref[i - 1]) cout << i << '\n';
    } else {
        set<int> confirmed;
        for (pair<int, int> i : yes) {
            if (pref[i.second] - pref[i.first - 1] == 1) {
                int l = i.first, r = i.second;
                while (l != r) {
                    int mid = (l + r) / 2;
                    if (pref[mid] - pref[i.first - 1]) r = mid;
                    else l = mid + 1;
                }
                confirmed.insert(l);
            } 
        }
        if (confirmed.size()) {
            for (int i : confirmed) cout << i << '\n';
        } else cout << "-1\n";
    }
    return 0;
}
