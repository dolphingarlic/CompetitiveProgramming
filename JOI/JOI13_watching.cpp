#include<bits/stdc++.h>
 
using namespace std;
#define taskname "A"
#define pb	push_back
#define mp 	make_pair
#ifndef LOCAL
#define cerr if(0)cout
#endif
 
typedef long double ld;
typedef long long ll;
typedef pair<int,ll> ii;
const int maxn = 2005;
 
int n , q , p;
 
int a[maxn];
 
int dp[maxn][maxn];
 
bool chk(int w){
    dp[0][0] = 0;
    int ii = 1 , jj = 1;
    for(int i = 1 ; i <= n ; ++i){
        while(a[i] - a[ii] + 1 > w)++ii;
        while(a[i] - a[jj] + 1 > 2 * w)++jj;
//        cout << ii << " " << jj << " " << i << endl;
        for(int j = 0 ; j <= i && j <= p ; ++j){
            if(j == 0)dp[i][j] = dp[jj - 1][j] + 1;
            else dp[i][j] = min(dp[jj - 1][j] + 1 , dp[ii - 1][j - 1]),dp[i][j] = min(dp[i][j] , dp[i][j - 1]);
        }
    }
//    cout << w << " " << dp[n][min(p,n)] << endl;
    return dp[n][min(p,n)] <= q;
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if(fopen(taskname".INP","r")){
		freopen(taskname".INP", "r",stdin);
		freopen(taskname".OUT", "w",stdout);
    }
    cin >> n >> p >> q;
    int l = 1 , h = 1e9;
    for(int i = 1 ; i <= n ; ++i)cin >> a[i];
    sort(a + 1 , a + n + 1);
    fill_n(&dp[0][0],maxn*maxn,q + 1);
    while(l <= h){
        int mid = l + h >> 1;
        if(!chk(mid))l = mid + 1;
        else h = mid - 1;
//        return 0;
    }
    cout << l;
}