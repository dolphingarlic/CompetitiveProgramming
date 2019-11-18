#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const int n = 100;
int s_idx = 0, s_len;
char s[200];
double ans;

struct Window {
    int x1, y1, x2, y2, area;
    Window(int a, int b, int c, int d) {
        x1 = a < c ? a : c;
        x2 = a > c ? a : c;
        y1 = b < d ? b : d;
        y2 = b > d ? b : d;
        area = abs(a - c) * abs(b - d);
    }
};

Window *w[n];

class Qu {
   public:
    int size, idx[n];
    Qu() { size = 0; }
    int locate(int cur);
    void insert(int cur);
    void remove(int cur);
    void top(int cur);
    void bottom(int cur);
} q;
int Qu::locate(int cur) {
    for (int i = 1; i <= size; i++)
        if (idx[i] == cur) return i;
    return 0;
}
void Qu::insert(int cur) {
    size++;
    for (int i = size; i > 1; i--) idx[i] = idx[i - 1];
    idx[1] = cur;
}
void Qu::remove(int cur) {
    int i = locate(cur);
    if (i == 0) return;
    while (i < size) {
        idx[i] = idx[i + 1];
        i++;
    }
    size--;
}
void Qu::top(int cur) {
    int i = locate(cur);
    while (i > 1) {
        idx[i] = idx[i - 1];
        i--;
    }
    idx[1] = cur;
}
void Qu::bottom(int cur) {
    int i = locate(cur);
    while (i < size) {
        idx[i] = idx[i + 1];
        i++;
    }
    idx[size] = cur;
}

int get_id(char c) {
    if (c >= '0' && c <= '9') return c - '0' + 1;
    if (c >= 'a' && c <= 'z') return c - 'a' + 11;
    return c - 'A' + 37;
}
int get_num() {
    int res = 0;
    while (s_idx < s_len && s[s_idx] >= '0' && s[s_idx] <= '9') {
        res = 10 * res + s[s_idx] - '0';
        s_idx++;
    }
    s_idx++;
    return res;
}

void float_up(int k, int x1, int y1, int x2, int y2) {
    while (k > 0 && (y1 >= w[q.idx[k]]->y2 || y2 <= w[q.idx[k]]->y1 ||
                     x1 >= w[q.idx[k]]->x2 || x2 <= w[q.idx[k]]->x1))
        k--;
    if (k == 0) {
        ans += abs(x2 - x1) * abs(y2 - y1);
        return;
    }
    if (y2 > w[q.idx[k]]->y2) {
        float_up(k - 1, x1, max(y1, w[q.idx[k]]->y2), x2, y2);
        y2 = w[q.idx[k]]->y2;
    }
    if (y1 < w[q.idx[k]]->y1) {
        float_up(k - 1, x1, y1, x2, min(y2, w[q.idx[k]]->y1));
        y1 = w[q.idx[k]]->y1;
    }
    if (x1 < w[q.idx[k]]->x1)
        float_up(k - 1, x1, y1, min(x2, w[q.idx[k]]->x1), y2);
    if (x2 > w[q.idx[k]]->x2)
        float_up(k - 1, max(x1, w[q.idx[k]]->x2), y1, x2, y2);
}

int main() {
    int a, b, c, d;
    while (!cin.eof()) {
        cin >> s;
        if (cin.eof()) break;
        int cur = get_id(s[2]);
        s_len = strlen(s);
        switch (s[0]) {
            case 'w':
                if (w[cur] != NULL) {
                    delete w[cur];
                    w[cur] = NULL;
                    q.remove(cur);
                }
                s_idx = 4;
                a = get_num();
                b = get_num();
                c = get_num();
                d = get_num();
                w[cur] = new Window(a, b, c, d);
                q.insert(cur);
                break;
            case 't':
                q.top(cur);
                break;
            case 'b':
                q.bottom(cur);
                break;
            case 'd':
                q.remove(cur);
                break;
            case 's':
                int k = q.locate(cur);
                if (k == 0)
                    ans = 0;
                else if (k == 1)
                    ans = 100;
                else {
                    ans = 0.0;
                    float_up(k - 1, w[cur]->x1, w[cur]->y1, w[cur]->x2,
                             w[cur]->y2);
                    ans = ans / w[cur]->area * 100;
                }
                cout << fixed << setprecision(3) << ans << endl;
                break;
        }
    }
    return 0;
}