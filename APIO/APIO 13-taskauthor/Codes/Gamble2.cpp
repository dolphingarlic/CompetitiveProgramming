#include <cstdio>
using namespace std;

int i, a, b, V, E;

int main() {
  scanf("%d %d", &V, &E);
  for (i = 0; i < E; i++)
    scanf("%d %d", &a, &b);

  printf("%d\n", V);
  printf("%d", 0);
  for (i = 1; i < V; i++)
    printf(" %d", i);
  printf("\n");

  printf("TLE because iteration counter > 1000000\n");
  return 1; // this is TLE
}
