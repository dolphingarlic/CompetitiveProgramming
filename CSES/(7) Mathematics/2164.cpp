#include <iostream>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int q;
    cin >> q;
    while (q--) {
        int n, k;
        cin >> n >> k;
        bool rem_even = false;
        int suffix = 0, iters = 0;
        while (n > 1 && k > (n + rem_even) / 2) {
            suffix += (int)rem_even << iters;
            iters++;
            int to_rem = (n + rem_even) / 2;
            if (n & 1) rem_even = !rem_even;
            n -= to_rem;
            k -= to_rem;
        }
        if (n == 1) cout << suffix << '\n';
        else cout << (k * 2 - rem_even << iters) + suffix << '\n';
    }
    return 0;
}
