#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    ordered_set rem;
    for (int i = 0; i < n; i++) rem.insert(i);
    for (int i = 0, curr = 0; i < n; i++) {
        curr = (curr + k) % rem.size();
        auto it = rem.find_by_order(curr);
        cout << *it + 1 << ' ';
        rem.erase(it);
    }
    return 0;
}