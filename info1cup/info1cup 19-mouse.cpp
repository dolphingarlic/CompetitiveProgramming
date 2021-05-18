#include "grader.h"

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

// int n;
// vector<int> p;
// bool success = false;
// int queries = 0;

// int query(vector<int> q) {
//     queries++;
//     int cnt = 0;
//     for (int i = 0; i < n; i++) cnt += p[i] == q[i];
//     if (cnt == n) success = true;
//     return cnt;
// }

void solve(int N) {
    srand(694201337);
    vector<int> perm(N), pot(N);
    iota(perm.begin(), perm.end(), 1);
    vector<bool> known(N, false);
    int prv = -1;
    for (int i = 0; i < N;) {
        if (known[i]) {
            i++;
            continue;
        }
        int baseline = query(perm);
        if (baseline == N) return;

        int found = -1;
        for (int j = i + 1; j < N; j++) if (!known[j]) {
            swap(perm[i], perm[j]);
            pot[j] = query(perm);
            if (pot[j] == N) return;
            if (pot[j] > baseline) {
                found = j;
                break;
            }
            swap(perm[i], perm[j]);
        }
        if (~found) {
            for (int j = i + 1; j < N; j++) {
                if (pot[j] > baseline) break;
                if (!known[j] && pot[j] < baseline) known[j] = true;
            }
            if (~prv) known[prv] = true;
            prv = found;
        } else {
            for (int j = i + 1; j < N; j++) {
                if (pot[j] > baseline) break;
                if (!known[j] && pot[j] == baseline - 2) known[j] = true;
            }
            known[i] = true;
            i++;
            prv = -1;
        }
    }
    query(perm);
}

// int main() {
//     cin >> n;
//     p.resize(n);
//     for (int i = 0; i < n; i++) cin >> p[i];
//     solve(n);
//     if (success) {
//         cout << "Found the permutation after " << queries << " queries";
//     } else {
//         cout << "Wrong answer";
//     }
// }
