#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long long ll;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 10005;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

struct mf {
    struct edg {
        int pos, cap, rev;
    };
    vector<edg> gph[MAXN];
    void clear() {
        for (int i = 0; i < MAXN; i++) gph[i].clear();
    }
    void add_edge(int s, int e, int x) {
        gph[s].push_back({e, x, (int)gph[e].size()});
        gph[e].push_back({s, 0, (int)gph[s].size() - 1});
    }
    int dis[MAXN], pnt[MAXN];
    bool bfs(int src, int sink) {
        memset(dis, 0, sizeof(dis));
        memset(pnt, 0, sizeof(pnt));
        queue<int> que;
        que.push(src);
        dis[src] = 1;
        while (!que.empty()) {
            int x = que.front();
            que.pop();
            for (auto &e : gph[x]) {
                if (e.cap > 0 && !dis[e.pos]) {
                    dis[e.pos] = dis[x] + 1;
                    que.push(e.pos);
                }
            }
        }
        return dis[sink] > 0;
    }
    int dfs(int x, int sink, int f) {
        if (x == sink) return f;
        for (; pnt[x] < gph[x].size(); pnt[x]++) {
            edg e = gph[x][pnt[x]];
            if (e.cap > 0 && dis[e.pos] == dis[x] + 1) {
                int w = dfs(e.pos, sink, min(f, e.cap));
                if (w) {
                    gph[x][pnt[x]].cap -= w;
                    gph[e.pos][e.rev].cap += w;
                    return w;
                }
            }
        }
        return 0;
    }
    lint match(int src, int sink) {
        lint ret = 0;
        while (bfs(src, sink)) {
            int r;
            while ((r = dfs(src, sink, 2e9))) ret += r;
        }
        return ret;
    }
} mf;

int n, m, vtx;
char str[1001][11];
int idx[1001][11];

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> str[i];
        for (int j = 0; j < m; j++) {
            if (str[i][j] == '#') idx[i][j] = ++vtx;
        }
    }
    auto ok = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m && str[x][y] == '#';
    };
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (str[i][j] != '#') continue;
            int badx = 0, bady = 0;
            for (int k = 0; k < 4; k++) {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if (!ok(nx, ny)) {
                    if (k % 2 == 0)
                        badx++;
                    else
                        bady++;
                } else {
                    mf.add_edge(idx[nx][ny], idx[i][j], 1);
                }
            }
            if (badx) mf.add_edge(0, idx[i][j], badx);
            if (bady) mf.add_edge(idx[i][j], vtx + 1, bady);
        }
    }
    cout << mf.match(0, vtx + 1) / 2 << endl;
}
