/*
IZhO 2017 Money
- A subsegment S is good iff...
    - It is nondecreasing
    - None of the previous elements of the array lie in the range (min(S), max(S))
- We can simply greedily take the longest good subsegments possible
- We use a Fenwick tree to keep track of previous elements
- Complexity: O(N log MAX_A)
*/

#include <bits/stdc++.h>
using namespace std;
 
int n, a[1000005], bit[1000005];
 
void update(int pos) {
    for (; pos < 1000005; pos += (pos & (-pos))) bit[pos]++;
}
 
int query(int a) {
    int ans = 0;
    for (; a; a -= (a & (-a))) ans += bit[a];
    return ans;
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    int ans = 0;
    update(a[0]);
    for (int i = 0; i < n;) {
        int j = i++;
        ans++;
        while (i < n && query(a[i] - 1) <= query(a[j]) && a[i] >= a[i - 1]) i++;
        for (int k = j; k < i; k++) update(a[k]);
    }
    cout << ans;
    return 0;
}