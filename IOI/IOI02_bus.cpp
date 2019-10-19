#include <bits/stdc++.h>
using namespace std;

int n, x[502], y[502];
int D[502][502], O[502][502];
int H;

vector<pair<int, pair<int, int> > > M;

bool f(int a, int b) { return D[H][a] < D[H][b]; }

void preprocess() {
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            D[i][j] = D[j][i] = abs(x[i] - x[j]) + abs(y[i] - y[j]);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) O[i][j] = j;
        H = i;
        sort(O[i] + 1, O[i] + n + 1, f);
    }
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            M.push_back(make_pair(D[i][j], make_pair(i, j)));
    sort(M.begin(), M.end());
}

int cost(int a, int b, int d, int c, int H1, int H2) {
    return max(D[H1][b] + D[H1][H2] + D[H2][d],
               max(D[a][H1] + D[b][H1], D[c][H2] + D[d][H2]));
}

bool vis[502][502];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
    preprocess();

    int h1, h2, i, j, k, r;
    int mini = INT_MAX;
    int A[3], minOut;
    int lim = n <= 400 ? M.size() : 63000;
    for (r = 0; r < lim; r++) {
        h1 = M[r].second.first;
        h2 = M[r].second.second;
        if (D[h1][h2] > mini) continue;

        A[0] = A[1] = A[2] = minOut = 0;
        for (i = n; i >= 0; i--) {
            if (O[h1][i] == h2) continue;
            if (i < n) {
                if (minOut)
                    mini =
                        min(mini, cost(O[h1][i], minOut, A[0], A[1], h1, h2));
                if (A[0])
                    mini = min(mini, cost(O[h1][i], A[0], A[1], A[2], h1, h2));
                if (A[1])
                    mini = min(mini, cost(O[h1][i], A[1], A[0], A[2], h1, h2));
            }
            k = O[h1][i];
            for (j = 0; j < 3; j++)
                if (D[A[j]][h2] < D[k][h2]) swap(k, A[j]);
            minOut = minOut == 0 ? k : (D[k][h1] < D[minOut][h1] ? k : minOut);
        }
    }

    cout << mini << "\n";

    return 0;
}