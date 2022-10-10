#include <iostream>
#include <vector>
using namespace std;

void init(int subtask, int N);
int solve();

namespace INTERNAL {

string verdict = "W";
void fail(string msg = "") {
	cout << verdict << endl;
	if (msg.size()) {
		cerr << msg << endl;
	}
	exit(0);
}
 
void fassert(bool cond, string msg = "") {
	if (!cond) {
		fail(msg);
	}
}

int cur_num_ops = 0;
vector<int> P;
int max_num_ops = 0;
int N;

void init_test() {
	cur_num_ops = 0;
	P.resize(N);
	for (int& p: P) cin >> p;
}

void grade() {
	int subtask, T; cin >> subtask >> N >> T;
	init(subtask, N);
	while (T--) {
		init_test();
		int idx = solve();
		fassert(P.at(idx) == 0, "wrong minimum");
		max_num_ops = max(max_num_ops, cur_num_ops);
	}
	cout << "OK " << max_num_ops << endl;
}

}

bool less_than(int i, int j) {
	using namespace INTERNAL;
	++cur_num_ops;
	fassert(cur_num_ops <= 1000000, "way over the limit ...");
	return P.at(i) < P.at(j);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	INTERNAL::grade();
}
