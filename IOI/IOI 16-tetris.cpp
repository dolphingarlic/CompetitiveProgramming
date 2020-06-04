/*
IOI 2016 Mini Tetris
- If the block is type 1, place it horizontally and clear it
- Otherwise, notice how we can force only the bottom 2 rows to have pieces
- We have 6 states and we can transition between them using only type 2 and 3
- Complexity: O(N)
*/

#include "tetris.h"

void init(int n) {}

int position, rotation, state;
int nxt_pos[3][6] = {{0, 0, 0, 0, 0, 0}, {1, 0, 0, 2, 0, 1}, {1, 0, 0, 1, 0, 1}};
int nxt_rot[3][6] = {{0, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 0, 0}, {1, 3, 3, 2, 0, 1}};
int nxt_state[3][6] = {{0, 1, 2, 3, 4, 5}, {2, 2, 5, 4, 0, 0}, {1, 0, 3, 2, 5, 4}};

void new_figure(int figure_type) {
    position = nxt_pos[--figure_type][state];
    rotation = nxt_rot[figure_type][state];
    state = nxt_state[figure_type][state];
}

int get_position() { return position; }

int get_rotation() { return rotation; }
