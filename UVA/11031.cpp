/*
    Author : manu_sy

    Idea : 
        - For each i calculate the length of the longest increasing subsequence starting at i
        
        - Now for each query calculate answer by traversing cur from left to right
          if lis[cur] >= need && a[cur] > last_included :
             include a[cur] in ans
             last_included = a[cur]
             need--
*/
#include <bits/stdc++.h>
using namespace std;

/** Template Begins **/
#define IOS         ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl        '\n'
/** Template Ends **/

const int N = 1e4 + 7;

int n, q, m, a[N], lis[N], s[N], nxt[N], mx;

void calc_lis() {

    vector<int> v;
    v.push_back(a[n-1]), lis[n-1] = 1;
    mx = 1;

    for (int i = n-2; i >= 0; i--)
    {
        // find the position of the first element that is < a[i]
        int pos = lower_bound(v.begin(), v.end(), a[i], greater<int>()) - v.begin();
        if (pos == v.size())    
            v.push_back(a[i]);
        else 
            v[pos] = a[i];

        lis[i] = pos + 1;
        mx = max(mx, lis[i]);
    }
}

signed main() {

    IOS;
    int tc = 1;
    while (cin >> n >> q)
    {
        if (n == 0 && q == 0)   break;
        for (int i = 0; i < n; i++) cin >> a[i];

        calc_lis();

        cout << "Set " << tc++ << ":" << endl;
        for (int t = 1; t <= q; t++)
        {
            cin >> m;

            cout << "  Subset " << t << ":" << endl;
            cout << "    ";
            if (mx < m)
            {
                cout << "Impossible" << endl;
                continue;
            }

            for (int i = 0, need = m, cur = INT_MIN; i < n && need > 0; i++) 
            {
                if (lis[i] >= need && a[i] > cur)
                {
                    cur = a[i];
                    if (need != m)  cout << " ";    cout << a[i];
                    need--;
                }
            } cout << endl;
        }
    }
    
    return 0;
}
