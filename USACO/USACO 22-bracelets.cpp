#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t, last_appeared[51], parent[51];
    cin >> t;
    while (t--) {
        int n, m;
        bool good = true;
        vector<int> glob_order;
        cin >> n >> m;
        for (int i = 0; i <= n; i++) last_appeared[i] = parent[i] = -1;

        while (m--) {
            int k, curr = 0;
            cin >> k;
            stack<int> stck;
            vector<int> curr_order;

            while (k--) {
                int c;
                cin >> c;
                if (!good) continue;
                if (last_appeared[c] == m && stck.top() == c) {
                    stck.pop();
                    curr = parent[curr];
                } else {
                    if ((~last_appeared[c] && last_appeared[c] != m + 1) ||
                        last_appeared[c] == m ||
                        (~last_appeared[c] && parent[c] != curr)) {
                        // Conditions 1, 2, and 3
                        good = false;
                        continue;
                    }
                    // Condition 4 part A
                    curr_order.push_back(c);

                    parent[c] = curr;
                    last_appeared[c] = m;
                    stck.push(c);
                    curr = c;
                }
            }
            // Condition 4 part B
            if (!good) continue;
            int ptr = 0;
            for (int i : curr_order) {
                while (ptr != glob_order.size() &&
                       !count(curr_order.begin(), curr_order.end(), glob_order[ptr]))
                    ptr++;
                if (!count(glob_order.begin(), glob_order.end(), i))
                    glob_order.insert(glob_order.begin() + ptr, i);
                else if (ptr == glob_order.size() || glob_order[ptr] != i) {
                    good = false;
                    break;
                }
                ptr++;
            }
        }
        cout << (good ? "YES\n" : "NO\n");
    }
    return 0;
}
