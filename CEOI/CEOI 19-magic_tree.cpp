#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> graph[101010];
pair<ll, ll> fruit[101010];
ll n, m, k, ans;

void merge(map<ll, ll> &X, map<ll, ll> &Y) {
    if (X.size() < Y.size()) swap(X, Y);
    for (pair<ll, ll> t : Y) X[t.first] += t.second;
}

void dfs(ll p, map<ll, ll> &X) {
    ll s, t, x, y;

    for (ll &t : graph[p]) {
        map<ll, ll> Y;
        dfs(t, Y);
        merge(X, Y);
    }

    if (fruit[p].second) {
        tie(x, y) = fruit[p];
        X[x] += y;

        auto it = next(X.find(x));
        for (s = 0; it != X.end(); it = next(X.find(x))) {
            s += it->second;
            t = it->first;
            X.erase(it);
            if (s > y) {
                X[t] = s - y;
                break;
            }
        }
    }
}

int main() {
    ll i, p, d, w;

    cin >> n >> m >> k;

    for (i = 2; i <= n; i++) {
        cin >> p;
        graph[p].push_back(i);
    }

    for (i = 1; i <= m; i++) {
        cin >> p >> d >> w;
        fruit[p] = pair<ll, ll>(d, w);
    }

    map<ll, ll> X;
    dfs(1, X);

    for (pair<ll, ll> t : X) {
        ans += t.second;
    }

    cout << ans;

    return 0;
}