/*
USACO 2019 Exercise
- Notice how if we consider the paths A->lca(A, B)->B, then the answer is the number of pairs
  of paths that overlap
- We can split each path into 2 separate paths, count how many of those overlap, and subtract the
  number of pairs of paths that have the same lca and 2 outgoing edges
- The case where the tree is a line is a classical problem, so we just adapt that to work with a general tree
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
using namespace std;
#define MAXN 200000

int N, Q;
vector<int> edges[MAXN];
int x[MAXN], y[MAXN], anc[MAXN];
int p[MAXN][20];
int d[MAXN];

int numInters[MAXN];
int psInters[MAXN];
map<pair<int, int>, int> MP;

void dfs(int i, int par, int depth) {
    p[i][0] = par;
    d[i] = depth;
    for (int j = 0; j < edges[i].size(); j++)
        if (edges[i][j] != par) dfs(edges[i][j], i, depth + 1);
}

void dfsSum(int i, int ps) {
    psInters[i] = ps;
    for (int j = 0; j < edges[i].size(); j++)
        if (edges[i][j] != p[i][0])
            dfsSum(edges[i][j], ps + numInters[edges[i][j]]);
}

void precompute() {
    dfs(0, -1, 0);
    for (int j = 1; j < 20; j++)
        for (int i = 0; i < N; i++) {
            if (p[i][j - 1] == -1)
                p[i][j] = -1;
            else
                p[i][j] = p[p[i][j - 1]][j - 1];
        }
}

int lca(int a, int b) {
    for (int j = 19; j >= 0; j--)
        if (d[p[a][j]] >= d[b]) a = p[a][j];
    for (int j = 19; j >= 0; j--)
        if (d[p[b][j]] >= d[a]) b = p[b][j];
    for (int j = 19; j >= 0; j--)
        if (p[a][j] != p[b][j]) a = p[a][j], b = p[b][j];
    if (a == b) return a;
    return p[a][0];
}

int topEdge(int top, int bot) {
    if (top == bot) return -1;
    for (int j = 19; j >= 0; j--)
        if (d[p[bot][j]] > d[top]) bot = p[bot][j];
    return bot;
}

long long choose2(int m) { return (((long long)m) * (m - 1)) / 2; }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ifstream cin("exercise.in");
    ofstream cout("exercise.out");
    int M, a, b;
    cin >> N >> M;
    Q = M - (N - 1);
    for (int i = 0; i < N - 1; i++) {
        cin >> a >> b;
        a--, b--;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    precompute();
    long long ans = 0;
    for (int i = 0; i < Q; i++) {
        cin >> x[i] >> y[i];
        x[i]--, y[i]--;
        anc[i] = lca(x[i], y[i]);
        int topx = topEdge(anc[i], x[i]);
        if (topx != -1) {
            ans -= numInters[topx] + 1;
            numInters[topx]++;
        }
        int topy = topEdge(anc[i], y[i]);
        if (topy != -1) {
            ans -= numInters[topy] + 1;
            numInters[topy]++;
        }
        if (topx != -1 && topy != -1) {
            if (topx > topy) swap(topx, topy);
            ans -= MP[make_pair(topx, topy)];
            MP[make_pair(topx, topy)]++;
        }
    }
    dfsSum(0, 0);
    for (int i = 0; i < Q; i++)
        ans += psInters[x[i]] + psInters[y[i]] - 2 * psInters[anc[i]];
    cout << ans << '\n';
}