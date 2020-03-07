#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

vector<ll> stck;
map<ll, bool> visited;
ll a, b;
bool found = false;

bool is_prime(ll n) {
    if (n < 2) return false;
    FOR(i, 2, sqrt(n) + 1) if (n % i == 0) return false;
    return true;
}

void dfs(ll node) {
    if (found) return;
    stck.push_back(node);
    visited[node] = true;

    if (node == b) {
        cout << stck.size() << '\n';
        for (ll i : stck) cout << i << ' ';
        found = true;
        return;
    }

    if (is_prime(node + 2) && !visited[node + 2]) dfs(node + 2);
    if (is_prime(node - 2)) {
        if (!visited[node - 2]) dfs(node - 2);
        if (!visited[2]) dfs(2);
    }
    if (is_prime(b - node)) dfs(b);
    if (is_prime(b - 2) && is_prime(b - node - 2)) dfs(b - 2);
    if (is_prime(b + 2) && is_prime(b - node + 2)) dfs(b + 2);
    stck.pop_back();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> a >> b;

    dfs(a);
    if (!found) cout << -1;
    return 0;
}