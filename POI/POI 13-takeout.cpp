#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

string s;
int c = 0;
vector<int> space = {0}, available;
vector<vector<int>> sol;

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k >> s;

    FOR(i, 0, n) {
        available.push_back(i);
        if (s[i] == 'c') {
            space.push_back(0);
            c++;
        } else
            space[c]++;

        if (c && space[c] + space[c - 1] >= k) {
            sol.push_back({});
            FOR(j, 0, k + 1) {
                sol.back().push_back(available.back());
                available.pop_back();
            }

            int diff = space[c--];
            space.pop_back();
            space[c] -= (k - diff);
        }
    }

    reverse(sol.begin(), sol.end());

    for (vector<int> i : sol) {
        reverse(i.begin(), i.end());
        for (int j : i) cout << j + 1 << ' ';
        cout << '\n';
    }
    return 0;
}