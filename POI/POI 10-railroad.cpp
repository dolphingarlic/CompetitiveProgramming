#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int to[100001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    vector<int> a = {INT_MAX - 1}, b = {INT_MAX};
    int n, nxt = 1;
    cin >> n;
    FOR(i, 0, n) {
        int x;
        cin >> x;
        if (b.back() > a.back()) {
            if (x < a.back()) {
                a.push_back(x);
                to[i] = 1;
            } else if (x < b.back()) {
                b.push_back(x);
                to[i] = 2;
            } else return cout << "NIE", 0;
        } else {
            if (x < b.back()) {
                b.push_back(x);
                to[i] = 2;
            } else if (x < a.back()) {
                a.push_back(x);
                to[i] = 1;
            } else return cout << "NIE", 0;
        }

        while (a.back() == nxt || b.back() == nxt) {
            if (a.back() == nxt) {
                a.pop_back();
                nxt++;
            }
            if (b.back() == nxt) {
                b.pop_back();
                nxt++;
            }
        }
    }

    cout << "TAK\n";
    FOR(i, 0, n) cout << to[i] << ' ';
    return 0;
}