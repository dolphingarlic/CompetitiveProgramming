#include "monster.h"

#include <bits/stdc++.h>
using namespace std;

namespace {

vector<int> ans;

void quicksort(vector<int> cands, vector<int> spaces) {
  for (int i : cands) cout << i << ' ';
  cout << "| ";
  for (int i : spaces) cout << i << ' ';
  cout << endl;

  int N = cands.size();
  if (N <= 10) {
    vector<vector<bool>> win(N, vector<bool>(N));
    vector<int> has_strength(N);

    for (int i = 0; i < N; i++) for (int j = 0; j < i; j++) {
      bool res = Query(cands[i], cands[j]);
      win[i][j] = res, win[j][i] = !res;
    }

    vector<int> least, most;
    for (int i = 0; i < N; i++) {
      int win_cnt = accumulate(win[i].begin(), win[i].end(), 0);
      if (win_cnt == 1) least.push_back(i);
      else if (win_cnt == N - 2) most.push_back(i);
      else {
        ans[cands[i]] = spaces[win_cnt];
        has_strength[win_cnt] = i;
      }
    }

    if (N == 4) {
      int i = 0;
      if (win[most[i]][least[0]] && win[most[i]][least[1]])
        i++;
      ans[cands[most[i]]] = spaces[2], ans[cands[most[1 - i]]] = spaces[3];

      if (win[most[i]][least[0]])
        ans[cands[least[0]]] = spaces[0], ans[cands[least[1]]] = spaces[1];
      else
        ans[cands[least[0]]] = spaces[1], ans[cands[least[1]]] = spaces[0];
    } else {
      if (win[has_strength[2]][least[0]])
        ans[cands[least[0]]] = spaces[0], ans[cands[least[1]]] = spaces[1];
      else
        ans[cands[least[0]]] = spaces[1], ans[cands[least[1]]] = spaces[0];

      if (win[most[0]][has_strength[N - 3]])
        ans[cands[most[0]]] = spaces[N - 1], ans[cands[most[1]]] = spaces[N - 2];
      else
        ans[cands[most[0]]] = spaces[N - 2], ans[cands[most[1]]] = spaces[N - 1];
    }
  } else {
    random_shuffle(cands.begin(), cands.end());
    for (int i : cands) {
      vector<int> win, lose;
      for (int j : cands) if (i != j) {
        if (Query(i, j)) win.push_back(j);
        else lose.push_back(j);
      }

      if (win.size() > 3 && lose.size() > 3) {
        ans[i] = spaces[win.size()];
        vector<int> left, right;
        for (int j = 0; j < win.size() - 1; j++)
          left.push_back(j);
        left.push_back(win.size() + 1);
        right.push_back(win.size() - 1);
        for (int j = win.size() + 2; j < N; j++)
          right.push_back(j);
        quicksort(win, left);
        quicksort(lose, right);
        return;
      }
    }
  }
}

}

vector<int> Solve(int N) {
  srand(69420);
  ans.resize(N);
  vector<int> cands(N), spaces(N);
  iota(cands.begin(), cands.end(), 0);
  iota(spaces.begin(), spaces.end(), 0);
  quicksort(cands, spaces);
  return ans;
}
