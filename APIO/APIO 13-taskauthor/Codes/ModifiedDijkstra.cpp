#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> IntPair;
typedef vector<IntPair> VectorIntPair;

#define INF 1000000000

int i, j, V, n, w, counter, Q, s, t, d, u;
vector<VectorIntPair> AdjList;

// scroll down to line 92 for the
// short C++ implementation (with STL priority_queue)










































































int main() {
  scanf("%d", &V);
  AdjList.assign(V, VectorIntPair());
  for (i = 0; i < V; i++) {
    scanf("%d", &n);
    while (n--) {
      scanf("%d %d", &j, &w);
      AdjList[i].push_back(IntPair(j, w));

    }
  }

  counter = 0;
  scanf("%d", &Q);
  while (Q--) {
    scanf("%d %d", &s, &t);

    vector<int> dist(V, INF);
    dist[s] = 0;
    priority_queue< IntPair, vector<IntPair>, greater<IntPair> > pq;
    pq.push(IntPair(0, s));
    while (!pq.empty()) {
      counter++;
      if (counter > 1000000) {
        printf("TLE because iteration counter > 1000000\n");
        return 1;
      }

      IntPair front = pq.top(); pq.pop();
      d = front.first; u = front.second;
      if (d == dist[u]) {
        for (j = 0; j < (int)AdjList[u].size(); j++) {
          IntPair v = AdjList[u][j];
          if (dist[u] + v.second < dist[v.first]) {
            dist[v.first] = dist[u] + v.second;
            pq.push(IntPair(dist[v.first], v.first));
          }
        }
      }
    }

    printf("%d\n", dist[t]);
  }

  printf("The value of counter is: %d\n", counter);
  return 0;
}
