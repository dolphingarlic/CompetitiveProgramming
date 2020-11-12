/*
CEOI 2009 Boxes
- See the official editorial
*/

#include <iostream>
#include <map>

int n, at[10001];
std::map<int, int> occupied;

inline void place(int box, int pos) {
    std::cout << "I " << (pos + n) % n + 1 << std::endl;
    occupied[pos] = box;
    at[box] = pos;
}

inline void move(int box, int pos) {
    std::cout << "M " << box << ' ' << (pos + n) % n + 1 << std::endl;
    occupied.erase(at[box]);
    occupied[pos] = box;
    at[box] = pos;
}

int main() {
    std::cin >> n;
    for (int i = 1, p = 0; i <= n / 4; p += 1 + 100 * (i % 100 == 0), i++) {
        place(i, p);
    }
    for (int i = n / 4 + 1; i <= n / 2; i++) {
        int b, to_left = 0, to_right = 0;
        std::cin >> b;
        
        // Determine where to insert the box
        for (int j = at[b]; occupied.count(j); to_left++, j--);
        for (int j = at[b] + 1; occupied.count(j); to_right++, j++);
        if (to_left < to_right) {
            int pos = at[b];
            for (int j = at[b] - to_left + 1; j != pos + 1; j++) move(occupied[j], j - 1);
            place(i, pos);
        } else {
            int pos = at[b] + 1;
            for (int j = at[b] + to_right; j != pos - 1; j--) move(occupied[j], j + 1);
            place(i, pos);
        }

        // Rebalancing
        for (int j = 0, pos = occupied.rbegin()->first + 101; j < 100; j++, pos++) {
            move(occupied.begin()->second, pos);
        }
    }
    return 0;
}