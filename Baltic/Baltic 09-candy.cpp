#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;
 
pair<int, int> candies[100000];
pair<pair<int, int>, int> out[100001];
vector<int> wagons;
 
int main() {
    int n;
    cin >> n;
    FOR(i, 0, n) {
        int s, t;
        cin >> s >> t;
        candies[i] = {t + s, t - s};
    }
    sort(candies, candies + n);
    
    FOR(i, 0, n) {
        int a = candies[i].first, b = -candies[i].second;
        int pos = lower_bound(wagons.begin(), wagons.end(), b) - wagons.begin();
        if (pos == wagons.size()) wagons.push_back(b);
        else wagons[pos] = b;
        
        out[i] = {{(a + b) / 2, (a - b) / 2}, pos + 1};
    }
    
    cout << wagons.size() << '\n';
    FOR(i, 0, n) {
        cout << out[i].first.first << ' ' << out[i].first.second << ' ' << out[i].second << '\n';
    }
    return 0;
}