/*
IOI 2003 Reverse
- Let lim = {8, 44, 97, 115, 257}
    - The maximum number of consecutive S operations is
      lower_bound(lim, lim + 5) - lim
    - Let this value be mx
- Case 1: mx == 2 or mx == 4
    - TODO
- Case 2: mx == 0 or mx == 1 or mx == 3
    - TODO
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, k, reg[9];
int lim[5]{8, 44, 97, 116, 257};

void INIT(int V, int P) {
    printf("%d", V);
    if (P == 8) printf("\n");
    else printf(" ");
    assert(V > -1 && V < 256);
    assert(P > -1 && P < 9);
    reg[P] = V;
}

void ADD(int A, int B) {
    printf("S %d %d\n", A + 1, B + 1);
    assert(A > -1 && A < 9);
    assert(B > -1 && B < 9);
    reg[B] = reg[A] + 1;
}

int FIND(int V) { return find(reg, reg + 9, V) - reg; }

void PRINT(int P) {
    printf("P %d\n", P + 1);
    assert(P < 9);
    assert(reg[P] == n);
}

int main() {
    scanf("%d %d", &k, &n);
    printf("FILE reverse %d\n", k);

    int mx = lower_bound(lim, lim + 8, n) - lim;

    if (mx == 4 || mx == 2) {
        int c = n, diff1 = (mx == 2 ? 3 : 9), diff2 = (mx == 2 ? 2 : 0);
        INIT(c, 0);
        INIT(c - mx - 1, 1);
        c -= mx + 1;
        FOR(i, 1, 8) {
            c -= i * diff1 + diff2;
            INIT(max(c, 0), i + 1);
        }

        int nxt = 2, curr, rising = -1;
        queue<int> to_rise;
        bool twice = true;

        n++;
        while (n--) {
            curr = FIND(n);
            PRINT(curr);
            if (!n) break;

            int pos = FIND(n - 1);
            if (pos == 9) {
                FOR(i, 1, mx + 1) {
                    pos = FIND(n - 1 - i);
                    if (pos != 9) {
                        ADD(pos, curr);
                        for (int j = 1; j < i && reg[curr] < n - 1; j++) ADD(curr, curr);

                        if ((i != mx - 1 || mx == 2) && twice && rising > -1 && rising < 9 && rising != pos)
                            for (int j = i; j < mx && reg[rising] < n - 1; j++) ADD(rising, rising);

                        break;
                    }
                }
            } else {
                twice = !twice;
                if (twice && nxt != 9) {
                    if (!to_rise.size()) {
                        nxt++;
                        FOR(i, 0, nxt - 2) to_rise.push(reg[nxt] + i * diff1);
                    }
                    rising = FIND(to_rise.front());
                    to_rise.pop();
                } else {
                    FOR(j, 2, 2 * mx + 3) {
                        rising = FIND(n - j);
                        if (rising != 9) break;
                    }
                }

                if (rising != 9) {
                    ADD(rising, curr);
                    for (int i = 1; i < mx && reg[curr] < n - 2; i++) ADD(curr, curr);
                    rising = curr;
                }
            }
        }
    } else {
        int c = n;
        FOR(i, 0, 9) {
            INIT(max(0, c), i);
            c -= mx * i + mx + 1;
        }

        int nxt = 1, curr = -1, rising = 1;
        n++;
        while (n--) {
            int pos = FIND(n);
            if (pos == 9) {
                FOR(i, 1, mx + 1) {
                    pos = FIND(n - i);
                    if (pos != 9) {
                        ADD(pos, curr);
                        FOR(j, 1, i) ADD(curr, curr);
                        PRINT(curr);
                        break;
                    }
                }
            } else {
                if (pos == rising && nxt != 8) rising = ++nxt;
                if (~curr && mx && reg[rising] + mx < n) {
                    ADD(rising, curr);
                    FOR(i, 1, mx) ADD(curr, curr);
                    rising = curr;
                }
                PRINT(pos);
                curr = pos;
            }
        }
    }
    return 0;
}