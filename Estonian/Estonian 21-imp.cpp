#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

// cmp1 = Normal DSU, cmp2 = Biconnected component DSU
int cmp1[300001], sz[300001], cmp2[300001];
int par[300001], last_visited[300001];
int lca_iter = 0, bridge_cnt = 0;

int find(int A, int* cmp) {
    if (A == -1) return -1;
    return cmp[A] = (cmp[A] == A ? A : find(cmp[A], cmp));
}

void make_root(int v) {
    v = find(v, cmp2);
    int root = v;
    int child = -1;
    while (v != -1) {
        int p = find(par[v], cmp2);
        par[v] = child;
        cmp1[v] = root;
        child = v;
        v = p;
    }
    sz[root] = sz[child];
}

void merge_path(int a, int b) {
    lca_iter++; // Bypass having to clear the array each time
    vector<int> path_a, path_b;
    int lca = -1;
    while (lca == -1) {
        if (a != -1) {
            a = find(a, cmp2);
            path_a.push_back(a);
            if (last_visited[a] == lca_iter){
                lca = a;
                break;
            }
            last_visited[a] = lca_iter;
            a = par[a];
        }
        if (b != -1) {
            b = find(b, cmp2);
            path_b.push_back(b);
            if (last_visited[b] == lca_iter){
                lca = b;
                break;
            }
            last_visited[b] = lca_iter;
            b = par[b];
        }
    }

    for (int v : path_a) {
        cmp2[v] = lca;
        if (v == lca) break;
        bridge_cnt--;
    }
    for (int v : path_b) {
        cmp2[v] = lca;
        if (v == lca) break;
        bridge_cnt--;
    }
}

void add_edge(int a, int b) {
    a = find(a, cmp2), b = find(b, cmp2);
    if (a == b) return;
    int a2 = find(a, cmp1), b2 = find(b, cmp1);
    if (a2 != b2) {
        bridge_cnt++;
        // Merge by rank to do LCA
        if (sz[a2] > sz[b2]) {
            swap(a, b);
            swap(a2, b2);
        }
        make_root(a);
        par[a] = cmp1[a] = b;
        sz[b2] += sz[a];
    } else {
        merge_path(a, b);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    iota(cmp1 + 1, cmp1 + n + 1, 1);
    iota(cmp2 + 1, cmp2 + n + 1, 1);
    fill(sz + 1, sz + n + 1, 1);
    fill(par + 1, par + n + 1, -1);
    while (q--) {
        char c;
        cin >> c;
        if (c == '+') {
            int u, v;
            cin >> u >> v;
            add_edge(u, v);
        } else {
            int k;
            cin >> k;
            cout << (k >= n || n - bridge_cnt - 1 > k ? "EI" : "JAH") << '\n';
        }
    }
    return 0;
}
