import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;
 
public class ArrayOperationsHarderFasterMod {
    public static final long MOD = 1000000007;
 
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        int[] bs = new int[n + 1];
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        for (int j = 1; j <= n; j++) {
            bs[j] = Integer.parseInt(tokenizer.nextToken());
        }
        long[][] dp = new long[n + 1][1001];
        long answer = 0;
        for (int d = 0; d <= 1000; d++) {
            Arrays.fill(dp[0], 0);
            dp[0][0] = 1;
            for (int j = 1; j <= n; j++) {
                Arrays.fill(dp[j], 0);
                for (int x = 0; x <= bs[j] - d; x++) {
                    dp[j][bs[j] - d - x] = dp[j - 1][x];
                }
                for (int x = 999; x >= 0; x--) {
                    dp[j][x] += dp[j][x + 1];
                    if (dp[j][x] >= MOD) {
                        dp[j][x] -= MOD;
                    }
                }
            }
            answer += dp[n][0];
            answer %= MOD;
            if (n % 2 == 0) {
                break;
            }
        }
        System.out.println(answer);
    }
}
