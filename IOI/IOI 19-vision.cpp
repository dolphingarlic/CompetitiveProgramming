#include "vision.h"
#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

void construct_network(int H, int W, int K) {
    vector<int> l_diagonal_or, l_diagonal_xor, r_diagonal_or, r_diagonal_xor;
    FOR(i, 0, H + W - 1) {
        vector<int> l, r;
        FOR(j, 0, i + 1) {
            if (j < H && i - j < W) {
                l.push_back(j * W + i - j);
                r.push_back((H - j - 1) * W + i - j);
            }
        }
        l_diagonal_or.push_back(add_or(l));
        l_diagonal_xor.push_back(add_xor(l));
        r_diagonal_or.push_back(add_or(r));
        r_diagonal_xor.push_back(add_xor(r));
    }

    vector<int> l_2black_k_plus_1, r_2black_k_plus_1;
    FOR(i, 0, H + W - K - 1) {
        vector<int> l_or, l_xor, r_or, r_xor;
        FOR(j, 0, K + 1) {
            l_or.push_back(l_diagonal_or[i + j]);
            l_xor.push_back(l_diagonal_xor[i + j]);
            r_or.push_back(r_diagonal_or[i + j]);
            r_xor.push_back(r_diagonal_xor[i + j]);
        }
        l_2black_k_plus_1.push_back(add_xor({add_or(l_or), add_xor(l_xor)}));
        r_2black_k_plus_1.push_back(add_xor({add_or(r_or), add_xor(r_xor)}));
    }
    int less_than_k_plus_1 = add_and({add_or(l_2black_k_plus_1), add_or(r_2black_k_plus_1)});

    vector<int> l_2black_k, r_2black_k;
    FOR(i, 0, H + W - K) {
        vector<int> l_or, l_xor, r_or, r_xor;
        FOR(j, 0, K) {
            l_or.push_back(l_diagonal_or[i + j]);
            l_xor.push_back(l_diagonal_xor[i + j]);
            r_or.push_back(r_diagonal_or[i + j]);
            r_xor.push_back(r_diagonal_xor[i + j]);
        }
        l_2black_k.push_back(add_xor({add_or(l_or), add_xor(l_xor)}));
        r_2black_k.push_back(add_xor({add_or(r_or), add_xor(r_xor)}));
    }
    int less_than_k = add_and({add_or(l_2black_k), add_or(r_2black_k)});

    add_and({add_not(less_than_k), less_than_k_plus_1});
}
