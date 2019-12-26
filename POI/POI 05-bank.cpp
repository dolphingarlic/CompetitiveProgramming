/*
POI 2005 Bank
- We can view this problem as a graph
- A directed edge from A to B means that A contains B's key
- Notice that each node has exactly 1 edge incoming, so we can always completely
  visit a single component in 1 move
- To find the number of components we use DSU
- Note: constructing the graph gets MLE so just use DSU
- Complexity: O(N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int cmp[1000001], cnt;
int find(int A) {
    while (A != cmp[A]) cmp[A] = cmp[cmp[A]], A = cmp[A];
    return A;
}
void onion(int A, int B) {
    if (find(A) != find(B)) {
        cnt--;
        cmp[find(A)] = cmp[find(B)];
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    cnt = n;
    FOR(i, 1, n + 1) cmp[i] = i;
    FOR(i, 1, n + 1) {
        int x;
        cin >> x;
        onion(x, i);
    }
    cout << cnt;
    return 0;
}