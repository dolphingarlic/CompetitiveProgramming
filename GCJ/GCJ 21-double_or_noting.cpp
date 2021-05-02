#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    for (int test = 1; test <= t; test++) {
        cout << "Case #" << test << ": ";

        string s, e;
        cin >> s >> e;
        int s_seg = 1, e_seg = 1;
        for (int i = 1; i < s.size(); i++) s_seg += s[i] != s[i - 1];
        for (int i = 1; i < e.size(); i++) e_seg += e[i] != e[i - 1];

        if (s == e) {
            cout << "0\n";
            continue;
        }
        if (e == "0") {
            cout << s_seg << '\n';
            continue;
        }
        int base = 0;
        if (s == "0") {
            s = "1";
            base++;
        }

        // Case 1: No overlap
        int ans = INT_MAX;
        if (s_seg - (s.back() == '0') >= e_seg - (e.back() == '0')) {
            ans = min(ans, int(e.size()) + s_seg);
        }

        // Case 2: Overlap
        int segs_before = -1;
        for (int i = 0; i < s.size(); i++)
            if (!i || s[i] != s[i - 1]) {
                segs_before++;
                if (s.size() - i <= e.size()) {
                    bool match0 = true, match1 = true;
                    for (int j = 0; j < s.size() - i; j++) {
                        match0 &= s[j + i] == e[j];
                        match1 &= s[j + i] != e[j];
                    }

                    if (match0) {
                        int segs_remaining = segs_before;
                        char curr_append = '0';
                        for (int j = s.size() - i; j < e.size(); j++) {
                            if (e[j] != curr_append) {
                                segs_remaining--;
                                curr_append = '1' + '0' - curr_append;
                            }
                        }
                        if (curr_append == '1') segs_remaining--;
                        if (segs_remaining >= 0)
                            ans = min(ans, int(e.size()) - int(s.size()) + i + segs_before);
                    }

                    if (match1) {
                        int segs_remaining = segs_before;
                        char curr_append = '1';
                        for (int j = s.size() - i; j < e.size(); j++) {
                            if (e[j] != curr_append) {
                                segs_remaining--;
                                curr_append = '1' + '0' - curr_append;
                            }
                        }
                        if (curr_append == '1') segs_remaining--;
                        if (segs_remaining >= 0)
                            ans = min(ans, int(e.size()) - int(s.size()) + i + segs_before);
                    }
                }
            }
        
        if (ans == INT_MAX) cout << "IMPOSSIBLE\n";
        else cout << ans + base << '\n';
    }
    return 0;
}
