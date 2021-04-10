#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void box(int dx, int dy) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            cout << dx + 11 * i << ' ' << dy + j << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << "1000\n";
    for (int i = 0; i < 10; i++)
        box(120 * i + 1, 120 * i + 1);
    return 0;
}
