#include "testlib.h" 
using namespace std;
 
int n;
long long dp[200][200][400];
 
readAndCheckAnswer(InStream& in) {
    int h = in.readInt(1, 200);
    int w = in.readInt(1, 200);
    dp[0][0][1] = 1;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            char c = in.readChar();
            if (c == '+') {
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
        in.quitf(_wa, "Wrong number of paths: expected %d but got %d, h=%d w=%d", n, dp[h - 1][w - 1][0], h, w);
}
 
int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    n = inf.readInt();
    readAndCheckAnswer(ouf);
    quitf(_ok, "n=%d", n);
}
