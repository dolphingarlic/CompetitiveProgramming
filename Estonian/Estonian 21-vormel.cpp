#include <iostream>
#include <tuple>
#include <stack>
#include <cstring>
#include <climits>
typedef long long ll;
using namespace std;

// i-th lap, j-th type of wheels, k-th time using those wheels
ll dp[201][501][201];
ll p[501], w[501];
tuple<int, int, int> backtrack[201][501][201];
bool pitstop[201][501][201];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int m, n, s;
    cin >> m >> n >> s;
    memset(dp, 0x3f, sizeof dp);
    for (int i = 1; i <= m; i++)
    {
        cin >> p[i] >> w[i];
        dp[1][i][1] = p[i];
    }
    ll prev_min = INT_MAX;
    tuple<int, int, int> prev;
    for (int j = 1; j <= m; j++)
    {
        if (dp[1][j][1] < prev_min)
        {
            prev_min = dp[1][j][1];
            prev = {1, j, 1};
        }
    }
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int k = 2; k <= i; k++)
            {
                dp[i][j][k] = p[j] + dp[i - 1][j][k - 1] + (k - 1) * w[j];
                backtrack[i][j][k] = {i - 1, j, k - 1};
            }
            dp[i][j][1] = prev_min + s + p[j];
            backtrack[i][j][1] = prev;
            pitstop[i][j][1] = true;
        }

        prev_min = INT_MAX;
        for (int j = 1; j <= m; j++)
        {
            for (int k = 1; k <= i; k++)
            {
                if (dp[i][j][k] < prev_min)
                {
                    prev_min = dp[i][j][k];
                    prev = {i, j, k};
                }
            }
        }
    }

    stack<tuple<int, int, int> > pitstops;
    for (int i = 1; i < n; i++)
    {
        if (pitstop[get<0>(prev)][get<1>(prev)][get<2>(prev)])
            pitstops.push(prev);
        prev = backtrack[get<0>(prev)][get<1>(prev)][get<2>(prev)];
    }
    cout << get<1>(prev) << ' ' << pitstops.size() << '\n';
    while (pitstops.size())
    {
        int i, j, k;
        tie(i, j, k) = pitstops.top();
        pitstops.pop();
        cout << i - 1 << ' ' << j << '\n';
    }
    return 0;
}
