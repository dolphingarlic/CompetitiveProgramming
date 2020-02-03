/*
APIO 2015 Palembang Bridges
- Firstly, since people would only cross bridges if the 2 places are on opposite
  sides, only consider those people for the rest of the problem (since we already
  know the distances the others have to walk)
- K = 1
    - Clearly, we'd like make the bridge at the median (like IOI 2011 Ricehub)
    - Just do it
- K = 2
    - Notice that if we have 2 bridges, a person would pick the one closer to the
      median of their 2 buildings
    - Sort the people by median
    - Notice that we can split the people into 2 contiguous groups now
    - Compute the answer for prefixes and suffixes, and the answer is simply the
      minimum combination of the two at some index
    - To find the running median, we use 2 priority queues
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
bool cmp(pair<int, int> a, pair<int, int> b) { return a.first + a.second < b.first + b.second; }

priority_queue<int> lpq;
priority_queue<int, vector<int>, greater<int>> rpq;
ll lsum, rsum;

void insert(int x) {
    int median = (lpq.size() ? lpq.top() : 1000000001);
    if (x <= median) {
        lpq.push(x);
        lsum += x;
    } else {
        rpq.push(x);
        rsum += x;
    }

    if (rpq.size() + 1 < lpq.size()) {
        int nxt = lpq.top();
        lpq.pop();
        rpq.push(nxt);
        lsum -= nxt;
        rsum += nxt;
    } else if (lpq.size() < rpq.size()) {
        int nxt = rpq.top();
        rpq.pop();
        lpq.push(nxt);
        rsum -= nxt;
        lsum += nxt;
    }
}

ll pref[100001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int k, n;
    ll same_side = 0;
    vector<pair<int, int>> v = {{0, 0}};
    cin >> k >> n;
    FOR(i, 0, n) {
        char a, b;
        int x, y;
        cin >> a >> x >> b >> y;
        if (a == b) same_side += abs(x - y);
        else v.push_back({x, y});
    }
    sort(v.begin(), v.end(), cmp);
    n = v.size() - 1;
    same_side += n;
    
    lsum = rsum = 0;
    FOR(i, 1, n + 1) {
        insert(v[i].first);
        insert(v[i].second);
        pref[i] = rsum - lsum;
    }

    ll ans = pref[n];
    
    if (k == 2) {
        while (lpq.size()) lpq.pop();
        while (rpq.size()) rpq.pop();
        lsum = rsum = 0;
        
        for (int i = n; i; i--) {
            insert(v[i].first);
            insert(v[i].second);
            ans = min(ans, rsum - lsum + pref[i - 1]);
        }
    }
    cout << same_side + ans;
    return 0;
}
