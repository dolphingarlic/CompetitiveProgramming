/*
Baltic 2021 Books
- Similar to IOI 2016 Molecules
- First, binary search for the least book with x[i] > A
- Next, get the values of the K least books and the K greatest
  books that have x[i] <= A
- The answer will be one of two combinations:
    - (K - 1) least books + Least book with x[i] > A
    - i least books + (K - i) greatest books with x[i] <= A
*/

#include <bits/stdc++.h>

#include "books.h"

typedef long long ll;
using namespace std;

map<int, ll> cache;

ll query(int x) {
    if (cache.count(x)) return cache[x];
    return cache[x] = skim(x);
}

ll getWindow(int l, int r, ll A) {
    ll ans = 0;
    for (int i = l; i <= r; i++) ans += query(i);
    return ans;
}

void solve(int N, int K, ll A, int S) {
    cache.clear();

    int l = 1, r = N + 1;
    while (l != r) {
        int mid = (l + r) / 2;
        if (query(mid) > A) r = mid;
        else l = mid + 1;
    }
    int partition = l;
    if (partition < K) impossible();

    ll smallest = getWindow(1, K, A);
    if (smallest > 2 * A) impossible();
    if (partition != N + 1 && smallest - query(K) + query(partition) <= 2 * A) {
        vector<int> ans = {partition};
        for (int i = 1; i < K; i++) ans.push_back(i);
        answer(ans);
    }
    vector<ll> pref = {0}, suff = {0};
    for (int i = 1; i <= K; i++) {
        ll q = query(i);
        pref.push_back(q + pref.back());
    }
    for (int i = partition - 1; i >= partition - K; i--) {
        ll q = query(i);
        suff.push_back(q + suff.back());
    }
    for (int i = 0; i <= K; i++) {
        if (pref[K - i] + suff[i] > 2 * A) impossible();
        if (pref[K - i] + suff[i] >= A) {
            vector<int> ans;
            for (int j = 1; j <= K - i; j++) ans.push_back(j);
            for (int j = 1; j <= i; j++) ans.push_back(partition - j);
            answer(ans);
        }
    }
    impossible();
}
