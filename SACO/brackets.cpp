#include <iostream>
using namespace std;

bool open[200][200];

int main() {
    int k;
    cin >> k;
    
    if (k == 4) {
        cout << "3 4\n+---\n+++-\n+---\n";
        return 0;
    }

    for (int i = 0, x = 0, y = 0; i < 30; i++, x += 2, y += 6, k >>= 1) {
        open[x][y] = open[x + 1][y + 1] = true;
        open[x + 1][y + 3] = open[x + 2][y + 3] = true;
        if (k & 1)
            for (int j = x + 2; j < 200; j += 2) open[j][y] = true;
    }
    for (int i = 0; i < 200; i += 2) open[64][i] = true;

    cout << "65 200\n";
    for (int i = 0; i < 65; i++) {
        for (int j = 0; j < 200; j++) {
            if (open[i][j])
                cout << '+';
            else
                cout << '-';
        }
        cout << '\n';
    }
}
