#include <bits/stdc++.h>
using namespace std;

#define MAXN 503
typedef long long ll;

const int MOD = 1e9 + 7;
int N, A[MAXN], B[MAXN], L[MAXN * 2], D[MAXN][MAXN * 2], inv[MAXN];
vector<int> X;

/*
 * D[i][j] = number of increasing subsequence between index 1 ~ i,
             and the largest number is equal or lower than the endpoint of
 interval j
 * inv[i] = modular inverse of integer i (modulo MOD)
 */

int main() {
    inv[1] = 1;
    for (int i = 2; i < MAXN; i++)
        inv[i] = (ll)inv[MOD % i] * (MOD - MOD / i) % MOD;

    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d%d", A + i, B + i);
        X.push_back(A[i]);
        X.push_back(B[i] + 1);
    }

    sort(X.begin(), X.end());
    X.erase(unique(X.begin(), X.end()), X.end());

    for (int i = 1; i <= N; i++) {
        A[i] = upper_bound(X.begin(), X.end(), A[i]) - X.begin();
        B[i] = upper_bound(X.begin(), X.end(), B[i]) - X.begin();
    }

    for (int i = 1; i < X.size(); i++) L[i] = X[i] - X[i - 1];
    for (int i = 0; i < X.size(); i++) D[0][i] = 1;

    for (int i = 1; i <= N; i++) {
        for (int j = A[i]; j <= B[i]; j++) {
            D[i][j] = (ll)L[j] * D[i - 1][j - 1] % MOD;

            int cnt = 1, choose = L[j] - 1;
            for (int k = i - 1; k > 0; k--) {
                if (A[k] <= j && j <= B[k]) {
                    cnt++;
                    choose = (ll)choose * (L[j] + cnt - 2) % MOD * inv[cnt] % MOD;
                    if (!choose) break;

                    D[i][j] = (D[i][j] + (ll)D[k - 1][j - 1] * choose) % MOD;
                }
            }
        }

        D[i][0] = 1;
        for (int j = 1; j < X.size(); j++)
            D[i][j] = ((ll)D[i][j] + D[i - 1][j] + D[i][j - 1] - D[i - 1][j - 1] + MOD) % MOD;
    }

    printf("%d\n", (D[N][X.size() - 1] - 1 + MOD) % MOD);
    return 0;
}