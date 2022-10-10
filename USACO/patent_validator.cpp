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
#include <numeric>

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

input in(cin);

#define gi(a, b) in.get_int(a, b)
#define gl(a, b) in.get_line(a, b)
#define gs() in.get_space()
#define ge() in.get_eol()
#define gt() in.get_token()

const int MAX_AB = 1e9;
const int MAX_NK = 2e3;

int a[2000], b[2000], cmp1[2000], cmp2[2000], adj_a[2000], adj_b[2000];

int find(int A, int* cmp) { return cmp[A] = (A == cmp[A] ? A : find(cmp[A], cmp)); }
void onion(int A, int B, int* cmp) { cmp[find(A, cmp)] = find(B, cmp); }

int main(int argc, char** argv) {
    int tc = atoi(argv[1]);  // test id
    cerr << "TEST #: " << tc << endl;

    int n = gi(1, MAX_NK);
    gs();
    int k = gi(1, MAX_NK);
    ge();

    for (int i = 0; i < n; i++) {
        a[i] = gi(1, MAX_AB);
        if (i == n - 1) ge();
        else gs();
    }
    for (int i = 0; i < n; i++) {
        b[i] = gi(1, MAX_AB);
        if (i == n - 1) ge();
        else gs();
    }

    iota(cmp1, cmp1 + n, 0);
    for (int i = 1; i < n; i++) {
        int u = gi(1, n) - 1;
        gs();
        int v = gi(1, n) - 1;
        ge();
        onion(u, v, cmp1);
        adj_a[u]++;
        adj_a[v]++;
        fassert(adj_a[u] <= 5 && adj_a[v] <= 5, "More than 5 nodes adjacent to one node in A");
    }
    for (int i = 1; i < n; i++) {
        fassert(find(i, cmp1) == find(0, cmp1), "Given graph isn't a tree for A");
    }
    iota(cmp2, cmp2 + n, 0);
    for (int i = 1; i < n; i++) {
        int u = gi(1, n) - 1;
        gs();
        int v = gi(1, n) - 1;
        ge();
        onion(u, v, cmp2);
        adj_b[u]++;
        adj_b[v]++;
        fassert(adj_b[u] <= 5 && adj_b[v] <= 5, "More than 5 nodes adjacent to one node in B");
    }
    for (int i = 1; i < n; i++) {
        fassert(find(i, cmp2) == find(0, cmp2), "Given graph isn't a tree for B");
    }

#ifndef LOCAL
    const int NUM_BATCHES = 4;
    vector<int> batches = get_test_case_batches(argc, argv);
    cerr << "BATCHES: {";
    for (int i = 0; i < (int)batches.size(); ++i) {
        if (i) cerr << ", ";
        fassert(0 <= batches[i] && batches[i] < NUM_BATCHES,
                "invalid batching");
        cerr << batches[i];
    }
    cerr << "}\n";
    for (int batch = 0; batch < NUM_BATCHES; ++batch) {
        bool contains_batch = find(all(batches), batch) != end(batches);
        bool calc_batch = 1;
        // modify calc_batch below to actually check whether test is in batch
        if (batch == 0)
            calc_batch = (n <= 200 && k == 1 && *max_element(a, a + n) == 1 && *max_element(b, b + n) == 1);
        else if (batch == 1)
            calc_batch = (n <= 200 && k == 1);
        else if (batch == 2)
            calc_batch = (n <= 200 && k <= 200);
        fassert(calc_batch == contains_batch);
    }
#endif

    in.get_eof();
    cerr << "VALIDATED!" << endl;
}
