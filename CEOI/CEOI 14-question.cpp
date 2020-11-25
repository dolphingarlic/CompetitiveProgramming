#include "question.h"
using namespace std;

int sets[925][12];

void Init(int N){
    for (int i = 0, cnt = 1; i < (1<<12); i++) {
        if (__builtin_popcount(i) == 6) {
            for (int j = 0; j < 12; j++) if (i & (1<<j)) sets[cnt][j] = 1; else sets[cnt][j] = 0;
            cnt++;
        }
    }
}

int Alice(int x,int y){
    for (int i = 0; i < 12; i++) if (sets[x][i] && !sets[y][i]) return i + 1;
}

int Bob(int q,int h){
    return sets[q][h - 1];
}