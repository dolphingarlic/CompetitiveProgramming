#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int max_n = atoi(argv[1]), st = atoi(argv[2]);
    if (st == 2) cout << max_n << '\n';
    else if (st == 4) cout << (1 << max_n) << '\n';
    else cout << rnd.next(1, max_n) << '\n';
    return 0;
}
