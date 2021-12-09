#include "game.h"
 
void initialize(int n) {}
int c[1500];
int hasEdge(int u, int v) {
    return ++c[u > v ? u : v] == (u > v ? u : v);
}
