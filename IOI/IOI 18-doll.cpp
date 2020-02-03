#include "doll.h"
#include <vector>

int N, P = 1, switches = 1;
std::vector<int> X(1<<19), Y(1<<19);
bool state[1<<19];

int build(int l, int r) {
	if (l == r) return 0;
	if (r < P - N) return -1;

	int ts = switches++, mid = (l + r) / 2;
	X[ts - 1] = build(l, mid);
	Y[ts - 1] = build(mid + 1, r);
	return -ts;
}

void point(int i, int j) {
	int &a = state[-i] ? Y[-i - 1] : X[-i - 1];
	state[-i] = !state[-i];

	if (!a) a = j;
	else point(a, j);
}

void create_circuit(int M, std::vector<int> A) {
	N = A.size();
    while (P < N) P *= 2;

	build(0, P - 1);

	for (int i = 1; i < N; i++) point(-1, A[i]);
	if (N & 1) point(-1, -1);
	point(-1, 0);

	X.resize(switches), Y.resize(switches);
	std::vector<int> C(M + 1, -1);
	C[0] = A[0];

    answer(C, X, Y);
}
