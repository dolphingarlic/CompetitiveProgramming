/*
IOI 2004 Polygon
- We can view the Minkowski addition of A and B as sliding B along A's
  perimeter and taking the "trace" as A + B
- Decompose the edges of the polygon into several "primitive" vectors
    - i.e. vectors that don't cross a lattice point
    - We can find these using gcd
- If we split these vectors into two sets such that the sets both
  form a closed polygon, then the two polygons are A and B
    - Idk why this is true, but it feels true
- There are O(N * max gcd) of these vectors
- For each candidate edge/pair of edges in A, we can use a hashmap
  to check whether there exists other vectors that can form A with them
- Complexity: O(N^2 * max gcd^2)
*/

#include <bits/stdc++.h>
using namespace std;

struct Vec {
    int x, y;
    Vec operator+(Vec B) { return {x + B.x, y + B.y}; }
    Vec operator-(Vec B) { return {x - B.x, y - B.y}; }
} p[1000], prim[1000], v[1000];

bool operator<(Vec A, Vec B) { return tie(A.x, A.y) < tie(B.x, B.y); }
ostream& operator<<(ostream& o, Vec A) {
    o << A.x << ' ' << A.y;
    return o;
}

int n, t, g[1000];

void check_quad() {
    map<Vec, tuple<int, int, Vec>> mp;
    for (int i = 0; i < n; i++) {
        Vec curr = prim[i];
        for (int j = 0; j < g[i]; j++) {
            for (int k = i + 1; k < n; k++) {
                Vec curr2 = prim[k];
                for (int l = 0; l < g[k]; l++) {
                    Vec two = curr + curr2;
                    Vec cmpl = {-two.x, -two.y};
                    if (mp.count(cmpl)) {
                        int a, b, c = i, d = k;
                        Vec va, vb, vc = curr, vd = curr2;
                        tie(a, b, va) = mp[cmpl];
                        vb = cmpl - va;

                        vector<Vec> poly;
                        Vec vert = p[0];
                        for (int k = 0; k < n; k++) {
                            if (k == a) {
                                Vec pot = v[k] - va;
                                if (pot.x || pot.y) {
                                    poly.push_back(vert);
                                    vert = vert + pot;
                                }
                            } else if (k == b) {
                                Vec pot = v[k] - vb;
                                if (pot.x || pot.y) {
                                    poly.push_back(vert);
                                    vert = vert + pot;
                                }
                            } else if (k == c) {
                                Vec pot = v[k] - vc;
                                if (pot.x || pot.y) {
                                    poly.push_back(vert);
                                    vert = vert + pot;
                                }
                            } else if (k == d) {
                                Vec pot = v[k] - vd;
                                if (pot.x || pot.y) {
                                    poly.push_back(vert);
                                    vert = vert + pot;
                                }
                            } else {
                                poly.push_back(vert);
                                vert = vert + v[k];
                            }
                        }
                        if (!poly.size()) continue;
                        
                        cout << "4\n0 0\n" << va << '\n' << cmpl << '\n' << cmpl + vc << '\n';
                        cout << poly.size() << '\n';
                        for (Vec k : poly) cout << k << '\n';
                        exit(0);
                    }
                    curr2 = curr2 + prim[k];
                }
            }
            curr = curr + prim[i];
        }
        
        curr = prim[i];
        for (int j = 0; j < g[i]; j++) {
            for (int k = 0; k < i; k++) {
                Vec curr2 = prim[k];
                for (int l = 0; l < g[k]; l++) {
                    mp[curr + curr2] = {k, i, curr2};
                    curr2 = curr2 + prim[k];
                }
            }
            curr = curr + prim[i];
        }
    }
}

void check_tri() {
    map<Vec, tuple<int, int, Vec>> mp;
    for (int i = 0; i < n; i++) {
        Vec curr = prim[i], cmpl = {-prim[i].x, -prim[i].y};
        for (int j = 0; j < g[i]; j++) {
            if (mp.count(cmpl)) {
                int a, b, c = i;
                Vec va, vb, vc = curr;
                tie(a, b, va) = mp[cmpl];
                vb = cmpl - va;

                vector<Vec> poly;
                Vec vert = p[0];
                for (int k = 0; k < n; k++) {
                    if (k == a) {
                        Vec pot = v[k] - va;
                        if (pot.x || pot.y) {
                            poly.push_back(vert);
                            vert = vert + pot;
                        }
                    } else if (k == b) {
                        Vec pot = v[k] - vb;
                        if (pot.x || pot.y) {
                            poly.push_back(vert);
                            vert = vert + pot;
                        }
                    } else if (k == c) {
                        Vec pot = v[k] - vc;
                        if (pot.x || pot.y) {
                            poly.push_back(vert);
                            vert = vert + pot;
                        }
                    } else {
                        poly.push_back(vert);
                        vert = vert + v[k];
                    }
                }
                if (!poly.size()) continue;

                cout << "3\n0 0\n" << va << '\n' << cmpl << '\n';
                cout << poly.size() << '\n';
                for (Vec k : poly) cout << k << '\n';
                exit(0);
            }
            curr = curr + prim[i];
            cmpl = cmpl - prim[i];
        }

        curr = prim[i];
        for (int j = 0; j < g[i]; j++) {
            for (int k = 0; k < i; k++) {
                Vec curr2 = prim[k];
                for (int l = 0; l < g[k]; l++) {
                    mp[curr + curr2] = {k, i, curr2};
                    curr2 = curr2 + prim[k];
                }
            }
            curr = curr + prim[i];
        }
    }
}

void check_seg() {
    map<Vec, int> mp;
    for (int i = 0; i < n; i++) {
        Vec curr = prim[i], cmpl = {-prim[i].x, -prim[i].y};
        for (int j = 0; j < g[i]; j++) {
            if (mp.count(cmpl)) {
                int a = mp[cmpl], b = i;

                vector<Vec> poly;
                Vec vert = p[0];
                for (int k = 0; k < n; k++) {
                    if (k == a) {
                        Vec pot = v[k] - cmpl;
                        if (pot.x || pot.y) {
                            poly.push_back(vert);
                            vert = vert + pot;
                        }
                    } else if (k == b) {
                        Vec pot = v[k] - curr;
                        if (pot.x || pot.y) {
                            poly.push_back(vert);
                            vert = vert + pot;
                        }
                    } else {
                        poly.push_back(vert);
                        vert = vert + v[k];
                    }
                }
                if (!poly.size()) continue;

                cout << "2\n0 0\n" << cmpl << '\n';
                cout << poly.size() << '\n';
                for (Vec k : poly) cout << k << '\n';
                exit(0);
            }
            mp[curr] = i;
            curr = curr + prim[i];
            cmpl = cmpl - prim[i];
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;
    p[n] = p[0];
    cin >> t;
    cout << "#FILE polygon " << t << '\n';

    for (int i = 0; i < n; i++) {
        g[i] = abs(__gcd(p[i + 1].x - p[i].x, p[i + 1].y - p[i].y));
        v[i] = {p[i + 1].x - p[i].x, p[i + 1].y - p[i].y};
        prim[i] = {(p[i + 1].x - p[i].x) / g[i], (p[i + 1].y - p[i].y) / g[i]};
    }

    check_quad();
    check_tri();
    check_seg();
    assert(false);
    return 0;
}
