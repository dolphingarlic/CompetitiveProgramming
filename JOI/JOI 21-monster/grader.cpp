#include <cstdio>
#include <cstdlib>

#include "monster.h"

namespace {

using std::exit;
using std::fprintf;
using std::printf;
using std::scanf;

constexpr int Q_MAX = 25'000;
constexpr int N_MAX = 1'000;

int N;
int S[N_MAX];

int query_count = 0;

void WrongAnswer(int code) {
  printf("Wrong Answer [%d]\n", code);
  exit(0);
}

}  // namespace

bool Query(int a, int b) {
  if (++query_count > Q_MAX) WrongAnswer(6);
  if (a < 0 || N <= a || b < 0 || N <= b) WrongAnswer(4);
  if (a == b) WrongAnswer(5);
  return (S[a] > S[b]) ^ (abs(S[a] - S[b]) == 1);
}

int main() {
  if (scanf("%d", &N) != 1) {
    fprintf(stderr, "Error while reading.\n");
    exit(1);
  }
  for (int i = 0; i < N; i++) {
    if (scanf("%d", S + i) != 1) {
      fprintf(stderr, "Error while reading.\n");
      exit(1);
    }
  }
  std::vector<int> T = Solve(N);
  if ((int)T.size() != N) WrongAnswer(1);
  for (int i = 0; i < N; i++) {
    if (T[i] < 0 || N <= T[i]) WrongAnswer(2);
    if (T[i] != S[i]) WrongAnswer(3);
  }
  printf("Accepted: %d\n", query_count);
  return 0;
}
