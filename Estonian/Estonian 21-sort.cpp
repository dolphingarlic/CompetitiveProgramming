#include <iostream>
#include <vector>
#include <set>
#include <numeric>
#include <cassert>
using namespace std;

int semi[101];
set<int> known;

bool query_less(int l, int r) {
    cout << "? " << l << ' ' << r << endl;
    char c;
    cin >> c;
    return c == '<';
}

int quickselect(int pos, int l, int r) {
    if (l == r) return semi[l];
    
    int pivot = rand() % (r - l + 1) + l;
    vector<int> lt, gt;
    for (int i = l; i <= r; i++) {
        if (i == pivot) continue;
        if (query_less(semi[pivot], semi[i])) gt.push_back(semi[i]);
        else lt.push_back(semi[i]);
    }

    known.insert(l + lt.size());
    semi[l + lt.size()] = semi[pivot];
    for (int i = 0; i < lt.size(); i++)
        semi[l + i] = lt[i];
    for (int i = 0; i < gt.size(); i++)
        semi[r - i] = gt[i];

    if (lt.size() == pos - 1) return semi[l + lt.size()];
    if (lt.size() >= pos) return quickselect(pos, l, l + lt.size() - 1);
    return quickselect(pos - lt.size() - 1, r - gt.size() + 1, r);
}

int main() {
    int n, q;
    cin >> n >> q;
    if (n > 20) srand(998244383);
    known.insert(0);
    known.insert(n + 1);
    iota(semi + 1, semi + n + 1, 1);
    while (q--) {
        int x;
        cin >> x;
        if (known.count(x)) cout << "! " << semi[x] << endl;
        else {
            auto ub = known.upper_bound(x);
            int ans = quickselect(x - *prev(ub), *prev(ub) + 1, *ub - 1);
            cout << "! " << ans << endl;
        }
    }
    return 0;
}
