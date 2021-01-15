#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
 
ll dtot = 0, f[200001];
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        ll d;
        cin >> f[i] >> d;
        dtot += d;
    }
    sort(f, f + n);
    dtot -= f[0];
    for (int i = 1; i < n; i++) {
        f[i] += f[i - 1];
        dtot -= f[i];
    }
    cout << dtot;
    return 0;
}