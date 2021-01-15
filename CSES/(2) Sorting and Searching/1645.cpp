#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
 
int a[200001];
 
int main() {
    int n;
    scanf("%d", &n);
    stack<int> stck;
    stck.push(0);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        while (a[i] <= a[stck.top()]) stck.pop();
        printf("%d ", stck.top());
        stck.push(i);
    }
    return 0;
}