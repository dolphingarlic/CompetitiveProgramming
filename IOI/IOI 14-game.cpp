#include "game.h"
#include <bits/stdc++.h>
using namespace std;
 
int cnt[1500];
int first_time;
 
void initialize(int n) {}
int c[1500];
int hasEdge(int u, int v) {
    return ++c[u > v ? u : v] == (u > v ? u : v);
}