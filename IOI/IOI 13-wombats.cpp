/*
IOI 2013 Wombats
- Firstly, notice that optimal paths never cross
    - i.e. For some rows X and Y and positions A and B, if
      opt[X][A - 1][Y][B] = i and opt[X][A][Y][B - 1] = j, then
      opt[X][A - 1][Y][B] <= opt[X][A][Y][B] <= opt[X][A][Y][B - 1]
    - Proof is by contradiction (just draw it and you'll see)
- Let {x, y} be the table of minimum paths from each junction in row x
  to each junction in row y
    - We can compute this in O(C^2) because of the first observation
- Only store {2^i * x, 2^i * (x + 1)} (like a segtree)
    - Notice how each change now invalidates O(log R) of these
    - This means we can update everything in O(C^2 log R)
    - To query, use the top node of the segtree for O(1) queries
- Oh no! The problemsetter was evil and made tight memory limits
    - Instead of storing every node of the segtree, only store nodes
      such that r - l < LIM for some limit
    - This slows the program down by a factor of LIM but uses a factor
      of LIM less memory
    - LIM = 10 seems to work
- Complexity: O(UC^2 log R + Q)
*/

#include "wombats.h"
#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

const int K = 10;

int R, C, H[5000][200], V[5000][200];

int T[1024][200][200];

void hsmooth(int* A, int r) {
    FOR(i, 1, C) A[i] = min(A[i], A[i - 1] + H[r][i - 1]);
    for (int i = C - 2; i >= 0; i--) A[i] = min(A[i], A[i + 1] + H[r][i]);
}

void bruteforce(int A[200][200], int rlo, int rhi) {
    FOR(i, 0, C) {
        int* B = A[i];
        FOR(j, 0, C) B[j] = i == j ? 0 : 0x3f3f3f3f;

        FOR(r, rlo, rhi) {
            hsmooth(B, r);
            FOR(j, 0, C) {
                B[j] += V[r][j];
            }
        }
    }
}

void solve(int i, int jlo, int jhi, int klo, int khi, int R[200], int X[200], int Y[200][200]) {
    if (jlo == jhi) return;

    int jmd = (jlo + jhi) / 2;
    int kmd = klo;

    R[jmd] = X[kmd] + Y[kmd][jmd];
    FOR(k, klo + 1, khi) {
        int v = X[k] + Y[k][jmd];
        if (v < R[jmd]) {
            R[jmd] = v;
            kmd = k;
        }
    }

    solve(i, jlo, jmd, klo, kmd + 1, R, X, Y);
    solve(i, jmd + 1, jhi, kmd, khi, R, X, Y);
}

void marge(int R[200][200], int X[200][200], int Y[200][200]) {
    FOR(i, 0, C) solve(i, 0, C, 0, C, R[i], X[i], Y);
}

void update(int x, int rlo, int rhi, int rupdate) {
    if (rlo + 1 >= R) return;
    if (rhi - rlo == K) bruteforce(T[x], rlo, min(R - 1, rhi));
    else {
        int rmd = (rlo + rhi) / 2;

        if (rupdate == -1 || rupdate < rmd) update(2 * x + 1, rlo, rmd, rupdate);
        if (rupdate == -1 || rmd <= rupdate) update(2 * x + 2, rmd, rhi, rupdate);

        if (rmd + 1 < R) marge(T[x], T[2 * x + 1], T[2 * x + 2]);
        else memcpy(T[x], T[2 * x + 1], sizeof(T[x]));
    }
}

void init(int RR, int CC, int HH[5000][200], int VV[5000][200]) {
    R = RR;
    C = CC;
    memcpy(H, HH, sizeof(H));
    memcpy(V, VV, sizeof(V));
    update(0, 0, 512 * K, -1);
}

void changeH(int P, int Q, int W) {
    H[P][Q] = W;
    update(0, 0, 512 * K, P);
}

void changeV(int P, int Q, int W) {
    V[P][Q] = W;
    update(0, 0, 512 * K, P);
}

int escape(int V1, int V2) {
    hsmooth(T[0][V1], R - 1);
    return T[0][V1][V2];
}
