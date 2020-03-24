#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> alt_sequences = {0, 0};

    int prev = 0, len = 0;
    FOR(i, 0, n) {
        int curr;
        cin >> curr;
        if (curr == prev) {
            alt_sequences.push_back(len);
            len = 0;
        }
        len++;
        prev = curr;
    }
    alt_sequences.push_back(len);

    int ans = 0;
    FOR(i, 0, alt_sequences.size() - 2)
    ans = max(ans,
              alt_sequences[i] + alt_sequences[i + 1] + alt_sequences[i + 2]);
    cout << ans << '\n';
    return 0;
}