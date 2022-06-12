#include <iostream>
#include <vector>
using namespace std;

char shift(char c, int offset) { return 'A' + ((c - 'A') + offset) % 3; }

bool consec(vector<char>& v) {
    return v.size() > 2 && v[v.size() - 3] == v.back() &&
           v[v.size() - 2] == v.back();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<char> stck[2];
    for (int i : {0, 1}) {
        char curr = '-';
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;
            c = shift(c, n - j);
            stck[i].push_back(c);
            if (consec(stck[i])) {
                stck[i].pop_back();
                stck[i].pop_back();
                stck[i].pop_back();
            }
        }
    }
    if (stck[0] == stck[1])
        cout << "YES";
    else
        cout << "NO";
}
