#include <bits/stdc++.h>
using namespace std;

vector<int> freq[600001];
int pref[600001][20];

int main() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        freq[a].push_back(i);
        for (int j = 0; j < 20; j++) {
            pref[i][j] = pref[i - 1][j];
            if (a & (1 << j)) pref[i][j]++;
        }
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;
        int c = 0;
        for (int i = 0; i < 20; i++)
            if (pref[r][i] - pref[l][i] > (r - l) / 2) c += (1 << i);

        if (freq[c].size() &&
            upper_bound(freq[c].begin(), freq[c].end(), r) -
                    upper_bound(freq[c].begin(), freq[c].end(), l) >
                (r - l) / 2)
            cout << c << '\n';
        else
            cout << "0\n";
    }
    return 0;
}
