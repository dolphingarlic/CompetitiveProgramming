#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int r, h, r_cnt = 0, h_cnt = 0;
map<string, int> r_mp, h_mp;
int r_left[1000], h_left[1000];
pair<int, int> r_right[1000], h_right[1000];
int r_prv[3000], h_prv[3000], r_known[3000], h_known[3000];

bool good(int i, int j) {
    // Right sides don't match up
    if (~r_known[r_left[i]] && r_known[r_left[i]] != h_left[j]) return false;

    // We know both variables on the left side
    if (~r_known[r_right[i].first] && ~r_known[r_right[i].second]) {
        if (make_pair(min(r_known[r_right[i].first], r_known[r_right[i].second]),
                      max(r_known[r_right[i].first], r_known[r_right[i].second]))
            != h_right[i])
            return false;
    }
    // We know only r_right[i].first
    if (~r_known[r_right[i].first]) {
        if (r_known[r_right[i].first] != h_right[i].first && r_known[r_right[i].first] != h_right[i].second)
            return false;
    }
    // We know only r_right[i].second
    if (~r_known[r_right[i].second]) {
        if (r_known[r_right[i].second] != h_right[i].first && r_known[r_right[i].second] != h_right[i].second)
            return false;
    }

    // We know neither right-hand-side variable, so we check the other program

    // We know both variables on the left side
    if (~h_known[h_right[i].first] && ~h_known[h_right[i].second]) {
        if (make_pair(min(h_known[h_right[i].first], h_known[h_right[i].second]),
                      max(h_known[h_right[i].first], h_known[h_right[i].second]))
            != r_right[i])
            return false;
    }
    // We know only h_right[i].first
    if (~h_known[h_right[i].first]) {
        if (h_known[h_right[i].first] != r_right[i].first && h_known[h_right[i].first] != r_right[i].second)
            return false;
    }
    // We know only h_right[i].second
    if (~h_known[h_right[i].second]) {
        if (h_known[h_right[i].second] != r_right[i].first && h_known[h_right[i].second] != r_right[i].second)
            return false;
    }

    // No conflicts
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> r >> h;
    for (int i = 0; i < r; i++) {
        string s1, s2, s3, tmp;
        cin >> s1 >> tmp >> s2 >> tmp >> s3 >> tmp;
        if (r_mp.find(s1) == r_mp.end()) r_mp[s1] = r_cnt++;
        if (r_mp.find(s2) == r_mp.end()) r_mp[s2] = r_cnt++;
        if (r_mp.find(s3) == r_mp.end()) r_mp[s3] = r_cnt++;
        r_left[i] = r_mp[s1];
        r_right[i] = {r_mp[s2], r_mp[s3]};
        if (r_right[i].first > r_right[i].second) swap(r_right[i].first, r_right[i].second);
    }
    for (int i = 0; i < h; i++) {
        string s1, s2, s3, tmp;
        cin >> s1 >> tmp >> s2 >> tmp >> s3 >> tmp;
        if (h_mp.find(s1) == h_mp.end()) h_mp[s1] = h_cnt++;
        if (h_mp.find(s2) == h_mp.end()) h_mp[s2] = h_cnt++;
        if (h_mp.find(s3) == h_mp.end()) h_mp[s3] = h_cnt++;
        h_left[i] = h_mp[s1];
        h_right[i] = {h_mp[s2], h_mp[s3]};
        if (h_right[i].first > h_right[i].second) swap(h_right[i].first, h_right[i].second);
    }

    int ans = 0;
    for (int delta = -h + 1; delta < r; delta++) {
        fill(r_known, r_known + 3 * r, -1);
        fill(h_known, h_known + 3 * r, -1);

        int i_lptr = max(0, delta);
        int j_lptr = i_lptr - delta;
        for (int i = i_lptr, j = j_lptr; i < r && j < h; i++, j++) {
            while (!good(i, j)) {
                // TODO: Erase programs i_lptr/j_lptr from the thing
                i_lptr++, j_lptr++;
            }
            ans = max(ans, i - i_lptr + 1);
            // TODO: Add programs i/j to the thing
            r_known[r_left[i]] = h_left[j], h_known[h_left[j]] = r_left[i];
        }
    }
    cout << ans;
    return 0;
}
