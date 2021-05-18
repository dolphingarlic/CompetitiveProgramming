/*
InfO(1) Cup 2019 Cat
- Since the swaps are symmetric, we can "fold" the permutation in half
- Notice that if we do this, then sorting is possible iff each pair is
  of the form (x, N + 1 - x)
- After doing this check, we can sort it in N - (no. of cycles) swaps
- However, some pairs may be "inverted" i.e. x > N / 2
- To fix this, we can fix two inverted pairs at a time by swapping
  their elements
- This means that sorting is also only possible if the number of inverted
  pairs is even
- Each cycle with an odd number of inverted pairs also contributes 1
  additional swap
- Complexity: O(N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, a[200001];
bool inverted[200001], visited[200001];
vector<pair<int, int>> moves;

void swp(int x, int y) {
    moves.push_back({x, y});
    swap(a[x], a[y]);
    swap(a[n - x + 1], a[n - y + 1]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        int inv_cnt = 0;
        bool possible = true;
        for (int i = 1; i <= n / 2; i++) {
            possible &= a[i] + a[n - i + 1] == n + 1;
            inverted[i] = a[i] > a[n - i + 1];
            inv_cnt += inverted[i];
            visited[i] = false;
        }
        if ((inv_cnt & 1) || !possible) {
            cout << "-1\n";
            continue;
        }

        moves.clear();
        vector<int> unresolved;
        int opt = n / 2;
        for (int i = 1; i <= n / 2; i++) if (!visited[i]) {
            opt--;
            int curr = i, prv_inv = 0;
            while (!visited[curr]) {
                visited[curr] = true;
                if (inverted[curr]) {
                    if (prv_inv) {
                        swp(curr, n - prv_inv + 1);
                        curr = prv_inv;
                        prv_inv = 0;
                    } else prv_inv = curr;
                }
                curr = min(a[curr], a[n - curr + 1]);
            }
            if (prv_inv) unresolved.push_back(prv_inv);
        }
        for (int i = 0; i < unresolved.size(); i += 2) {
            opt += 2;
            swp(unresolved[i], n - unresolved[i + 1] + 1);
        }

        for (int i = 1; i <= n / 2; i++) {
            int curr = i;
            while (a[curr] != i) swp(curr, a[curr]);
        }
        
        cout << opt << ' ' << moves.size() << '\n';
        for (pair<int, int> i : moves)
            cout << i.first << ' ' << i.second << '\n';
    }
    return 0;
}
