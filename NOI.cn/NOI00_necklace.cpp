#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
	  if (a % b == 0 && a % (2 * b) != 0) cout << 0;
    else cout << round(a / (2 * b));
    return 0;
}
