#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

map<string, pair<ll, ll>> mp;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, m;
    cin >> n >> m;
    FOR(i, 0, n) {
        string name;
        cin >> name;
        ll solved = 0, penalty = 0;
        FOR(j, 0, m) {
            string s;
            cin >> s;
            if (s[0] != '-') {
                solved++;
                penalty += (s[1] - '1') * 1200;
                penalty += stoi(s.substr(3, 2)) * 3600 + stoi(s.substr(6, 2)) * 60 + stoi(s.substr(9, 2));
            } else if (s.size() > 1) {
                penalty += (s[1] - '1') * 1200;
            }
        }
        mp[name] = {-solved, penalty};
    }

    string name;
    cin >> name;
    ll solved = 0, penalty = 0;
    FOR(i, 0, m) {
        string s;
        cin >> s;
        if (s[0] == '+') {
            solved++;
            penalty += (s[1] - '1') * 1200;
            penalty += stoi(s.substr(3, 2)) * 3600 + stoi(s.substr(6, 2)) * 60 + stoi(s.substr(9, 2));
        }
    }
    mp[name] = {-solved, penalty};

    vector<pair<pair<ll, ll>, string>> v;
    for (auto& i : mp) v.push_back({i.second, i.first});
    sort(v.begin(), v.end());

    cout << find(v.begin(), v.end(), make_pair(mp[name], name)) - v.begin() + 1;
    return 0;
}