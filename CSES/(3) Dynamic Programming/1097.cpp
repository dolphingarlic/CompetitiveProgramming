#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
ll n, sum[5005], best[5005][5005];
 
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> best[i][i];
        sum[i] = sum[i - 1] + best[i][i];
    }
   
    for (int i = 1; i <= n; i++) for (int j = 1; j + i <= n; j++)
        best[j + i][j] = sum[j + i] - sum[j - 1] - min(best[j + i - 1][j], best[j + i][j + 1]);
    cout << best[n][1];
}