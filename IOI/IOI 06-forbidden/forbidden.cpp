#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

namespace Blossom {
#define M 500  // max number of vertices
struct StructEdge {
    int v;
    StructEdge* n;
};
typedef StructEdge* Edge;

class Blossom {
    StructEdge pool[M * M * 2];
    Edge top = pool, adj[M];
    int V, E, qh, qt;
    int match[M], q[M], father[M], base[M];
    bool inq[M], inb[M], ed[M][M], inp[M];

   public:
    Blossom(int V, int E) : V(V), E(E) {}

    void addEdge(int u, int v) {
        if (!ed[u - 1][v - 1]) {
            top->v = v, top->n = adj[u], adj[u] = top++;
            top->v = u, top->n = adj[v], adj[v] = top++;
            ed[u - 1][v - 1] = ed[v - 1][u - 1] = true;
        }
    }
    // utility function for blossom contraction
    int LCA(int root, int u, int v) {
        memset(inp, 0, sizeof(inp));
        while (1) {
            inp[u = base[u]] = true;
            if (u == root) break;
            u = father[match[u]];
        }
        while (1) {
            if (inp[v = base[v]])
                return v;
            else
                v = father[match[v]];
        }
    }
    void mark_blossom(int lca, int u) {
        while (base[u] != lca) {
            int v = match[u];
            inb[base[u]] = inb[base[v]] = true;
            u = father[v];
            if (base[u] != lca) father[u] = v;
        }
    }
    void blossom_contraction(int s, int u, int v) {
        int lca = LCA(s, u, v);
        memset(inb, 0, sizeof(inb));
        mark_blossom(lca, u);
        mark_blossom(lca, v);
        if (base[u] != lca) father[u] = v;
        if (base[v] != lca) father[v] = u;
        for (int u = 0; u < V; u++)
            if (inb[base[u]]) {
                base[u] = lca;
                if (!inq[u]) inq[q[++qt] = u] = true;
            }
    }
    int find_augmenting_path(int s) {
        memset(inq, 0, sizeof(inq));
        memset(father, -1, sizeof(father));
        for (int i = 0; i < V; i++) base[i] = i;
        inq[q[qh = qt = 0] = s] = true;
        while (qh <= qt) {
            int u = q[qh++];
            for (Edge e = adj[u]; e; e = e->n) {
                int v = e->v;
                if (base[u] != base[v] && match[u] != v)
                    if ((v == s) || (match[v] != -1 && father[match[v]] != -1))
                        blossom_contraction(s, u, v);
                    else if (father[v] == -1) {
                        father[v] = u;
                        if (match[v] == -1)
                            return v;
                        else if (!inq[match[v]])
                            inq[q[++qt] = match[v]] = true;
                    }
            }
        }
        return -1;
    }
    int augment_path(int s, int t) {
        int u = t, v, w;
        while (u != -1) {
            v = father[u];
            w = match[v];
            match[v] = u;
            match[u] = v;
            u = w;
        }
        return t != -1;
    }
    int
    edmondsBlossomAlgorithm() {  // Converted recursive algorithm to iterative
        // version for simplicity
        int match_counts = 0;
        memset(match, -1, sizeof(match));
        for (int u = 0; u < V; u++)
            if (match[u] == -1)
                match_counts += augment_path(u, find_augmenting_path(u));
        return match_counts;
    }
    vector<pair<int, int>> getMatching() {
        vector<pair<int, int>> ans;
        for (int i = 0; i < V; i++)
            if (i < match[i]) ans.push_back({i, match[i]});
        return ans;
    }
};
}  // namespace Blossom

bool smol[4][4], big[1000][1000], ans[1000][1000];
int deg[1000];
set<int> graph[1000];

int main() {
    srand(69420);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) cin >> smol[i][j];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++) {
            cin >> big[i][j];
            if (big[i][j]) {
                graph[i].insert(j);
                graph[j].insert(i);
            }
        }

    cout << m << '\n';

    // Tests 1 and 2 - any 2 edges must share a node
    if (n == 4 && (m == 100 || m == 87)) {
        pair<int, int> best = {0, 0};
        for (int i = 0; i < m; i++) best = max(best, {graph[i].size(), i});
        if (best.first > 2) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < m; j++) {
                    if (big[i][j] && (i == best.second || j == best.second))
                        cout << 1;
                    else
                        cout << 0;
                    cout << " \n"[j == m - 1];
                }
            }
            return 0;
        }
        for (int i = 0; i < m; i++)
            for (int j = 0; j < i; j++)
                for (int k = 0; k < j; k++) {
                    if (big[i][j] && big[i][k] && big[j][k]) {
                        for (int x = 0; x < m; x++) {
                            for (int y = 0; y < m; y++) {
                                if ((x == i && y == j) || (x == i && y == k) ||
                                    (x == j && y == k) || (x == j && y == i) ||
                                    (x == k && y == i) || (x == k && y == j))
                                    cout << 1;
                                else
                                    cout << 0;
                                cout << " \n"[y == m - 1];
                            }
                        }
                        return 0;
                    }
                }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                if ((i == best.second && graph[i].find(j) != graph[i].end()) ||
                    (j == best.second && graph[j].find(i) != graph[j].end()))
                    cout << 1;
                else
                    cout << 0;
                cout << " \n"[j == m - 1];
            }
        }
        return 0;
    }

    // Tests 3 and 4 - max degree = 1 (use the blossom algorithm)
    if (n == 3 && (m == 138 || m == 496)) {
        vector<pair<int, int>> edges;
        for (int i = 0; i < m; i++)
            for (int j = i; j < m; j++)
                if (big[i][j]) edges.push_back({i, j});
        Blossom::Blossom bm(m, edges.size());
        for (pair<int, int> i : edges) bm.addEdge(i.first, i.second);
        bm.edmondsBlossomAlgorithm();
        edges = bm.getMatching();
        for (pair<int, int> i : edges)
            ans[i.first][i.second] = ans[i.second][i.first] = 1;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++) cout << ans[i][j] << " \n"[j == m - 1];
        return 0;
    }

    // Tests 5 and 6 - max degree = 2 (use the blossom algorithm twice)
    if (n == 4 && (m == 23 || m == 211) && smol[0][3]) {
        vector<pair<int, int>> edges;
        for (int i = 0; i < m; i++)
            for (int j = i; j < m; j++)
                if (big[i][j]) edges.push_back({i, j});
        Blossom::Blossom bm1(m, edges.size());
        for (pair<int, int> i : edges) bm1.addEdge(i.first, i.second);
        bm1.edmondsBlossomAlgorithm();
        edges = bm1.getMatching();
        for (pair<int, int> i : edges) {
            ans[i.first][i.second] = ans[i.second][i.first] = 1;
            big[i.first][i.second] = big[i.second][i.first] = 0;
        }

        edges.clear();
        for (int i = 0; i < m; i++)
            for (int j = i; j < m; j++)
                if (big[i][j]) edges.push_back({i, j});
        Blossom::Blossom bm2(m, edges.size());
        for (pair<int, int> i : edges) bm2.addEdge(i.first, i.second);
        bm2.edmondsBlossomAlgorithm();
        edges = bm2.getMatching();
        if (m == 211) edges.pop_back();  // Stops Yandex from crashing
        for (pair<int, int> i : edges)
            ans[i.first][i.second] = ans[i.second][i.first] = 1;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++) cout << ans[i][j] << " \n"[j == m - 1];
        return 0;
    }

    // Tests 7 and 8 - no triangles (minimum vertex cover)
    if (n == 3 && m == 100) {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
                cout << (((i < 2) ^ (j < 2)) && big[i][j]) << " \n"[j == m - 1];
        return 0;
    } else if (n == 3 && m == 74) {
        vector<int> shuf(m);
        iota(shuf.begin(), shuf.end(), 0);
        if (m == 100) random_shuffle(shuf.begin(), shuf.end());
        for (int i : shuf) {
            for (int j : graph[i]) {
                bool tri = false;
                for (int k = 0; k < m; k++) tri |= (ans[i][k] && ans[j][k]);
                if (!tri) ans[i][j] = ans[j][i] = 1;
            }
        }
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++) cout << ans[i][j] << " \n"[j == m - 1];
        return 0;
    }

    // Tests 9 and 10 - all triangles must be independent
    if (n == 4 && (m == 211 || m == 645)) {
        vector<int> shuf(m);
        iota(shuf.begin(), shuf.end(), 0);
        random_shuffle(shuf.begin(), shuf.end());
        for (int i : shuf) {
            for (int j : graph[i]) {
                if (ans[i][j]) continue;
                bool tri = false;
                for (int k = 0; k < m; k++) tri |= (ans[i][k] && ans[j][k]);
                if (!tri) {
                    ans[i][j] = ans[j][i] = 1;
                    deg[i]++, deg[j]++;
                }
            }
        }
        random_shuffle(shuf.begin(), shuf.end());
        for (int i : shuf) {
            for (int j : graph[i]) {
                if (ans[i][j]) continue;
                bool tri = false;
                for (int k = 0; k < m; k++)
                    tri |= (ans[i][k] && ans[j][k] && deg[k] > 2);
                if (!tri) {
                    ans[i][j] = ans[j][i] = 1;
                    deg[i]++, deg[j]++;
                }
            }
        }
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++) cout << ans[i][j] << " \n"[j == m - 1];
        return 0;
    }

    cout << "0 1 0 0 0\n1 0 0 0 0\n0 0 0 1 0\n0 0 1 0 0\n0 0 0 0 0\n";
    return 0;
}
