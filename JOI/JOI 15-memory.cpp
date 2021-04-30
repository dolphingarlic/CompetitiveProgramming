/*
JOISC 2015 Memory
- Notice how 101 * 101 * 101 * 2 * 2 is just less than 2^22 - 1
- Let's check whether each closing bracket is matched correctly
- The trick is that we don't only do this forwards - we also
  do it in reverse
    - This works because even if the bracket sequence is like
      <<<<<
      and the forward algorithm deems it correct, it's like
      >>>>>
      in reverse and the reverse algorithm will deem it incorrect
- We can achieve this by storing the following values in memory:
    - The direction of our algorithm
    - The bracket type of the closing bracket we're checking
    - The left and right endpoints of the "window" we're checking
    - The "balance" of the window
- This runs in O(N^2) and uses just enough bits of memory
*/

#include "Memory_lib.h"

int serialize(int direction, int brace_type, int lptr, int rptr, int balance) {
    int ans = 0;
    ans += balance; ans *= 101;
    ans += rptr; ans *= 101;
    ans += lptr; ans <<= 1;
    ans += brace_type; ans <<= 1;
    ans += direction;
    return ans;
}

int Memory(int N, int M) {
    int direction = M & 1;
    M >>= 1;
    int brace_type = M & 1;
    M >>= 1;
    int lptr = M % 101;
    M /= 101;
    int rptr = M % 101;
    M /= 101;
    int balance = M;

    if (lptr > rptr || lptr > N || rptr > N || balance > N) // Sanity check
        return -2;

    if (lptr == rptr) {
        if (lptr == N) // End of the string -- it's good
            return -2 * direction + 1;
        
        char c;
        if (direction) c = Get(N - lptr);
        else c = Get(lptr + 1);

        if ((c == '<' || c == '[') ^ direction) // Opening brace -- don't do anything
            return serialize(direction, 0, lptr + 1, rptr + 1, 0);
        // Closing brace -- find its match
        if (!lptr) return -2;
        return serialize(direction, (c == '[' || c == ']'), lptr - 1, rptr, 1);
    } else {
        if (!balance) return -2;

        char c;
        if (direction) c = Get(N - lptr);
        else c = Get(lptr + 1);

        balance -= 2 * ((c == '<' || c == '[') ^ direction) - 1;

        if (balance) {// We still have characters left to check
            if (!lptr) return -2;
            return serialize(direction, brace_type, lptr - 1, rptr, balance);
        }

        if ((c == '<' || c == '>') ^ brace_type) // We've found the match
            return serialize(direction, 0, rptr + 1, rptr + 1, 0);
        return -2;
    }
}
