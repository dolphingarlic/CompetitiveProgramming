#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;
 
set<string> strings;
string s;
bool visited[8];
int n;
 
void dfs(int level, int indx, string curr) {
    visited[indx] = true;
    if (level == n) {
        strings.insert(curr + s[indx]);
    } else {
        FOR(i, 0, n) {
            if (!visited[i]) dfs(level + 1, i, curr + s[indx]);
        }
    }
    visited[indx] = false;
}
 
int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    cin >> s;
    n = s.size();
 
    FOR(i, 0, n) {
        dfs(1, i, "");
    }
 
    cout << strings.size() << '\n';
    for (string i : strings) cout << i << '\n';
    return 0;
}