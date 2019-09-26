#include "messy.h"
#include <math.h>
#include <string>
#include <vector>
#define FOR(i, x, y) for (int i = x; i < y; i++)
 
std::vector<int> res;
 
void solve(int n, int levels, int l, int r, std::vector<int> inactive,
           std::vector<int> in_range) {
    if (l == r) {
        res[in_range[0]] = l;
    } else {
        std::vector<int> inside, outside;
        std::string base = "";
        FOR(i, 0, n) base += "0";
        for (int i : inactive) base[i] = '1';
 
        for (int i : in_range) {
            std::string s = base;
            s[i] = '1';
 
            if (check_element(s))
                inside.push_back(i);
            else
                outside.push_back(i);
        }
 
        int mid = (l + r) / 2;
 
        std::vector<int> left = inactive;
        left.insert(left.end(), outside.begin(), outside.end());
        solve(n, levels, l, mid, left, inside);
 
        std::vector<int> right = inactive;
        right.insert(right.end(), inside.begin(), inside.end());
        solve(n, levels, mid + 1, r, right, outside);
    }
}
 
void init(int n, int levels) {
    FOR(i, 0, n) {
        int l = 0, r = n - 1;
 
        for (int j = levels - 1; ~j; j--) {
            if (!(i & (1 << j))) {
                std::string s = "";
                FOR(k, 0, n) s += (k >= l && k <= r && k != i ? "0" : "1");
                add_element(s);
            }
 
            int mid = (l + r) / 2;
            if (i > mid)
                l = mid + 1;
            else
                r = mid;
        }
    }
 
    compile_set();
}
 
std::vector<int> restore_permutation(int n, int w, int r) {
    int levels = (int)log2(n);
    res.resize(n);
    std::vector<int> all;
    FOR(i, 0, n) all.push_back(i);
 
    init(n, levels);
    solve(n, levels, 0, n - 1, {}, all);
 
    return res;
}