#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int a[50], b[50], c[50];
vector<pair<int, int>> moves;
// {1, x} = Vertical
// {2, x} = Horizontal

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    FOR(i, 0, n) {
        cin >> a[i];
        b[i % k] = (b[i % k] + a[i]) % k;
    }

    // Checks if possible
    FOR(i, 1, n % k) if (b[i] != b[i - 1]) return cout << -1, 0;
    FOR(i, n % k + 1, k) if (b[i] != b[i - 1]) return cout << -1, 0;

    // Makes heights non-decreasing from left to right
    FOR(i, 1, n) {
        while (a[i] < a[i - 1]) {
            moves.push_back({1, i});
            a[i] += k;
        }
    }
    FOR(i, 0, n) c[i] = a[i];

    // Places horizontal blocks to make rows k-1 to n-1 equal
    FOR(i, 0, a[n - 1]) {
        int pos = upper_bound(a, a + n, i) - a - 1;
        while (pos >= k - 1) {
            FOR(j, pos - k + 1, pos + 1) c[j]++;
            moves.push_back({2, pos - k + 1});
            pos -= k;
        }
    }

    // Places vertical blocks to make rows k-1 to n-1 equal to 0
    FOR(i, 0, k - 1) {
        while (c[i] < c[n - 1]) {
            moves.push_back({1, i});
            c[i] += k;
        }
    }

    // Places vertical blocks to make rows n%k to k-2 equal to 0
    int mx = *max_element(c + n % k, c + k - 1);
    FOR(i, n % k, k - 1) {
        while (c[i] != mx) {
            moves.push_back({1, i});
            c[i] += k;
        }
    }

    // Places vertical and horizontal blocks to clear the board
    mx = *max_element(c, c + n % k);
    FOR(i, 0, n % k) {
        while (c[i] != mx) {
            moves.push_back({1, i});
            c[i] += k;
        }
    }
    FOR(i, 0, c[0] - c[n % k]) {
        for (int j = n % k; j + k <= n; j += k) {
            moves.push_back({2, j});
        }
    }


    cout << moves.size() << '\n';
    for (pair<int, int> i : moves) cout << i.first << ' ' << i.second + 1 << '\n';
    return 0;
}