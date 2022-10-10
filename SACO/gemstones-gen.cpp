#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

vector<int> tree[200001], perimeter[200001];
array<int, 3> coords[200001];
int counter = 3, assigned[200001];

void dfs1(int node = 1, int x = 1, int y = 2, int z = 3) {
    coords[node] = {x, y, z};
    if (node == 1) {
        if (tree[node].size() == 1) {
            dfs1(tree[node][0], y, z, ++counter);
            perimeter[x].push_back(y);
            perimeter[y].push_back(x);
            perimeter[x].push_back(z);
            perimeter[z].push_back(x);
        } else {
            dfs1(tree[node][0], x, y, ++counter);
            dfs1(tree[node][1], x, z, ++counter);
            perimeter[y].push_back(z);
            perimeter[z].push_back(y);
        }
    } else {
        if (tree[node].size() == 0) {
            perimeter[x].push_back(z);
            perimeter[z].push_back(x);
            perimeter[y].push_back(z);
            perimeter[z].push_back(y);
        } else if (tree[node].size() == 1) {
            dfs1(tree[node][0], x, z, ++counter);
            perimeter[y].push_back(z);
            perimeter[z].push_back(y);
        } else {
            dfs1(tree[node][0], x, z, ++counter);
            dfs1(tree[node][1], y, z, ++counter);
        }
    }
}

void dfs2(int node = 1, int curr = 1) {
    assigned[node] = curr;
    for (int i : perimeter[node]) if (!assigned[i])
        dfs2(i, curr + 1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int n = atoi(argv[1]), mx_c = atoi(argv[2]), st = atoi(argv[3]);
    for (int i = 2; i <= n - 2; i++) {
        int p = rnd.next(1, i - 1);
        while (tree[p].size() == 2) p = rnd.next(1, i - 1);
        tree[p].push_back(i);
    }
    dfs1();
    dfs2();
    cout << n << '\n';
    for (int i = 1; i <= n - 2; i++) {
        cout << assigned[coords[i][0]] << ' '
             << assigned[coords[i][1]] << ' '
             << assigned[coords[i][2]] << ' ';
        cout << rnd.next(1, mx_c) << '\n';
    }
    return 0;
}
