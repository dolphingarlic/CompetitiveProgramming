#include <algorithm>
#include <cstdio>
using namespace std;

int i, j, k, V, n, w, M[300][300], counter, Q, s, t;

int main() {
  scanf("%d", &V);
  for (i = 0; i < V; i++)
    for (j = i+1; j < V; j++)
      M[i][j] = M[j][i] = 1000000000;
  for (i = 0; i < V; i++)
    M[i][i] = 0;

  for (i = 0; i < V; i++) {
    scanf("%d", &n);
    while (n--) {
      scanf("%d %d", &j, &w);
      M[i][j] = min(M[i][j], w);
    }
  }

  counter = 0;
  for (k = 0; k < V; k++)
    for (i = 0; i < V; i++)
      for (j = 0; j < V; j++) {
        counter++;
        if (counter > 1000000) {
          printf("TLE because iteration counter > 1000000\n");
          return 1;
        }
        M[i][j] = min(M[i][j], M[i][k] + M[k][j]);
      }

  scanf("%d", &Q);
  while (Q--) {
    scanf("%d %d", &s, &t);
    printf("%d\n", M[s][t]);
  }

  printf("The value of counter is: %d\n", counter);
  return 0;
}
