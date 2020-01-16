/*
COCI 2017 Sirni
- Basically we want to find the minimum spanning tree of a complete graph
  where the edge weight between X and Y (where X > Y) is A[X] % A[Y]
- We want to limit the number of edges
- WLOG assume all numbers are distinct
- To do this, we take an approach similar to the sieve of Erastosthenes
  (or however you spell it idk)
    - For each number, consider the multiples of it not greater than the largest A[i]
        - Let this A[i] be MX
    - For each such multiple, only add the edge between the number and the smallest
      number greater than that multiple in the list
        - Think of the multiples as bucket boundaries and so this works intuitively
    - By harmonic sums, the number of edges is now O(MX log MX)
- Now we can sort the edges and run Kruskal as usual
    - However, since MX is very big and the edge weights are at most MX, we can
      use counting sort to sort the edge list in O(MX log MX)
- Complexity: O(MX log MX)
*/

#include <bits/stdc++.h>
using namespace std;

int a[100001];
vector<pair<int, int>> edges[10000001];

int cmp[100001];
int find(int A) {
    while (A != cmp[A]) cmp[A] = cmp[cmp[A]], A = cmp[A];
    return A;
}
void onion(int A, int B) { cmp[find(A)] = cmp[find(B)]; }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    set<int> s;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        s.insert(x);
    }
    n = 0;
    for (int i : s) {
        cmp[n] = n;
        a[n++] = i;
    }

    for (int i = 0; i < n; i++) {
        if (i != n - 1) edges[a[i + 1] % a[i]].push_back({i, i + 1});
        int lb = i + 1;
        for (int j = 2 * a[i]; j <= a[n - 1]; j += a[i]) {
            while (a[lb] < j) lb++;
            edges[a[lb] % a[i]].push_back({i, lb});
        }
    }
    
    long long ans = 0;
    for (int i = 0; i < a[n - 1]; i++) {
        for (pair<int, int> j : edges[i]) {
            if (find(j.first) != find(j.second)) {
                ans += i;
                onion(j.first, j.second);
            }
        }
    }
    cout << ans;
    return 0;
}
