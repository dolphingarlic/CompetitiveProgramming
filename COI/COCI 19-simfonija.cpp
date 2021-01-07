#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int a[100000];
map<int, int> cnt;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) {
        int b;
        cin >> b;
        cnt[a[i] - b]++;
    }
    int mx = 0;
    for (pair<int, int> i : cnt) mx = max(mx, i.second);
    cout << min(n, mx + k);
    return 0;
}