#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for(int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
pair<int, int> a[100001];
int b[100001];
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    FOR(i, 0, n) cin >> a[i].second >> a[i].first;
    FOR(i, 0, m) cin >> b[i];
    sort(a, a + n, greater<pair<int, int>>());
    sort(b, b + m, greater<int>());
 
    int ptr1 = 0, ptr2 = 0, cnt = 0;
    while (ptr1 < n && ptr2 < m) {
        if (a[ptr1].second <= b[ptr2]) {
            cnt++;
            ptr2++;
        }
        ptr1++;
    }
    cout << cnt << '\n';
    return 0;
}