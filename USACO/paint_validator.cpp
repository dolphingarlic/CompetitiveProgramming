#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <unordered_set>
#include <vector>

using namespace std;

#define GET_MACRO(_0, _1, _2, _3, NAME, ...) NAME

#define fail2(msg, line)                                           \
    do {                                                           \
        const char* _msg = (msg);                                  \
        if (_msg) {                                                \
            cout << "fail[line  " << line << "] " << _msg << endl; \
        } else {                                                   \
            cout << "fail[line " << line << "]" << endl;           \
        }                                                          \
        exit(1);                                                   \
    } while (0)

#define fail1(msg) fail2((msg), __LINE__)

#define fail0() fail2(NULL, __LINE__)

#define fail(...) \
    GET_MACRO(_0, _1, ##__VA_ARGS__, fail2, fail1, fail0)(__VA_ARGS__)

#define fassert3(cond, msg, line) \
    do {                          \
        if (!(cond)) {            \
            fail((msg), (line));  \
        }                         \
    } while (0)

#define fassert2(cond, msg) fassert3(cond, msg, __LINE__)

#define fassert1(cond) fassert3(cond, NULL, __LINE__)

#define fassert(...) \
    GET_MACRO(_0, ##__VA_ARGS__, fassert3, fassert2, fassert1)(__VA_ARGS__)

// void fail(const char* msg = NULL) {
// 	if (msg) {
// 		cout << "fail: " << msg << endl;
// 	} else {
// 		cout << "fail" << endl;
// 	}
// 	exit(1);
// }

// void fassert(bool cond, const char* msg = NULL) {
// 	if (!cond) {
// 		fail(msg);
// 	}
// }

struct input {
    input(FILE* f) : uch(-2), fin(f), sin(NULL) {}
    input(istream& in) : uch(-2), fin(NULL), sin(&in) {}

    int get() {
        if (uch != -2) {
            int ch = uch;
            uch = -2;
            return ch;
        } else if (fin) {
            return fgetc(fin);
        }
        return sin->get();
    }

    void unget(int ch) { uch = ch; }

    char get_char() {
        int ch = get();
        if (ch == -1) {
            fail("expected char");
        } else if (ch != '\n' && (ch < 32 || 126 < ch)) {
            fail("expected printable ascii");
        }
        return ch;
    }

    void get_eof() { fassert(get() == -1, "expected eof"); }

    void get_eol() { fassert(get() == '\n', "expected eol"); }

    void get_space() { fassert(get() == ' ', "expected space"); }

    void get_spaces() {
        int ch;
        get_space();
        for (ch = get(); ch == ' '; ch = get())
            ;
        unget(ch);
    }

    string get_token() {
        int ch;
        string res;
        for (ch = get(); ch != -1 && ch != '\n' && ch != ' '; ch = get()) {
            res += (char)ch;
        }
        fassert(!res.empty(), "expected token");
        unget(ch);
        return res;
    }

    long long get_int(long long min, long long max) {
        string tok = get_token();
        long long res = atoll(tok.c_str());
        fassert(tok == to_string(res), "expected int");
        fassert(min <= res && res <= max, "int out of range");
        return res;
    }

    string get_line(int min_length, int max_length) {
        int ch;
        string res;
        for (ch = get(); ch != -1 && ch != '\n'; ch = get()) {
            res += (char)ch;
            fassert(res.size() <= max_length, "line too long");
        }
        fassert(min_length <= res.size(), "line too short");
        unget(ch);
        return res;
    }

    int uch;
    FILE* fin;
    istream* sin;
};

vector<int> get_test_case_batches(int argc, char** argv) {
    vector<int> res;
    if (argc < 3) {
        return res;
    }

    int test_id = atoi(argv[1]);
    if (test_id == 0) {
        return res;
    }

    int batch = 0;
    ifstream fscorer_in(argv[2]);
    for (string ln; getline(fscorer_in, ln);) {
        if (ln.empty() || ln[0] == '#') {
            continue;
        }
        for (char& c : ln)
            if (c == ',') c = ' ';
        int sppos = ln.find(' ');
        if (sppos == string::npos) {
            continue;
        }
        istringstream sin(ln.substr(sppos + 1));

        for (string part; sin >> part;) {
            int dash = part.find('-');
            if (dash == string::npos) {
                int num = atoi(part.c_str());
                if (num == test_id) {
                    res.push_back(batch);
                    break;
                }
            } else {
                int lo = atoi(part.substr(0, dash).c_str());
                int hi = atoi(part.substr(dash + 1).c_str());
                if (lo <= test_id && test_id <= hi) {
                    res.push_back(batch);
                    break;
                }
            }
        }
        batch++;
    }
    return res;
}

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<pi> vpi;

#define f first
#define s second
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rsz resize
#define bk back()
#define pb push_back
#define ins insert

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define trav(a, x) for (auto& a : x)

const int MOD = 1e9 + 7;

template <class T>
bool ckmin(T& a, const T& b) {
    return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T& a, const T& b) {
    return a < b ? a = b, 1 : 0;
}

struct DSU {
    vi e;
    void init(int n) { e = vi(n, -1); }
    int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
    bool sameSet(int a, int b) { return get(a) == get(b); }
    int size(int x) { return -e[get(x)]; }
    bool unite(int x, int y) {  // union-by-rank
        x = get(x), y = get(y);
        if (x == y) return 0;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y];
        e[y] = x;
        return 1;
    }
};

input in(cin);

#define gi(a, b) in.get_int(a, b)
#define gl(a, b) in.get_line(a, b)
#define gs() in.get_space()
#define ge() in.get_eol()
#define gt() in.get_token()

int x1[100001], y1[100001], x2[100001], y2[100001];
int xs[200001], ys[200001];
pair<int, int> events_x[200001], events_y[200001];

int main(int argc, char** argv) {
    int tc = atoi(argv[1]);  // test id
    cerr << "TEST #: " << tc << endl;

    int n, t;
    if (tc <= 4)
        n = gi(1, 1000);
    else
        n = gi(1001, 100000);
    gs();
    t = gi(1, 2);
    if ((8 <= tc && tc <= 10) || (14 <= tc && tc <= 18))
        fassert(t == 1, "T is not 1");
    else if ((11 <= tc && tc <= 13) || (19 <= tc && tc <= 23))
        fassert(t == 2, "T is not 2");
    ge();

    for (int i = 0; i < n; i++) {
        x1[i] = gi(1, 2 * n);
        gs();
        y1[i] = gi(1, 2 * n);
        gs();
        x2[i] = gi(1, 2 * n);
        gs();
        y2[i] = gi(1, 2 * n);
        ge();
        xs[2 * i] = x1[i];
        xs[2 * i + 1] = x2[i];
        ys[2 * i] = y1[i];
        ys[2 * i + 1] = y2[i];
        events_y[x1[i]] = {y1[i], y2[i]};
        events_y[x2[i]] = {y1[i], y2[i]};
        events_x[y1[i]] = {x1[i], x2[i]};
        events_x[y2[i]] = {x1[i], x2[i]};
    }
    in.get_eof();

    // Validate permutation
    sort(xs, xs + 2 * n);
    sort(ys, ys + 2 * n);
    for (int i = 0; i < 2 * n; i++) {
        fassert(xs[i] == i + 1, "x's don't form a permutation");
        fassert(ys[i] == i + 1, "y's don't form a permutation");
    }

    // Validate subtask-specific conditions
    if (5 <= tc && tc <= 7) {
        // Check no intersecting
        set<int> active_x, active_y;
        for (int i = 1; i <= 2 * n; i++) {
            if (active_x.count(events_x[i].first)) {
                fassert(*active_x.upper_bound(events_x[i].first) ==
                            events_x[i].second,
                        "Rectangles intersect");
                active_x.erase(events_x[i].first);
                active_x.erase(events_x[i].second);
            } else {
                active_x.insert(events_x[i].first);
                active_x.insert(events_x[i].second);
                fassert(*active_x.upper_bound(events_x[i].first) ==
                            events_x[i].second,
                        "Rectangles intersect");
            }
            if (active_y.count(events_y[i].first)) {
                fassert(*active_y.upper_bound(events_y[i].first) ==
                            events_y[i].second,
                        "Rectangles intersect");
                active_y.erase(events_y[i].first);
                active_y.erase(events_y[i].second);
            } else {
                active_y.insert(events_y[i].first);
                active_y.insert(events_y[i].second);
                fassert(*active_y.upper_bound(events_y[i].first) ==
                            events_y[i].second,
                        "Rectangles intersect");
            }
        }
    } else if (8 <= tc && tc <= 13) {
        // TODO: Check all intersecting
    }

    cerr << "VALIDATED!" << endl;
}
