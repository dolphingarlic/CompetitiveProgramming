#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n;
char a[1000][1000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ifstream cin("ssdj.in");
    ofstream cout("ssdj.out");

    cin >> n;
    FOR(i, 0, n) FOR(j, 0, n) cin >> a[n - 1 - i][j];
    
    int ans = 0;
    for (char c = 'z'; c >= 'a'; c--) {
        FOR(i, 0, n) {
            FOR(j, 0, n) {
                if (a[i][j] >= c) horiz[i][j] = j;
                else horiz[i][j]
            }
        }
    }
    return 0;
}