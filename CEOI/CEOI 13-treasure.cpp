/*
CEOI 2013 Treasure
- 2D prefix sums and PIE
    - We always try to query the largest possible rectangle
*/

#include <bits/stdc++.h>
using namespace std;

int query(int x1, int y1, int x2, int y2) {
    cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
    int ans;
    cin >> ans;
    return ans;
}

int pref[101][101];

int main() {
    int N;
    cin >> N;
    for (int i = N; i; i--) for (int j = N; j; j--) {
        if (i > N / 2) {
            if (j > N / 2) pref[i][j] = query(1, 1, i, j);
            else pref[i][j] = pref[i][N] - query(1, j + 1, i, N);
        } else {
            if (j > N / 2) pref[i][j] = pref[N][j] - query(i + 1, 1, N, j);
            else pref[i][j] = pref[i][N] + pref[N][j] - pref[N][N] + query(i + 1, j + 1, N, N);
        }
    }
    for (int i = N; i; i--) for (int j = N; j; j--) {
        pref[i][j] -= pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
    }
    cout << "END" << endl;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) cout << pref[i][j];
        cout << endl;
    }
    return 0;
}