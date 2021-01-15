#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
vector<int> lis;
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, n) {
        int x;
        cin >> x;
        int pos = lower_bound(lis.begin(), lis.end(), x) - lis.begin();
        if (pos == lis.size()) lis.push_back(x);
        else lis[pos] = x;
    }
    cout << lis.size();
    return 0;
}