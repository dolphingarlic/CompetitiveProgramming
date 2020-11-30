/*
RMI 2018 Password
- Basically merge sort but with strings
*/

#include <string>
using namespace std;

extern int query(string str);

string solve(int l, int r, int n) {
    if (l == r) {
        string to_guess = "";
        for (int i = 0; i < n; i++) to_guess += 'a' + l;
        int len = query(to_guess);
        return string(len, 'a' + l);
    } else {
        int mid = (l + r) / 2;
        string a = solve(l, mid, n), b = solve(mid + 1, r, n);
        int a_ptr = 0, b_ptr = 0;
        string known = "";
        while (a_ptr < a.size() && b_ptr < b.size()) {
            string to_guess = known + a[a_ptr] + b.substr(b_ptr);
            int prev_len = known.size() + b.size() - b_ptr;
            if (query(to_guess) > prev_len) known += a[a_ptr++];
            else known += b[b_ptr++];
        }
        if (a_ptr < a.size()) known += a.substr(a_ptr);
        else known += b.substr(b_ptr);
        return known;
    }
}

string guess(int n, int s) { return solve(0, s - 1, n); }
