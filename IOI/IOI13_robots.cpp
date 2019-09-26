#include "robots.h"
#include <bits/stdc++.h>
using namespace std;
 
#define fi first
#define se second
#define pb push_back
#define mp make_pair
typedef pair<int, int> ii;
 
const int len = 1e6+4;
int wlim[len], slim[len], n, m, k;
ii arr[len];
vector<int> vec;
priority_queue<int, vector<int>, greater<int> > pq;
 
bool check(int x){
    while (!pq.empty())
        pq.pop();
    vec.clear();
 
    for (int i = k-1, j = n-1, rem = x; i >= 0; i--){
        pq.push(arr[i].se);
        if (j >= 0 && arr[i].fi < wlim[j])
            rem--;
        else
            vec.pb(pq.top()), pq.pop();
 
        if (!rem)
            j--, rem = x;
    }
 
    sort(vec.begin(), vec.end());
    for (int i = (int)vec.size()-1, j = m-1, rem = x; i >= 0; i--){
        if (j < 0 || vec[i] >= slim[j])
            return false;
 
        rem--;
        if (!rem)
            j--, rem = x;
    }
 
    return true;
}
 
int putaway(int A, int B, int T, int X[], int Y[], int W[], int S[]){
    n = A, m = B, k = T;
 
    for (int i = 0; i < n; i++)
        wlim[i] = X[i];
    for (int i = 0; i < m; i++)
        slim[i] = Y[i];
    for (int i = 0; i < k; i++)
        arr[i] = mp(W[i], S[i]);
 
    sort(wlim, wlim+n);
    sort(slim, slim+m);
    sort(arr, arr+k);
 
    int l = 1, r = k, ans = -1;
    while (l <= r){
        int mid = (l+r)/2;
        if (check(mid))
            r = mid-1, ans = mid;
        else
            l = mid+1;
    }
 
    return ans;
}