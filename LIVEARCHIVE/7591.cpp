/*
    Author : manu_sy
    
    Idea : mx[i], mn[i] denotes the maximum, minimum index from which ith line is reachable
           ans[i] = mx[i] - mn[i] + 1
           
           In increasing order of x, just keep updating values for y and y+1
*/
#include <bits/stdc++.h>
using namespace std;

/** Template Begins **/
#define IOS         ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl        '\n'
/** Template Ends **/

const int MAXN = 2e5+7;
int n, m, mx[MAXN], mn[MAXN];
pair<int, int> p[MAXN];

signed main() {

    IOS;
    while (cin >> n >> m)
    {
        for (int i = 1; i <= n; i++) mx[i] = mn[i] = i;

        for (int i = 0; i < m; i++) cin >> p[i].first >> p[i].second;
        sort(p, p+m);

        for (int i = 0; i < m; i++)
        {
            int x = p[i].first, y = p[i].second;

            mx[y] = mx[y+1] = max(mx[y], mx[y+1]);
            mn[y] = mn[y+1] = min(mn[y], mn[y+1]);
        }

        for (int i = 1; i <= n; i++) {
            if (i-1) cout << " ";
            cout << mx[i] - mn[i] + 1;
        } cout << endl;
    }

    return 0;
}
