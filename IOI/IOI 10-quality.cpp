#include "quality.h"

int lg[3001][3001], pref[3001][3001];

bool check(int median, int R, int C, int H, int W, int Q[3001][3001]) {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (Q[i][j] > median) lg[i + 1][j + 1] = 1;
			else if (Q[i][j] == median) lg[i + 1][j + 1] = 0;
			else lg[i + 1][j + 1] = -1;

			pref[i + 1][j + 1] = lg[i + 1][j + 1] + pref[i + 1][j] + pref[i][j + 1] - pref[i][j];
		}
	}

	for (int i = H; i <= R; i++) {
		for (int j = W; j <= C; j++) {
			if (pref[i][j] + pref[i - H][j - W] - pref[i][j - W] - pref[i - H][j] <= 0) return true;
		}
	}
	return false;
}

int rectangle(int R, int C, int H, int W, int Q[3001][3001]) {
	int l = 1, r = R * C;
	while (l != r) {
		int mid = (l + r) / 2;
		if (check(mid, R, C, H, W, Q)) r = mid;
		else l = mid + 1;
	}
	return l;
}