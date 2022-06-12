#include <iostream>
#include <numeric>
#include <set>
using namespace std;

const int SZ = 1 << 15;

int cmp[SZ];
int find(int A) { return cmp[A] = (A == cmp[A] ? A : find(cmp[A])); }
void onion(int A, int B) { cmp[find(A)] = cmp[find(B)]; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    iota(cmp, cmp + SZ, 0);
    int n;
    cin >> n;
    set<int> opened;
    while (n--) {
        int x, y, z;
        char c1, c2;
        cin >> x >> y >> z >> c1 >> c2;
        int x2 = x, y2 = y, z2 = z;
        if (c2 == '+') {
            if (c1 == 'X') x2++;
            else if (c1 == 'Y') y2++;
            else z2++;
        } else {
            if (c1 == 'X') x2--;
            else if (c1 == 'Y') y2--;
            else z2--;
        }
        if (opened.count((x << 25) + (y << 20) + (z << 15) + (x2 << 10) + (y2 << 5) + z2))
            onion((x << 10) + (y << 5) + z, (x2 << 10) + (y2 << 5) + z2);
        else
            opened.insert((x2 << 25) + (y2 << 20) + (z2 << 15) + (x << 10) + (y << 5) + z);
    }
    int x, y, z;
    cin >> x >> y >> z;
    for (int i = 1; i <= 25; i++)
        for (int j = 1; j <= 25; j++)
            for (int k = 1; k <= 25; k++)
                if (find((x << 10) + (y << 5) + z) == find((k << 10) + (j << 5) + i))
                    cout << k << ' ' << j << ' ' << i << '\n';
    return 0;
}
