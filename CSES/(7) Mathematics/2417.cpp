#include <iostream>
#include <vector>
using namespace std;

bool composite[1000001];
vector<int> primes;

void gen_primes() {
    for (int i = 2; i <= 1000000; i++)
        if (!composite[i]) {
            primes.push_back(i);
            for (int j = i * 2; j <= 1000000; j += i)
                composite[i] = true;
        }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    gen_primes();
    int n;
    cin >> n;
    while (n--) {
        int x;
        cin >> x;
    }
    return 0;
}
