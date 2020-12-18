#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll a, m;
    int l, q;
    cin >> a >> m >> l >> q;

    ll curr_hsh = 0, curr_pw = 1;
    map<ll, vector<int>> has_hsh;
    for (int i = 1; i <= l; i++) {
        ll t;
        cin >> t;
        curr_hsh = (curr_hsh + curr_pw * t) % m;
        curr_pw = curr_pw * a % m;
        has_hsh[curr_hsh].push_back(i);
        cout << curr_hsh << ' ';
    }

    vector<tuple<int, int, int>> words;
    for (auto& i : has_hsh)
        for (int j = 1; j < i.second.size(); j++)
            words.push_back({i.second[j] - i.second[j - 1], i.second[j - 1] + 1, i.second[j]});

    sort(words.begin(), words.end(),
        [](tuple<int, int, int> A, tuple<int, int, int> B) {
            return get<1>(A) > get<1>(B);
        });
    
    for (tuple<int, int, int> i : words) {
        
    }
    return 0;
}