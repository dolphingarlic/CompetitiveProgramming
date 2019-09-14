#include <bits/stdc++.h>
#define INF 10000000
using namespace std;

int n, p;
int dist[302][302];
int DP[302][32], d[302][32], vis[302][32];
int A[302];

void distances() {
    for (int i = 2; i <= n; i++)
        dist[0][i] = dist[0][i - 1] + (i - 1) * (A[i] - A[i - 1]);
    for (int i = n - 1; i; i--)
        dist[i][n + 1] = dist[i + 1][n + 1] + (n - i) * (A[i + 1] - A[i]);

    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            for (int k = i + 1; k < j; k++)
                dist[i][j] += min(A[k] - A[i], A[j] - A[k]);
}

int f(int i, int j) {
    if (j > p) return dist[i][n + 1];

    if (i > n) return INF;

    if (!vis[i][j]) {
        vis[i][j] = 1;
        DP[i][j] = INF;
        for (int k = i + 1; k <= n + 1; k++) {
            int aux = f(k, j + 1) + dist[i][k];
            if (aux < DP[i][j]) {
                DP[i][j] = aux;
                d[i][j] = k;
            }
        }
    }
    return DP[i][j];
}

int main() {
    cin >> n >> p;
    for (int i = 1; i <= n; i++) cin >> A[i];

    distances();
    int menor = INF, inicio = 0;
    for (int i = 1; i <= n; i++) {
        int aux = f(i, 2) + dist[0][i];
        if (aux < menor) {
            menor = aux;
            inicio = i;
        }
    }
    cout << menor << "\n";
    int i = inicio, j = 2;
    for (; p; p--) {
        cout << A[i];
        if (p > 1)
            cout << " ";
        else
            cout << "\n";
        i = d[i][j];
        j++;
    }
}