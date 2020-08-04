#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const int B_SIZE = 9;

bool can_place(vector<vector<bool>> board, int type, int column) {
    switch (type) {
        case 1:
            return !(board[0][column]);
        case 2:
            return !(board[0][column] || board[1][column]);
        case 3:
            return !(column > 7 || board[0][column] || board[0][column + 1]);
        case 4:
            return !(board[0][column] || board[1][column] || board[2][column]);
        case 5:
            return !(column > 6 || board[0][column] || board[0][column + 1] || board[0][column + 2]);
        case 6:
            return !(column > 7 || board[0][column] || board[1][column] || board[0][column + 1] || board[1][column + 1]);
        case 7:
            return !(column > 7 || board[0][column] || board[1][column] || board[0][column + 1] || board[1][column + 1]);
        case 8:
            return !(column > 7 || board[0][column] || board[1][column] || board[0][column + 1]);
        case 9:
            return !(column > 7 || board[0][column] || board[1][column + 1] || board[0][column + 1]);
        default:
            return false;
    }
}

vector<vector<bool>> place_piece(vector<vector<bool>> board, int type, int column) {
    switch (type) {
        case 1:
            FOR(i, 0, B_SIZE) if (i == B_SIZE - 1 || board[i + 1][column]) {
                board[i][column] = 1;
                break;
            }
            break;
        case 2:
            FOR(i, 1, B_SIZE) if (i == B_SIZE - 1 || board[i + 1][column]) {
                board[i][column] = board[i - 1][column] = 1;
                break;
            }
            break;
        case 3:
            FOR(i, 0, B_SIZE) if (i == B_SIZE - 1 || board[i + 1][column] || board[i + 1][column + 1]) {
                board[i][column] = board[i][column + 1] = 1;
                break;
            }
            break;
        case 4:
            FOR(i, 2, B_SIZE) if (i == B_SIZE - 1 || board[i + 1][column]) {
                board[i][column] = board[i - 1][column] = board[i - 2][column] = 1;
                break;
            }
            break;
        case 5:
            FOR(i, 0, B_SIZE) if (i == B_SIZE - 1 || board[i + 1][column] || board[i + 1][column + 1] || board[i + 1][column + 2]) {
                board[i][column] = board[i][column + 1] = board[i][column + 2] = 1;
                break;
            }
            break;
        case 6:
            FOR(i, 1, B_SIZE) if (i == B_SIZE - 1 || board[i + 1][column] || board[i + 1][column + 1]) {
                board[i][column] = board[i][column + 1] = board[i - 1][column] = 1;
                break;
            }
            break;
        case 7:
            FOR(i, 1, B_SIZE) if (i == B_SIZE - 1 || board[i + 1][column] || board[i + 1][column + 1]) {
                board[i][column] = board[i][column + 1] = board[i - 1][column + 1] = 1;
                break;
            }
            break;
        case 8:
            FOR(i, 1, B_SIZE) if (i == B_SIZE - 1 || board[i + 1][column] || board[i][column + 1]) {
                board[i][column] = board[i - 1][column] = board[i - 1][column + 1] = 1;
                break;
            }
            break;
        case 9:
            FOR(i, 1, B_SIZE) if (i == B_SIZE - 1 || board[i][column] || board[i + 1][column + 1]) {
                board[i - 1][column] = board[i][column + 1] = board[i - 1][column + 1] = 1;
                break;
            }
            break;
    }

    vector<vector<bool>> ret;
    while (board.size()) {
        if (find(board.back().begin(), board.back().end(), 0) != board.back().end()) ret.push_back(board.back());
        board.pop_back();
    }
    while (ret.size() < B_SIZE) ret.push_back(vector<bool>(B_SIZE));
    reverse(ret.begin(), ret.end());

    return ret;
}

void print_board(vector<vector<bool>> board) {
    FOR(i, 0, B_SIZE) {
        FOR(j, 0, B_SIZE) cerr << board[i][j];
        cerr << '\n';
    }
}

double heuristic(vector<vector<bool>> board) {
    // 1: Fewer used blocks is good
    // 2: Lower highest column is good
    // 3: Lower average consecutive difference is good
    // 4: Fewer unused blocks with a used block above is good
    double height_sum = 0, height_diff_sum = 0, prev_h;
    FOR(j, 0, B_SIZE) {
        bool has_used = false;
        FOR(i, 0, B_SIZE) {
            if (board[i][j] && !has_used) {
                height_sum += (B_SIZE - i) * (B_SIZE - i);
                if (i) height_diff_sum += (B_SIZE - i - prev_h) * (B_SIZE - i - prev_h);
                prev_h = B_SIZE - i;
            }
            has_used |= board[i][j];
        }
    }
    return -height_sum * height_diff_sum;
}

int p[100000];

pair<double, int> search(vector<vector<bool>> board, int idx, int level) {
    pair<double, int> opt = {-1e18, -1};
    FOR(i, 0, B_SIZE) {
        if (can_place(board, p[idx], i)) {
            if (!level) opt = max(opt, {heuristic(place_piece(board, p[idx], i)), i});
            else opt = max(opt, search(place_piece(board, p[i], i), idx + 1, level - 1));
        }
    }
    return opt;
}

int main() {
    int n;
    cin >> n;
    FOR(i, 0, n) cin >> p[i];

    vector<vector<bool>> board(B_SIZE, vector<bool>(B_SIZE));
    FOR(i, 0, n) {
        pair<double, int> opt = search(board, i, min(4, n - 1 - i));

        if (opt.second == -1) {
            print_board(board);
            return cerr << "SCORE: " << i << '\n', 0;
        }

        board = place_piece(board, p[i], opt.second);
        cout << opt.second + 1 << '\n';
        // print_board(board);
    }
    return 0;
}

/*
20
5 4 1 6 7 6 4 4 7 9 5 5 6 8 3 4 3 7 4 2
*/