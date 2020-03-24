#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXDIM 50
#define MAXN 100
#define MAXCOLOR 100
#define MAXROOM (MAXDIM * MAXDIM)

enum { Wwest = 1, Wnorth = 2, Weast = 4, Wsouth = 8 };

typedef struct Square Square;
struct Square {
    int wall;
    int numbered;
    int room;
};

int wid, ht;
Square castle[MAXDIM][MAXDIM];
int roomsize[MAXROOM];

void number(int room, int x, int y) {
    int w;

    if (castle[x][y].numbered) {
        assert(castle[x][y].room == room);
        return;
    }

    castle[x][y].numbered = 1;
    castle[x][y].room = room;
    roomsize[room]++;

    w = castle[x][y].wall;

    if (x > 0 && !(w & Wwest)) number(room, x - 1, y);

    if (x + 1 < wid && !(w & Weast)) number(room, x + 1, y);

    if (y > 0 && !(w & Wnorth)) number(room, x, y - 1);

    if (y + 1 < ht && !(w & Wsouth)) number(room, x, y + 1);
}

int main() {
    int x, y, w, nroom, bigroom;
    int i, n, m, mx, my;
    char mc;

    std::cin >> wid >> ht;

    /* read in wall info */
    for (y = 0; y < ht; y++) {
        for (x = 0; x < wid; x++) {
            std::cin >> w;
            castle[x][y].wall = w;
        }
    }

    /* number rooms */
    nroom = 0;
    for (y = 0; y < ht; y++)
        for (x = 0; x < wid; x++)
            if (!castle[x][y].numbered) number(nroom++, x, y);

    /* find biggest room */
    bigroom = roomsize[0];
    for (i = 1; i < nroom; i++)
        if (bigroom < roomsize[i]) bigroom = roomsize[i];

    /* look at best that can come of removing an east or north wall */
    m = 0;
    for (x = 0; x < wid; x++)
        for (y = ht - 1; y >= 0; y--) {
            if (y > 0 && castle[x][y].room != castle[x][y - 1].room) {
                n = roomsize[castle[x][y].room] +
                    roomsize[castle[x][y - 1].room];
                if (n > m) {
                    m = n;
                    mx = x;
                    my = y;
                    mc = 'N';
                }
            }
            if (x + 1 < wid && castle[x][y].room != castle[x + 1][y].room) {
                n = roomsize[castle[x][y].room] +
                    roomsize[castle[x + 1][y].room];
                if (n > m) {
                    m = n;
                    mx = x;
                    my = y;
                    mc = 'E';
                }
            }
        }

    std::cout << nroom << '\n' << bigroom << '\n' << m << '\n';
    std::cout << my + 1 << ' ' << mx + 1 << ' ' << mc << '\n';

    return 0;
}