#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int cnt[1000001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, ans = 0;
    cin >> n;
    while (n--) {
        int a;
        cin >> a;
        if (cnt[a]) cnt[a]--;
        else ans++;
        cnt[a - 1]++;
    }
    cout << ans;
    return 0;
}