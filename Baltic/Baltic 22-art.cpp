#include "art.h"

void solve(int N) {
    std::vector<int> o(N), q(N);
    for (int i = 0; i < N; i++) o[i] = i + 1;
    for (int i = 0; i < N; i++) {
        q[i] = publish(o);
        for (int j = 0; j < N; j++) o[j] = o[j] % N + 1;
    }
    for (int i = 0; i < N; i++)
        o[(q[i] - q[(i + 1) % N] + N) / 2] = i + 1;
    answer(o);
}
