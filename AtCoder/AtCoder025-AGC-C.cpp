/*
    Author : manu
    Idea : Just go to the leftmost interval and then to rightmost point and continue like this.
          - Check starting from rightmost also
*/

#include "bits/stdc++.h"
using namespace std;
 
/** Template Begins **/

#define ll          long long 
#define IOS         ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl        '\n'
 
const int N = 5e6+7;

/** Template Ends **/
using pii = pair<int, int>;

ll solve(multiset<pii> lf, multiset<pii> rt, int mv)
{
    int cur = 0;
    ll ans = 0;
    for (; rt.size(); mv++)
    {
        if (mv & 1)
        {
            pii p = *rt.rbegin();    rt.erase(rt.find(p));   lf.erase(lf.find({p.second, p.first}));
            ans += max(0, p.first - cur);
            cur = max(cur, p.first);
        }
        else
        {
            pii p = *lf.begin();    lf.erase(lf.find(p));   rt.erase(rt.find({p.second, p.first}));
            ans += max(0, cur - p.first);
            cur = min(cur, p.first);
        }
    }
    ans += abs(cur);
    return ans;
}

signed main() 
{ 
    IOS;
    int n;  cin >> n;
    multiset<pii> rt, lf;

    for (int i = 0; i < n; i++)
    {
        int x, y;   cin >> x >> y;
        rt.insert({x, y});
        lf.insert({y, x});
    }
    cout << max(solve(lf, rt, 0), solve(lf, rt, 1)) << endl;

    return 0;
}
