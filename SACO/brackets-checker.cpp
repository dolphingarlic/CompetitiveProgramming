#include "testlib.h" 
using namespace std;
 
int n;
long long dp[200][200][400];
 
readAndCheckAnswer(InStream& in) {
    int h = in.readInt(1, 200, "h");
    int w = in.readInt(1, 200, "w");

    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            for (int k = 0; k < 400; k++)
                dp[i][j][k] = 0;
    dp[0][0][1] = 1;

    in.readEoln();
    for (int i = 0; i < h; i++) {
        string s = in.readToken("[+-]{" + to_string(w) + "}", "s");
        for (int j = 0; j < w; j++) {
            if (s[j] == '+') {
                if (i)
                    for (int k = 1; k < 400; k++)
                        dp[i][j][k] += dp[i - 1][j][k - 1];
                if (j)
                    for (int k = 1; k < 400; k++)
                        dp[i][j][k] += dp[i][j - 1][k - 1];
            } else {
                if (i)
                    for (int k = 0; k < 399; k++)
                        dp[i][j][k] += dp[i - 1][j][k + 1];
                if (j)
                    for (int k = 0; k < 399; k++)
                        dp[i][j][k] += dp[i][j - 1][k + 1];
            }
        }
    }

    if (dp[h - 1][w - 1][0] != n)
        in.quitf(_wa, "Wrong number of paths");
}
 
int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    n = inf.readInt();
    readAndCheckAnswer(ans);
    readAndCheckAnswer(ouf);
    quitf(_ok, "n=%d", n);
}
