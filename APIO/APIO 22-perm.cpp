#include "perm.h"
 
#include <bits/stdc++.h>
using namespace std;
 
vector<int> construct_permutation(long long k) {
    int bit = 64 - __builtin_clzll(k);
    vector<double> ans;
    bool flag = false;
    while (bit > 0) {
        bit -= 2;
        if (bit == -1) {
            ans.push_back(1e9);
            if (k & 1) ans.push_back(-1e9);
        } else {
            int val = (k >> bit) & 3;
            if (ans.empty()) {
                if (val == 2) ans = {0};
                else ans = {1, 0}, flag = true;
            } else {
                if (val == 0) {
                    ans.push_back(1e9);
                    ans.push_back(1e9 + 1);
                } else if (val == 1) {
                    ans.push_back(1e9);
                    ans.push_back(1e9 + 1);
                    ans.push_back(-1e9);
                    flag = true;
                } else if (val == 2) {
                    ans.push_back(1e9);
                    ans.push_back(-1e9);
                    ans.push_back(1e9 + 1);
                    flag = true;
                } else {
                    if (!flag) {
                        ans.push_back(1e9);
                        ans.push_back(-1e9);
                        ans.push_back(1e9 + 1);
                        ans.push_back(-1e9 - 1);
                        flag = true;
                    } else {
                        ans.push_back(1e9);
                        ans.push_back(1e9 + 1);
                        ans.push_back(1.5);
                    }
                }
            }
        }
        vector<double> uni(ans.begin(), ans.end());
        sort(uni.begin(), uni.end());
        for (auto &it : ans)
            it = lower_bound(uni.begin(), uni.end(), it) - uni.begin();
    }
 
    return vector<int>(ans.begin(), ans.end());
}
