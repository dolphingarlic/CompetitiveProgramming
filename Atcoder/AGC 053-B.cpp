#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;

ll a[400001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    ll ans = 0;
    for (int i = 1; i <= 2 * n; i++) {
        cin >> a[i];
        ans += a[i];
    }
    priority_queue<ll> pq;
    for (int i = 1; i <= n; i++) {
        pq.push(-a[n - i + 1]);
        pq.push(-a[n + i]);
        ans += pq.top();
        pq.pop();
    }
    cout << ans;
}
