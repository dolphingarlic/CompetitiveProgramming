// #include <bits/stdc++.h>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <set>
#include <utility>
#include <vector>
using namespace std;

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

vector<int> tree[100001];
int n, t, cluster_size, num_clusters, num_singular;
int sz[100001], first_half[100001], second_half[100001];
vector<vector<int>> rects;

void gen_cluster(int x) {
    int num_wildcard = cluster_size / 10 - rng() % (cluster_size / 10);
    vector<int> x1, y1, x2, y2, rem_x, rem_y;
    random_shuffle(first_half, first_half + cluster_size);
    random_shuffle(second_half, second_half + cluster_size);
    for (int i = 0; i < num_wildcard; i++) {
        x1.push_back(first_half[i]);
        x2.push_back(second_half[i]);
    }
    for (int i = num_wildcard; i < cluster_size; i++) {
        rem_x.push_back(first_half[i]);
        rem_x.push_back(second_half[i]);
    }
    sort(rem_x.begin(), rem_x.end());

    random_shuffle(first_half, first_half + cluster_size);
    random_shuffle(second_half, second_half + cluster_size);
    for (int i = 0; i < num_wildcard; i++) {
        y1.push_back(first_half[i]);
        y2.push_back(second_half[i]);
    }
    for (int i = num_wildcard; i < cluster_size; i++) {
        rem_y.push_back(first_half[i]);
        rem_y.push_back(second_half[i]);
    }
    sort(rem_y.begin(), rem_y.end());

    for (int i = 0; i < num_wildcard; i++)
        rects.push_back({x + x1[i], x + y1[i], x + x2[i], x + y2[i]});
    for (int i = 0; i < cluster_size - num_wildcard; i++)
        rects.push_back({x + rem_x[i], x + rem_y[rem_y.size() / 2 - i - 1],
                         x + rem_x[rem_x.size() - i - 1],
                         x + rem_y[rem_y.size() / 2 + i]});
}

void gen_tree(int node = 0, int x = 0) {
    int prv = 0;
    for (int i : tree[node]) {
        if (i <= num_singular || cluster_size == 1) {
            rects.push_back({2 * prv + x + 1, 2 * prv + x + 1,
                             2 * (prv + sz[i]) + x, 2 * (prv + sz[i]) + x});
        } else
            gen_cluster(2 * prv + x + 1);
        gen_tree(i, 2 * prv + x + 1);
        prv += sz[i];
    }
}

int main(int argc, char* argv[]) {
    int tc = atoi(argv[1]);
    // int b = atoi(argv[2]);
    // int c = atoi(argv[3]);

    if (tc <= 4) {
        n = 1000;
        t = 2;
        cluster_size = rng() % 50 + 51;
    } else if (tc <= 7) {
        n = 100000;
        t = 2;
        cluster_size = 100001;
    } else if (tc <= 13) {
        n = 100000;
        t = (tc <= 10 ? 1 : 2);
        cluster_size = n;
    } else {
        n = 100000;
        t = (tc <= 18 ? 1 : 2);
        cluster_size = rng() % 2500 + 7501;
    }
    num_clusters = n / cluster_size;
    num_singular = n - num_clusters * cluster_size;
    iota(first_half, first_half + cluster_size, 0);
    iota(second_half, second_half + cluster_size, cluster_size);

    // We're going to make a tree where some leaves are "clusters"
    // of intersecting rectangles
    for (int i = 1; i <= num_singular; i++) {
        int p = i - 1 - rng() % min(10, i);
        tree[p].push_back(i);
    }
    for (int i = 1; i <= num_clusters; i++) {
        int p = rng() % (num_singular + 1);
        tree[p].push_back(num_singular + i);
        sz[num_singular + i] = cluster_size;
    }
    for (int i = num_singular; i; i--) {
        sz[i]++;
        for (int j : tree[i]) sz[i] += sz[j];
    }
    gen_tree(0);
    random_shuffle(rects.begin(), rects.end());

    cout << n << ' ' << t << '\n';
    for (auto& i : rects) {
        cout << i[0] << ' ' << i[1] << ' ' << i[2] << ' ' << i[3] << '\n';
    }
}
