#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

typedef pair<int, int> IntPair;
typedef vector<IntPair> VectorIntPair;

#define INF 1000000000

int i, j, u, V, n, w, Q, counter, s, t;
vector<VectorIntPair> AdjList;
bool change;

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

    for (i = 0; i < V-1; i++) {
      change = false;
      for (u = 0; u < V; u++)
        for (j = 0; j < (int)AdjList[u].size(); j++) {
          counter++;
          if (counter > 1000000) {
            printf("TLE because iteration counter > 1000000\n");
            return 1;
          }

          IntPair v = AdjList[u][j];
          
          if (dist[u] + v.second < dist[v.first]) {
            dist[v.first] = dist[u] + v.second;
            change = true;
          }
        }

      if (!change) // the optimized BellmanFord
        break;
    }

    printf("%d\n", dist[t]);
  }

  printf("The value of counter is: %d\n", counter);
  return 0;
}
