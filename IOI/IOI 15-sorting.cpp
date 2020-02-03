#include <bits/stdc++.h>
using namespace std;

const int maxn = 200000;
const int maxm = 600000;

int n, m;
int S[maxn], X[maxm], Y[maxm];
int Fx[maxm], Fy[maxm];

bool valid(int w) {
    int cp1[maxn];
    int cp2[maxn];
    for (int i = 0; i < n; i++) {
        cp1[i] = S[i];
        cp2[i] = S[i];
    }
    for (int i = 0; i < w; i++) {
        swap(cp1[X[i]], cp1[Y[i]]);
    }
    int fp[maxn];
    int ap[maxn];
    for (int i = 0; i < n; i++) {
        ap[cp2[i]] = i;
        fp[cp1[i]] = i;
    }
    int f[maxn];
    int fi[maxn];

    for (int i = 0; i < n; i++) {
        f[ap[i]] = fp[i];
    }
    for (int i = 0; i < n; i++) {
        fi[f[i]] = i;
    }
    int a = 0;
    for (int i = 0; i < w; i++) {
        swap(cp2[X[i]], cp2[Y[i]]);
        swap(f[X[i]], f[Y[i]]);

        ap[cp2[X[i]]] = X[i];
        ap[cp2[Y[i]]] = Y[i];
        fi[f[X[i]]] = X[i];
        fi[f[Y[i]]] = Y[i];

        bool end = false;
        while (!end && a < n) {
            int a1 = ap[a];
            int a2 = fi[a];
            if (a1 != a2) {
                swap(cp2[a1], cp2[a2]);

                ap[cp2[a1]] = a1;
                ap[cp2[a2]] = a2;

                Fx[i] = a1;
                Fy[i] = a2;
                end = true;
            }
            a++;
        }
        if (!end) {
            Fx[i] = 0;
            Fy[i] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        if (cp2[i] != i) {
            return false;
        }
    }
    return true;
}
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> S[i];
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> X[i] >> Y[i];
    }

    int a = 0, b = m + 1;
    while (a != b) {
        int h = (a + b) / 2;
        if (valid(h)) {
            b = h;
        } else {
            a = h + 1;
        }
    }

    valid(b);
    cout << b << '\n';
    for (int i = 0; i < b; i++) {
        cout << Fx[i] << ' ' << Fy[i] << '\n';
    }
}
