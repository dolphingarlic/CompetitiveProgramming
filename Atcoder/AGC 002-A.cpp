#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int a, b;
    cin >> a >> b;
    if (a <= 0 && b >= 0) return cout << "Zero", 0;
    cout << ((min(b, 0) - min(a, -1)) % 2 ? "Positive" : "Negative");
    return 0;
}
