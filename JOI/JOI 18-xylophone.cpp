#include "xylophone.h"

int A[5001];
bool visited[5001];

void update(int pos, int val) {
    A[pos] = val;
    visited[val] = true;
    answer(pos, val);
}

void solve(int N) {
    int l = 1, r = N;
    while (l != r) {
        int mid = (l + r + 1) / 2;
        if (query(mid, N) == N - 1)
            l = mid;
        else
            r = mid - 1;
    }

    update(l, 1);

    if (l < N) {
        int q1 = query(l, l + 1);
        update(l + 1, q1 + 1);
        for (int i = l + 2; i <= N; i++) {
            q1 = query(i - 1, i);
            if (A[i - 1] + q1 > N || visited[A[i - 1] + q1]) {
                update(i, A[i - 1] - q1);
            } else if (A[i - 1] - q1 < 1 || visited[A[i - 1] - q1]) {
                update(i, A[i - 1] + q1);
            } else {
                int q2 = query(i - 2, i);
                if (A[i - 1] > A[i - 2]) {
                    if (q2 - q1 == A[i - 1] - A[i - 2]) {
                        update(i, A[i - 1] + q1);
                    } else {
                        update(i, A[i - 1] - q1);
                    }
                } else {
                    if (q2 - q1 == A[i - 2] - A[i - 1]) {
                        update(i, A[i - 1] - q1);
                    } else {
                        update(i, A[i - 1] + q1);
                    }
                }
            }
        }
    }

    if (l > 1) {
        int q1 = query(l - 1, l);
        update(l - 1, q1 + 1);
        for (int i = l - 2; i; i--) {
            q1 = query(i, i + 1);
            if (A[i + 1] + q1 > N || visited[A[i + 1] + q1]) {
                update(i, A[i + 1] - q1);
            } else if (A[i + 1] - q1 < 1 || visited[A[i + 1] - q1]) {
                update(i, A[i + 1] + q1);
            } else {
                int q2 = query(i, i + 2);
                if (A[i + 1] > A[i + 2]) {
                    if (q2 - q1 == A[i + 1] - A[i + 2]) {
                        update(i, A[i + 1] + q1);
                    } else {
                        update(i, A[i + 1] - q1);
                    }
                } else {
                    if (q2 - q1 == A[i + 2] - A[i + 1]) {
                        update(i, A[i + 1] - q1);
                    } else {
                        update(i, A[i + 1] + q1);
                    }
                }
            }
        }
    }
}
