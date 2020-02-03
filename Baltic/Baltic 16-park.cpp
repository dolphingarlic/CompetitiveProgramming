#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
#define x first
#define y second
typedef long long ll;
using namespace std;

ll cmp[2004];
ll find(ll a) {
    while (cmp[a] != a) cmp[a] = cmp[cmp[a]], a = cmp[a];
    return a;
}
void onion(ll a, ll b) { cmp[find(a)] = cmp[find(b)]; }

pair<pair<ll, ll>, ll> tree[2000], visitors[100000];
priority_queue<pair<double, pair<ll, ll>>> pq;
string ans[100000];

ll dist(pair<ll, ll> a, pair<ll, ll> b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, m, w, h;
    cin >> n >> m >> w >> h;
    FOR(i, 0, n + 4) cmp[i] = i;
    FOR(i, 0, n) {
        cin >> tree[i].x.x >> tree[i].x.y >> tree[i].y;
        FOR(j, 0, i) {
            pq.push({-(sqrt(dist(tree[i].x, tree[j].x)) - tree[i].y - tree[j].y), {i, j}});
        }
        pq.push({-(tree[i].x.x - tree[i].y), {i, n}});
        pq.push({-(tree[i].x.y - tree[i].y), {i, n + 1}});
        pq.push({-(w - tree[i].x.x - tree[i].y), {i, n + 2}});
        pq.push({-(h - tree[i].x.y - tree[i].y), {i, n + 3}});
    }
    FOR(i, 0, m) {
        cin >> visitors[i].x.x >> visitors[i].x.y;
        visitors[i].y = i;
    }
    sort(visitors, visitors + m);

    // n: East wall
    // n+1: South wall
    // n+2: West wall
    // n+3: North wall
    FOR(i, 0, m) {
        while (-pq.top().x < 2 * visitors[i].x.x) {
            onion(pq.top().y.x, pq.top().y.y);
            pq.pop();
        }

        if (visitors[i].x.y == 1) {
            ans[visitors[i].y] += "1";
            if (find(n) != find(n + 1) && find(n + 1) != find(n + 3) && find(n + 1) != find(n + 2)) ans[visitors[i].y] += "2";
            if (find(n) != find(n + 2) && find(n) != find(n + 1) && find(n + 1) != find(n + 3) && find(n + 2) != find(n + 3)) ans[visitors[i].y] += "3";
            if (find(n) != find(n + 1) && find(n) != find(n + 2) && find(n) != find(n + 3)) ans[visitors[i].y] += "4";
        } else if (visitors[i].x.y == 2) {
            if (find(n) != find(n + 1) && find(n + 1) != find(n + 3) && find(n + 1) != find(n + 2)) ans[visitors[i].y] += "1";
            ans[visitors[i].y] += "2";
            if (find(n) != find(n + 2) && find(n + 1) != find(n + 2) && find(n + 3) != find(n + 2)) ans[visitors[i].y] += "3";
            if (find(n) != find(n + 2) && find(n + 1) != find(n + 3) && find(n + 1) != find(n + 2) && find(n) != find(n + 3)) ans[visitors[i].y] += "4";
        } else if (visitors[i].x.y == 3) {
            if (find(n) != find(n + 2) && find(n) != find(n + 1) && find(n + 1) != find(n + 3) && find(n + 2) != find(n + 3)) ans[visitors[i].y] += "1";
            if (find(n) != find(n + 2) && find(n + 1) != find(n + 2) && find(n + 3) != find(n + 2)) ans[visitors[i].y] += "2";
            ans[visitors[i].y] += "3";
            if (find(n) != find(n + 3) && find(n + 1) != find(n + 3) && find(n + 2) != find(n + 3)) ans[visitors[i].y] += "4";
        } else {
            if (find(n) != find(n + 1) && find(n) != find(n + 2) && find(n) != find(n + 3)) ans[visitors[i].y] += "1";
            if (find(n) != find(n + 2) && find(n + 1) != find(n + 3) && find(n + 1) != find(n + 2) && find(n) != find(n + 3)) ans[visitors[i].y] += "2";
            if (find(n) != find(n + 3) && find(n + 1) != find(n + 3) && find(n + 2) != find(n + 3)) ans[visitors[i].y] += "3";
            ans[visitors[i].y] += "4";
        }
    }

    FOR(i, 0, m) cout << ans[i] << '\n';
    return 0;
}