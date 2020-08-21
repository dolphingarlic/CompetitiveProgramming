#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

typedef vector<int> vi;

#define INF 1000000000

int i, a, b, V, E, counter, X;
vector<vi> AdjList;
vi cur, ans;
bool found;

void backtrack(int u, int label) {
  if (found) return;



  counter++;
  cur[u] = label; // assign label to u
  if (u == V - 1) { // done
    found = true;
    ans.assign(V, 0);
    for (int j = 0; j < V; j++)
      ans[j] = cur[j];
    return;
  }

  // explore neighbors
  vi ok(X, 1);

  for (int j = 0; j < (int)AdjList[u+1].size(); j++) {
    counter++;
    if (counter > 1000000)
      return;

    int v = AdjList[u+1][j];
    if (cur[v] != -1)
      ok[cur[v]] = false;
  }

  for (int j = 0; j < X; j++)
    if (ok[j])
      backtrack(u+1, j);
}

int main() {
  scanf("%d %d", &V, &E);
  AdjList.assign(V, vi());
  for (i = 0; i < E; i++) {
    scanf("%d %d", &a, &b);
    AdjList[a].push_back(b);
    AdjList[b].push_back(a);
  }

  found = false;
  counter = 0;
  for (X = 2; X <= V; X++) {
    cur.assign(V, -1);
    backtrack(0, 0);
    if (found)
      break;

    if (counter > 1000000) {
      printf("TLE\n");
      return 1;
    }
  }

  printf("%d\n", X);
  printf("%d", ans[0]);
  for (i = 1; i < V; i++)
    printf(" %d", ans[i]);
  printf("\n");

  printf("The value of counter is: %d\n", counter);
  return 0;
}
