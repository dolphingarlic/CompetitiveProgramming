#include <iostream>
#include <bitset>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, bad = 0;
    cin >> n;
    bitset<1024> broken, tune;
    for (int i = 0; i < n; i++) {
        int b;
        cin >> b;
        broken[b] = true;
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int a;
        cin >> a;
        if (broken[a]) bad++;
        tune[a] = true;
    }
    cout << bad << '\n';
    for (int i = 0; i < 1024; i++) {
        if ((tune << i).count() == tune.count() && ((tune << i) & broken).count() == 0)
            return cout << i, 0;
        if ((tune >> i).count() == tune.count() && ((tune >> i) & broken).count() == 0)
            return cout << -i, 0;
    }
    cout << 'X';
    return 0;
}
