/*
Baltic 2009 Triangulation
- Lemma: All triangulations of polygons have at least one "ear"
         i.e. a triangle with 2 edges of the polygon
- We can repeatedly "collapse" ears into single edges and in each
  triangle, store the number of triangles of each colour
  "collapesed" into it previously
    - We use small-to-large merging to merge hashmaps efficiently
- We can cut off an ear if the triangles collapsed into it are all
  those of their respective colours
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int on_edge[100000], good_cnt[100000];
unordered_map<int, int> tot, collapsed[100000];
map<pair<int, int>, int> has;
vector<int> adj[100000], stck;
bool visited[100000];

void merge(int A, int B) { // Merge A's info into B
    if (collapsed[A].size() > collapsed[B].size())
        swap(collapsed[A], collapsed[B]), swap(good_cnt[A], good_cnt[B]);
    for (pair<int, int> i : collapsed[A]) {
        collapsed[B][i.first] += i.second;
        if (collapsed[B][i.first] == tot[i.first]) good_cnt[B]++;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 2; i < n; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        tot[d]++, collapsed[i][d]++;
        // Each diagonal has two incident triangles
        if (has.count({a, b})) adj[i].push_back(has[{a, b}]), adj[has[{a, b}]].push_back(i);
        else has[{a, b}] = has[{b, a}] = i;
        if (has.count({a, c})) adj[i].push_back(has[{a, c}]), adj[has[{a, c}]].push_back(i);
        else has[{a, c}] = has[{c, a}] = i;
        if (has.count({b, c})) adj[i].push_back(has[{b, c}]), adj[has[{b, c}]].push_back(i);
        else has[{b, c}] = has[{c, b}] = i;
    }
    // Check which triangles are good or ears
    for (int i = 2; i < n; i++) {
        good_cnt[i] = tot[collapsed[i].begin()->first] == 1;
        on_edge[i] = 3 - adj[i].size();
        if (on_edge[i] == 2) stck.push_back(i);
    }
    int ans = 0;
    for (int i = 3; i < n; i++) {
        int curr = stck.back(); stck.pop_back();
        visited[curr] = true;
        ans += good_cnt[curr] == collapsed[curr].size();
        for (int j : adj[curr]) if (!visited[j]) {
            merge(curr, j);
            on_edge[j]++;
            if (on_edge[j] == 2) stck.push_back(j);
        }
    }
    cout << ans;
    return 0;
}
