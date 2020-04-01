/*
    Author : manu_sy
    Idea : Lexicographically shortest euler tour.
         - Idea same as https://github.com/quangloc99/CompetitiveProgramming/blob/master/UVA/10040.cpp
*/
#include "bits/stdc++.h"
using namespace std;
 
/** Template Begins **/
 
typedef long long        ll;
typedef pair<int,int>    PII;
 
#define IOS         ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl        '\n'
#define pb          push_back
#define F           first
#define S           second
#define mp          make_pair
#define all(a)      (a).begin(), (a).end()
#define FOR(i,a,b)  for(int i=a;i<=b;i++)
#define LP(i,n)     for(int i=0;i< n;i++)
 
/* Debug */
 
template<class L, class R> ostream &operator<<(ostream &os, pair<L,R> P) {
  return os << "(" << P.F << "," << P.S << ")";
} 
 
template<class T> ostream &operator<<(ostream& os, vector<T> V) {
  os << "["; for (auto vv : V) os << vv << ","; return os << "]";
}
 
template<class TH> void _dbg(const char *sdbg, TH h){ cerr << sdbg << '=' << h << endl; }
 
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
  while(*sdbg!=',') cerr << *sdbg++;
  cerr<<'='<<h<<','; _dbg(sdbg+1, a...);
}
 
#ifdef LOCAL
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif
 
/* Debug Ends */
 
const int N = 22+3;
 
/** Template Ends **/

vector<int> ans[N];
 
vector<vector<PII> > de_brujin_graph(int length) 
{
    int n = (1 << length);
    int tmask = n - 1;
    vector<vector<PII> > g(n);
    LP(i, n) for (int j = 1; j >= 0; j--) {
        g[i].pb({((i << 1) + j) & tmask, j});
    }
    return g;
}
list<PII> dfs(int v, vector<vector<PII> >& g)
{
    list<PII> ans;
    while (g[v].size()) 
    {
        ans.push_front(g[v].back());
        g[v].pop_back();
        v = ans.front().F;
    }

    for (auto it = ans.begin(); it != ans.end(); it++) {
        ans.splice(it, dfs((*it).F, g));
    }
    return ans;
}
list<PII> euler_dir(vector<vector<PII> > g, int start)
{
    auto ans = dfs(start, g);
    reverse(all(ans));
    return ans;
}

signed main() {
 
    IOS;
    int t;  cin >> t;
    while (t--)
    {
        int n, k;   cin >> n >> k;
        if (ans[n].size() == 0)
        {
            auto s = euler_dir(de_brujin_graph(n - 1), 0);
            LP(i, n - 1) s.push_front({0, 0});
            for (auto i: s) ans[n].pb(i.S);
        }
        int ret = 0;
        LP(i,n) {
            ret |= ((1 & ans[n][(k + i)]) << (n - 1 - i));
        }
        cout << ret << endl;
    }
 
    return 0;
}
