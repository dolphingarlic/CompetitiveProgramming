/*
InfO(1) Cup 2019 Consul
- The probability of finding the winner in 25 random guesses is very high
*/

#include "grader.h"

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void solve(int n) {
    srand(69420);
    set<int> found;
    int unknown = n;
    vector<int> rem(n);
    iota(rem.begin(), rem.end(), 1);
    random_shuffle(rem.begin(), rem.end());

    int queries = 60;
    while (unknown > n / 3 && queries > 1) {
        int curr = rem.back();
        rem.pop_back();
        int v = kth(curr);
        queries--;
        if (found.count(v)) continue;
        found.insert(v);
        int c = cnt(v);
        queries--;
        if (c > n / 3) {
            say_answer(v);
            return;
        }
        unknown -= c;
    }
    say_answer(-1);
}
