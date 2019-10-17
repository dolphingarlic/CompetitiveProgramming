#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int B, D, n, m;

int A[100002];
long long int ans;

// Literally just std::lower_bound

void solutionA() {
    for (int i = 1; i <= n; i++) cin >> A[i];
    sort(A + 1, A + n + 1);

    int fin = 1;
    for (int i = 1; i <= n; i++) {
        while (A[fin] - A[i] <= D && fin <= n) fin++;
        fin--;
        ans += (ll)(fin) - (ll)(i);
    }
    cout << ans << "\n";
}

int p, lim = 150002;
struct pt {
    pt(int _x, int _y, int _t) {
        x = _x;
        y = _y;
        t = _t;
    }
    int x, y;
    int t;
};
bool operator<(pt a, pt b) {
    if (a.x < b.x) return true;
    if (b.x < a.x) return false;
    if (a.y < b.y) return true;
    if (b.y < a.y) return false;
    return a.t == 0;
}
pt P[500002] = pt(0, 0, 0);
int BIT[200002];

void get_coor(pt &a) {
    int x = a.x, y = a.y;
    a.x = x + y - 1;
    a.y = m - x + y;
}

void update(int x) {
    for (; x <= lim; x += (x & -x)) BIT[x]++;
}

int query(int x) {
    if (x == 0) return 0;
    int ret = 0;
    for (; x; x -= (x & -x)) ret += BIT[x];
    return ret;
}

// Line sweep + rotation + BIT

void solutionB() {
    for (int i = 1; i <= n; i++) {
        cin >> P[i].x >> P[i].y;
        P[i].t = 0;
        get_coor(P[i]);
    }

    p = n;
    lim = 2 * m - 1;
    for (int i = 1; i <= n; i++) {
        int nx = min(P[i].x + D, lim), ny = min(P[i].y + D, lim);
        P[++p] = pt(P[i].x - D - 1, P[i].y - D - 1, 1);
        P[++p] = pt(nx, ny, 1);
        P[++p] = pt(nx, P[i].y - D - 1, -1);
        P[++p] = pt(P[i].x - D - 1, ny, -1);
    }
    sort(P + 1, P + p + 1);

    long long int ans = 0;
    for (int i = 1; i <= p; i++) {
        if (P[i].x < 1 || P[i].y < 1) continue;
        if (P[i].t)
            ans += query(P[i].y) * P[i].t;
        else
            update(P[i].y);
    }
    ans -= n;
    ans /= 2;
    cout << ans << "\n";
}

struct pnt {
    int x, y, z;
};
pnt C[100002];
long long int M[202][202][202];

long long int sum(int k, int x, int y, int x1, int y1) {
    return M[k][x1][y1] - M[k][x1][y - 1] - M[k][x - 1][y1] +
           M[k][x - 1][y - 1];
}

void getNewCoor(pnt &a) {
    int x = a.x, y = a.y, z = a.z;
    a.x = x;
    a.y = y + z - 1;
    a.z = m - y + z;
}

// Rotate (x, y, z) -> (y + z - x, x + z - y, x + y - z) and prefix sums

void solutionC() {
    for (int i = 1; i <= n; i++) {
        cin >> C[i].x >> C[i].y >> C[i].z;
        getNewCoor(C[i]);
        M[C[i].x][C[i].y][C[i].z]++;
    }

    m *= 2;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
            for (int k = 1; k <= m; k++)
                M[i][j][k] +=
                    M[i][j][k - 1] + M[i][j - 1][k] - M[i][j - 1][k - 1];

    long long int ans = 0;
    int h, nx, ny, nx1, ny1;
    for (int x = 1; x <= n; x++)
        for (int i = 1; i <= m; i++) {
            h = D - abs(C[x].x - i);
            if (h >= 0) {
                nx = max(1, C[x].y - h);
                ny = max(1, C[x].z - h);
                nx1 = min(m, C[x].y + h);
                ny1 = min(m, C[x].z + h);
                ans += sum(i, nx, ny, nx1, ny1);
            }
        }

    ans -= n;
    ans /= 2;
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> B >> n >> D >> m;
    if (B == 1)
        solutionA();
    else if (B == 2)
        solutionB();
    else
        solutionC();
    return 0;
}