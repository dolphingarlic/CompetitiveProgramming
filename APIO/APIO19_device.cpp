#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
// Observation: pairs are periodic, period = B * (A / gcd(A, B + 1))
// We can thus "line sweep" i.e. keep a vector of events and +1 for add,
// -1 for remove and count as long as positive
 
ll gcd(ll a, ll b) { return (b == 0 ? a : gcd(b, a % b)); }
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, a, b;
    cin >> n >> a >> b;
    ll period = b * (a / gcd(a, b + 1));
    vector<pair<ll, int>> events;
    FOR(i, 0, n) {
        ll x, y;
        cin >> x >> y;
        x += period - 1;
        y += period - 1;
        if (y - x >= period) {
            return cout << period << '\n', 0;
        }
        if (x % period > y % period) {
            events.push_back(make_pair(1, 0));
            events.push_back(make_pair(y % period + 1, 1));
            events.push_back(make_pair(x % period + 1, 0));
            events.push_back(make_pair(period, 1));
        } else {
            events.push_back(make_pair(x % period + 1, 0));
            events.push_back(make_pair(y % period + 1, 1));
        }
    }
    sort(events.begin(), events.end());
    ll cnt = 0, leftmost = -1, ans = 0;
    for (auto& i : events) {
        if (!i.second) {
            cnt++;
            if (leftmost == -1) leftmost = i.first;
        } else {
            cnt--;
            if (cnt == 0) {
                ans += (i.first - leftmost + 1);
                leftmost = -1;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}