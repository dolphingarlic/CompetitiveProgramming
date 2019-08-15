// #include "paint.h"
#include <bits/stdc++.h>

using namespace std;

const int K = 105;
const int N = 200010;

string s;
vector<int> c;
int x[N], u[N];
int n, k, tot[N];
int dp[N][K];

int u_in_range(int l, int r) { return tot[r] - (l > 0 ? tot[l - 1] : 0); }

void update_x(int l, int r) { ++x[l], --x[r + 1]; }

void update_u(int l, int r) { ++u[l], --u[r + 1]; }

int call(int at, int block) {
    if (at >= n) return block == k;
    int &ret = dp[at][block];
    if (ret != -1) return ret;
    ret = 0;
    if (block == k) {
        if (s[at] == '_') {
            ret = call(at + 1, block);
            if (ret) update_u(at, at);
            return ret;
        } else if (s[at] == '.') {
            ret = call(at + 1, block);
            if (ret) update_u(at, at);
            return ret;
        } else {
            return ret = 0;
        }
    }
    if (s[at] == '_') {
        ret = call(at + 1, block);
        if (ret) update_u(at, at);
        return ret;
    }
    if (s[at] == 'X') {
        int nxt = at + c[block];
        if (nxt > n) return ret = 0;
        if (u_in_range(at, nxt - 1) > 0) {
            return ret = 0;
        }
        if (nxt < n and s[nxt] == 'X') {
            return ret = 0;
        }
        ret = call(nxt + 1, block + 1);
        if (ret) {
            if (nxt < n) {
                update_u(nxt, nxt);
            }
            update_x(at, nxt - 1);
        }
        return ret;
    }
    int one = call(at + 1, block);
    if (one) update_u(at, at);
    int two, nxt = at + c[block];
    if (nxt > n)
        two = 0;
    else if (u_in_range(at, nxt - 1) > 0) {
        two = 0;
    } else if (nxt < n and s[nxt] == 'X') {
        two = 0;
    } else {
        two = call(nxt + 1, block + 1);
        if (two) {
            if (nxt < n) {
                update_u(nxt, nxt);
            }
            update_x(at, nxt - 1);
        }
    }
    return ret = one | two;
}

string solve_puzzle(string s_in, vector<int> c_in) {
    s = s_in, c = c_in;
    n = s.size(), k = c.size();
    memset(dp, -1, sizeof dp);
    for (int i = 0; i < n; ++i) {
        if (i > 0) tot[i] = tot[i - 1];
        if (s[i] == '_') {
            ++tot[i];
        }
    }
    call(0, 0);
    string res = "";
    for (int i = 0; i < n; ++i) {
        if (i) {
            x[i] += x[i - 1];
            u[i] += u[i - 1];
        }
        if (x[i] and u[i])
            res += '?';
        else if (x[i])
            res += 'X';
        else
            res += '_';
    }
    return res;
}

int main() {
    string s;
    cin >> s;
    int k;
    cin >> k;
    vector<int> v(k);
    for (int i = 0; i < k; i++) cin >> v[i];
    cout << solve_puzzle(s, v);
}