/*
IOI 2004 Empodia
- Let gr[i] be the first element to the left of i such that a[gr[i]] > a[i]
- Let le[i] be the first element to the right of i such that a[le[i]] < a[i]
- We can find gr and le with a monotone stack
- Criteria for a framed sequence (l, r):
    - gr[r] < l
    - le[l] > r
    - a[l] - l == a[r] - r
- If we group the numbers by a[i] - i, we can find the potential empodia in each
group
- For each group, process it in decreasing order of index and maintain a stack
of potential endpoints (active)
- For some i we're checking:
    - If le[i] < active.top(), there can be no empodio starting on i, so we
break
    - If gr[active.top()] > i, active.top() can never be the end of an empodio
again, so we pop it from the stack
    - Otherwise, (i, active.top()) is a potential empodio
- Now we can just find which empodia don't contain others
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
using namespace std;

int a[2000000], le[2000000], gr[2000000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    map<int, stack<int>> mp;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mp[a[i] - i].push(i);
    }
    stack<int> stck;
    for (int i = 0; i < n; i++) {
        while (stck.size() && a[stck.top()] < a[i]) stck.pop();
        if (stck.size())
            gr[i] = stck.top();
        else
            gr[i] = -1;
        stck.push(i);
    }
    while (stck.size()) stck.pop();
    for (int i = n - 1; ~i; i--) {
        while (stck.size() && a[stck.top()] > a[i]) stck.pop();
        if (stck.size())
            le[i] = stck.top();
        else
            le[i] = n;
        stck.push(i);
    }

    vector<pair<int, int>> potential, empodia;
    for (pair<int, stack<int>> i : mp) {
        stack<int> active;
        while (i.second.size()) {
            while (active.size()) {
                if (le[i.second.top()] < active.top()) break;
                if (gr[active.top()] > i.second.top())
                    active.pop();
                else {
                    potential.push_back({i.second.top(), active.top()});
                    break;
                }
            }
            active.push(i.second.top());
            i.second.pop();
        }
    }

    sort(potential.begin(), potential.end(), greater<pair<int, int>>());
    for (pair<int, int> i : potential)
        if (!empodia.size() || empodia.back().second > i.second)
            empodia.push_back(i);

    cout << empodia.size() << '\n';
    while (empodia.size()) {
        cout << empodia.back().first + 1 << ' ' << empodia.back().second + 1 << '\n';
        empodia.pop_back();
    }
    return 0;
}