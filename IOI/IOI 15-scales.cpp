/*
IOI 2015 Scales
- Firstly, Q = 6
- Notice how each query has one of three outcomes and 3^6 > 6!
- This means that we should make queries in a way such that after K
  queries, there are at most 3^(6 - K) possible permutations left
- We can then just brute force a decision tree to find the optimal
  query for each set of possible permutations
- Honestly this problem is just so cancerous I can't be bothered to work
  out the complexity
*/

#include "scales.h"

#include <bits/stdc++.h>
using namespace std;

int lim[] = {1, 3, 9, 27, 81, 243, 729};

struct Ord {
    int a[7];
    Ord(vector<int>& v) {
        for (int i = 0; i < 6; i++) a[i + 1] = v[i];
    }
};

struct Query {
    int a, b, c, d;

    int ask() {
        int res;
        if (d == a) res = getLightest(a, b, c);
        else if (d == b) res = getMedian(a, b, c);
        else if (d == c) res = getHeaviest(a, b, c);
        else res = getNextLightest(a, b, c, d);
        if (res == a) return 1;
        if (res == b) return 2;
        if (res == c) return 3;
    }

    int simulate(Ord& ord) {
        int i = a, j = b, l = c, res;
        if (ord.a[i] > ord.a[j]) swap(i, j);
        if (ord.a[j] > ord.a[l]) swap(j, l);
        if (ord.a[i] > ord.a[j]) swap(i, j);
        if (a == d) res = i;
        else if (b == d) res = j;
        else if (c == d) res = l;
        else if (ord.a[d] < ord.a[i]) res = i;
        else if (ord.a[d] < ord.a[j]) res = j;
        else if (ord.a[d] < ord.a[l]) res = l;
        else res = i;
        if (res == a) return 1;
        if (res == b) return 2;
        if (res == c) return 3;
    }
};

vector<Query> all_queries;

struct State {
    int rem;
    vector<Ord*> possible;
    Query* opt;
    State* children[4];

    bool init() {
        if (possible.size() <= 1) return true;

        int cnt[4];
        for (Query& q : all_queries) {
            cnt[1] = cnt[2] = cnt[3] = 0;

            for (Ord*& o : possible) {
                int res = q.simulate(*o);
                cnt[res]++;
                if (cnt[res] > lim[rem]) break;
            }
            if (max({cnt[1], cnt[2], cnt[3]}) > lim[rem]) continue;

            for (int i = 1; i < 4; i++) {
                children[i] = new State();
                children[i]->rem = rem - 1;
            }
            for (Ord* o : possible) children[q.simulate(*o)]->possible.push_back(o);

            bool good = true;
            for (int i = 1; i < 4; i++) good &= children[i]->init();
            if (!good) {
                for (int i = 1; i < 4; i++) delete children[i];
            } else {
                opt = &q;
                return true;
            }
        }
        return false;
    }
} *root;

void init(int T) {
    for (int i = 1; i < 5; i++)
        for (int j = i + 1; j < 6; j++)
            for (int k = j + 1; k < 7; k++)
                for (int l = 1; l < 7; l++) all_queries.push_back({i, j, k, l});

    root = new State();
    root->rem = 5;

    vector<int> curr_perm = {1, 2, 3, 4, 5, 6};
    do {
        root->possible.push_back(new Ord(curr_perm));
    } while (next_permutation(curr_perm.begin(), curr_perm.end()));

    assert(root->init());
}

void orderCoins() {
    int W[] = {1, 2, 3, 4, 5};
    State *ans = root;
    while (ans->possible.size() > 1) ans = ans->children[ans->opt->ask()];
    for (int i = 1; i <= 6; i++) W[ans->possible[0]->a[i] - 1] = i;
    answer(W);
}