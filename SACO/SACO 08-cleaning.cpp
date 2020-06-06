/*
SACO 2008 Spring Cleaning
- Sort by height and use DSU to find the number of "islands" at each height
- Complexity: O(N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

vector<int> has_height[1000001];
int cmp[750002], cnt = 0, ans = 0;
bool visited[750002];

int find(int A) {
    while (A != cmp[A]) cmp[A] = cmp[cmp[A]], A = cmp[A];
    return A;
}

void onion(int A, int B) {
    cmp[find(A)] = cmp[find(B)];
    cnt--;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 1, n + 1) {
        int h;
        cin >> h;
        has_height[h].push_back(i);
    }

    iota(cmp + 1, cmp + n + 1, 1);
    for (int i = 1000000; i; i--) {
        cnt += has_height[i].size();
        for (int j : has_height[i]) {
            visited[j] = true;
            if (visited[j - 1]) onion(j - 1, j);
            if (visited[j + 1]) onion(j + 1, j);
        }
        ans += cnt;
        if (ans >= 1000000) ans -= 1000000;
    }
    cout << ans;
    return 0;
}