/*
CEOI 2021 Stones
- Basically, you choose stones and piles so that Branko
  must always take 1 stone, and there is either an even
  number of single-stone piles when he has to pick from
  a pile or there's at least one pile with >1 stone.
*/

#include <iostream>
#include <set>
using namespace std;

int a[501];

int main() {
    int n;
    cin >> n;
    set<int> ones, others;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == 1) ones.insert(i);
        else others.insert(i);
    }
    while (true) {
        int x;
        cin >> x;
        if (a[x] == 1) {
            ones.erase(x);
            cout << 1 << endl;
            if (ones.size() == 0 && others.size() == 0)
                return cout << -1 << endl, 0;
            cout << *ones.begin() << endl;
            ones.erase(ones.begin());
            cin >> x;
        } else {
            others.erase(x);
            if (others.size() == 0) {
                cout << a[x] << endl;
                if (ones.size() == 0)
                    return cout << -1 << endl, 0;
                cout << *ones.begin() << endl;
                ones.erase(ones.begin());
                cin >> x;
            } else {
                cout << a[x] - 1 << endl << x << endl;
                cin >> x;
            }
        }
    }
    return 0;
}
