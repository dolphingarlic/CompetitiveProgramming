#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int a[1000000];
vector<int> silence;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, c;
    cin >> n >> m >> c;

    multiset<int> soft, loud;
    FOR(i, 0, m) {
        cin >> a[i];
        soft.insert(a[i]);
        loud.insert(-a[i]);
    }
    if (-(*soft.begin() + *loud.begin()) <= c) silence.push_back(1);
    FOR(i, m, n) {
        cin >> a[i];
        soft.erase(soft.find(a[i - m]));
        loud.erase(loud.find(-a[i - m]));
        soft.insert(a[i]);
        loud.insert(-a[i]);
        if (-(*soft.begin() + *loud.begin()) <= c) silence.push_back(i - m + 2);
    }

    if (silence.size()) for (int i : silence) cout << i << '\n';
    else cout << "NONE\n";
    return 0;
}