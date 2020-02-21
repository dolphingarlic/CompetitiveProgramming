#include <bits/stdc++.h>
#include "artclass.h"
using namespace std;
typedef long long ll;
#define D 20
#define K 300
#define F 250
#define PB push_back
int s, t[10005], sz, ch, fh;
vector<int> q[250005];
bool vis[250005];
ll ul, ur, dl, dr, rs, gs, bs;
void dfs(int v) {
    vis[v] = true;
    s++;
    if (s > 10000) return;
    for (int i = 0; i < q[v].size(); i++) {
        int u = q[v][i];
        if (!vis[u]) dfs(u);
    }
}
int style(int h, int w, int r[500][500], int g[500][500], int b[500][500]) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (i < h / 2 && j < w / 2) ul += ll(r[i][j] + g[i][j] + b[i][j]);
            if (i < h / 2 && j >= w / 2) ur += ll(r[i][j] + g[i][j] + b[i][j]);
            if (i >= h / 2 && j < w / 2) dl += ll(r[i][j] + g[i][j] + b[i][j]);
            if (i >= h / 2 && j >= w / 2) dr += ll(r[i][j] + g[i][j] + b[i][j]);
            rs += ll(r[i][j]);
            gs += ll(g[i][j]);
            bs += ll(b[i][j]);
            if (j + 1 < w && abs(r[i][j] - r[i][j + 1]) < D &&
                abs(g[i][j] - g[i][j + 1]) < D &&
                abs(b[i][j] - b[i][j + 1]) < D) {
                q[i * w + j].PB(i * w + j + 1);
                q[i * w + j + 1].PB(i * w + j);
            }
            if (j + 1 < w && abs(r[i][j] - r[i][j + 1]) +
                                     abs(g[i][j] - g[i][j + 1]) +
                                     abs(b[i][j] - b[i][j + 1]) >
                                 K) {
                ch++;
            }
            if (j + 1 < w && abs(r[i][j] - r[i][j + 1]) +
                                     abs(g[i][j] - g[i][j + 1]) +
                                     abs(b[i][j] - b[i][j + 1]) >
                                 F) {
                fh++;
            }
            if (i + 1 < h && abs(r[i][j] - r[i + 1][j]) < D &&
                abs(g[i][j] - g[i + 1][j]) < D &&
                abs(b[i][j] - b[i + 1][j]) < D) {
                q[i * w + j].PB((i + 1) * w + j);
                q[(i + 1) * w + j].PB(i * w + j);
            }
            if (i + 1 < h && abs(r[i][j] - r[i + 1][j]) +
                                     abs(g[i][j] - g[i + 1][j]) +
                                     abs(b[i][j] - b[i + 1][j]) >
                                 K) {
                ch++;
            }
            if (i + 1 < h && abs(r[i][j] - r[i + 1][j]) +
                                     abs(g[i][j] - g[i + 1][j]) +
                                     abs(b[i][j] - b[i + 1][j]) >
                                 F) {
                fh++;
            }
            vis[i * w + j] = false;
        }
    }
    for (int i = 0; i < h * w; i++) {
        if (!vis[i]) {
            s = 0;
            dfs(i);
            sz++;
        }
    }
    ll sum = ur + ul + dl + dr;
    if (ch < 10) return 4;
    if (sz > 39000) return 3;
    if (fh < 200) return 2;
    if (double(bs) / double(rs + gs + bs) < double(0.24)) return 2;
    if (abs(double(ur + ul) / double(sum) - double(0.5)) * double(10) > 0.83 ||
        abs(double(ur + dr) / double(sum) - double(0.5)) * double(10) > 0.8)
        return 2;
    if (sum < 60000000LL) return 2;
    return 1;
}