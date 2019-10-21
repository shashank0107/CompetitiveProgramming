/*
    Author : manu_sy
    
    Idea : To get min/max between a,b :
          - just like finding lca, just store with each 1>>ith parent, the max and min edge till that parent
          - now when finding lca between a, b -> keep updating with max and min values
*/
#include <bits/stdc++.h>
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
template<class TH> void _dbg(const char *sdbg, TH h){ cerr<<sdbg<<'='<<h<<endl; }
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
  while(*sdbg!=',')cerr<<*sdbg++;
  cerr<<'='<<h<<','; _dbg(sdbg+1, a...);
}
#ifdef LOCAL
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif
/* Debug Ends */

const int N = 1e5+7;

/** Template Ends **/
int n, up[N][22], mx[N][22], mn[N][22], L[N], l;
vector<PII> g[N];

void dfs(int v, int p, int lvl, int e) 
{
    L[v] = lvl;
    up[v][0] = p;
    mx[v][0] = mn[v][0] = e;

    for (int i = 1; i <= l; i++)
        up[v][i] = up[up[v][i-1]][i-1],
        mx[v][i] = max(mx[v][i-1], mx[up[v][i-1]][i-1]),
        mn[v][i] = min(mn[v][i-1], mn[up[v][i-1]][i-1]);

    for (auto nb : g[v]) if (nb.F != p)
        dfs(nb.F, v, lvl+1, nb.S);
}

PII get(int u, int v) 
{
    if (u == v) return mp(0, 0);
    if (L[u] < L[v])    swap(u, v);

    int mxr = INT_MIN, mnr = INT_MAX;
    if (L[u] > L[v])
    {
        for (int i = l; i >= 0; i--)
            if (((L[u]-L[v])>>i) & 1)
                mxr = max(mxr, mx[u][i]),
                mnr = min(mnr, mn[u][i]),
                u = up[u][i];
    }
    if (u == v) return mp(mnr, mxr);

    for (int i = l; i >= 0; i--)
    {
        if (up[v][i] != up[u][i])
            mxr = max(mxr, max(mx[v][i], mx[u][i])),
            mnr = min(mnr, min(mn[v][i], mn[u][i])),
            v = up[v][i], u = up[u][i];
    }

    mxr = max(mxr, max(mx[v][0], mx[u][0]));
    mnr = min(mnr, min(mn[v][0], mn[u][0]));
    return mp(mnr, mxr);
}
signed main() {

    IOS;
    cin >> n;
    LP(i,n-1)
    {
        int a, b, c;    cin >> a >> b >> c;
        g[a].pb(mp(b, c));
        g[b].pb(mp(a, c));
    }
    l = ceil(log2(n));
    dfs(1, 1, 0, 0);

    int k;  cin >> k;
    while (k--) 
    {
        int a, b;   cin >> a >> b;
        PII res = get(a, b);
        cout << res.F << " " << res.S << endl;
    }

    return 0;
}
