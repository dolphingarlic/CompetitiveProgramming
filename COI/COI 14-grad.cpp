/*
COI 2014 Grad
- Let OG be the original graph and AG be an auxilliary graph
    - (cities, roads) = OG
    - (nodes, edges) = AG
- Consider the following construction for AG:
    - The nodes in AG represent the roads of OG
    - Initially, AG has a single node (1--2)
    - Whenever we join city x with cities y and z, join the two nodes
      (x--y) and (x--z) with (y--z)
- Notice how AG is a tree
- We represent the "shortest path" between two nodes (a--b) and (c--d)
  as four real numbers:
    1) Shortest path between cities a and c
    2) Shortest path between cities a and d
    3) Shortest path between cities b and c
    4) Shortest path between cities b and d
- Interestingly, we can combine two "shortest paths" into one in O(1)
- This means that we can find the "shortest path" between any two nodes
  in AG in O(log N) time using LCA + binary lifting!
- To find the shortest path between cities x and y, simply find the
  "shortest path" between two nodes in AG that contain x and y respectively
*/

#include <bits/stdc++.h>
using namespace std;

struct Point { int x, y; } p[101010];

struct SP;

struct Node { // Node in tree decomposition
    int idx[2], depth;
    double dist;
    Node *complement;
    vector<Node *> anc;
    vector<SP> anc_sp;

    Node(int _u, int _v) : dist(hypot(p[_u].x - p[_v].x, p[_u].y - p[_v].y)) {
        idx[0] = _u;
        idx[1] = _v;
    }
} *has_city[101010];

struct SP { // Shortest path between two nodes in tree decomposition
    int idx[2][2];
    double dist[2][2];

    SP(Node *u) {
        idx[0][0] = idx[1][0] = u->idx[0];
        idx[0][1] = idx[1][1] = u->idx[1];
        dist[0][0] = dist[1][1] = 0;
        dist[0][1] = dist[1][0] = u->dist;
    }

    SP(Node *u, Node *v) {
        assert(u->anc[0] == v);
        idx[0][0] = u->idx[0], idx[0][1] = u->idx[1];
        idx[1][0] = v->idx[0], idx[1][1] = v->idx[1];
        if (u->idx[0] == v->idx[0]) {
            dist[0][0] = 0;
            dist[0][1] = v->dist;
            dist[1][0] = u->dist;
            dist[1][1] = u->complement->dist;
        } else {
            dist[0][0] = v->dist;
            dist[0][1] = 0;
            dist[1][0] = u->complement->dist;
            dist[1][1] = u->dist;
        }
    }

    SP(SP a, SP b) {
        assert(a.idx[1][0] == b.idx[0][0] && a.idx[1][1] == b.idx[0][1]);
        idx[0][0] = a.idx[0][0], idx[0][1] = a.idx[0][1];
        idx[1][0] = b.idx[1][0], idx[1][1] = b.idx[1][1];
        for (int i : {0, 1}) for (int j : {0, 1})
            dist[i][j] = min(a.dist[i][0] + b.dist[0][j], a.dist[i][1] + b.dist[1][j]);
    }
};

map<pair<int, int>, Node*> mp;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> p[1].x >> p[1].y >> p[2].x >> p[2].y >> n;
    has_city[1] = has_city[2] = mp[{1, 2}] = new Node(1, 2);

    for (int cnt = 2; n; n--) {
        char c;
        cin >> c;
        if (c == 'd') {
            cnt++;
            int a, b;
            cin >> p[cnt].x >> p[cnt].y >> a >> b;
            if (a > b) swap(a, b);
            Node *par = mp[{a, b}];

            Node *u = new Node(a, cnt), *v = new Node(b, cnt);
            u->complement = v, v->complement = u;
            u->depth = v->depth = par->depth + 1;
            has_city[cnt] = u;

            u->anc.push_back(par);
            u->anc_sp.push_back(SP(u, par));
            for (int i = 0; i < u->anc.size() && i < u->anc[i]->anc.size(); i++) {
                u->anc.push_back(u->anc[i]->anc[i]);
                u->anc_sp.push_back(SP(u->anc_sp[i], u->anc[i]->anc_sp[i]));
            }
            mp[{a, cnt}] = u;

            v->anc.push_back(par);
            v->anc_sp.push_back(SP(v, par));
            for (int i = 0; i < v->anc.size() && i < v->anc[i]->anc.size(); i++) {
                v->anc.push_back(v->anc[i]->anc[i]);
                v->anc_sp.push_back(SP(v->anc_sp[i], v->anc[i]->anc_sp[i]));
            }
            mp[{b, cnt}] = v;

            has_city[cnt] = u;
        } else {
            int a, b;
            cin >> a >> b;
            if (has_city[a]->depth < has_city[b]->depth) swap(a, b);
            double ans = 1e18;
            Node *anode = has_city[a], *bnode = has_city[b];
            SP asp = SP(anode), bsp = SP(bnode);

            for (int i = 0, diff = anode->depth - bnode->depth; diff; i++, diff >>= 1) {
                if (diff & 1) {
                    asp = SP(asp, anode->anc_sp[i]);
                    anode = anode->anc[i];
                }
            }
            for (int i = anode->anc.size() - 1; ~i; i--) {
                if (i < anode->anc.size() && anode->anc[i] != bnode->anc[i]) {
                    asp = SP(asp, anode->anc_sp[i]);
                    anode = anode->anc[i];
                    bsp = SP(bsp, bnode->anc_sp[i]);
                    bnode = bnode->anc[i];
                }
            }

            for (int i : {0, 1}) for (int j : {0, 1}) if (asp.idx[0][i] == a && bsp.idx[0][j] == b)
                for (int k : {0, 1}) for (int l : {0, 1}) if (asp.idx[1][k] == bsp.idx[1][l])
                    ans = min(ans, asp.dist[i][k] + bsp.dist[j][l]);
            if (anode != bnode) {
                asp = SP(asp, anode->anc_sp[0]), bsp = SP(bsp, bnode->anc_sp[0]);
                for (int i : {0, 1}) for (int j : {0, 1}) if (asp.idx[0][i] == a && bsp.idx[0][j] == b)
                    for (int k : {0, 1}) for (int l : {0, 1}) if (asp.idx[1][k] == bsp.idx[1][l])
                        ans = min(ans, asp.dist[i][k] + bsp.dist[j][l]);
            }
            cout << fixed << setprecision(6) << ans << '\n';
        }
    }
    return 0;
}