/*
    Author : manu_sy
    
    Idea : The queries are like this :
          1. A series of edge additions to tree
          2. A series of queries of type is_ancestor(yi, x) where x is fixed
          3. Repeat 1 and 2
          
          So we just do it like this :
          - keep a counter cur that denotes how many documents packet queries (of type 2.)
          - when add edge - add edge of weight cur
          - to answer a query we just need to know if the maximum edge between path x to ancestor y is less than the counter of x, 
            which can be done easily using lca
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
int n, m, up[N][22], mx[N][22], l, L[N], x[N];
vector<PII> q[N];

int lvl(int u) {
    if (L[u] != -1) return L[u];
    if (up[u][0] == -1) return L[u] = 0;
    return L[u] = lvl(up[u][0]) + 1;
}

int get(int u, int v)
{
    if (lvl(u) < lvl(v))    return -1;
    int mxh = -1;
    for (int i = l; i >= 0; i--)
        if (((lvl(u) - lvl(v)) >> i) & 1)
            mxh = max(mxh, mx[u][i]),
            u = up[u][i];
    if (u != v) return -1;
    return mxh;
}

signed main() {

    IOS;
    cin >> n >> m;

    int cur = 0;
    memset(up, -1, sizeof up);
    memset(L, -1, sizeof L);
    memset(mx, -1, sizeof mx);
    LP(i,m)
    {
        int t, a, b, id;    cin >> t;
        if (t == 1)
        {
            cin >> a >> b;
            up[a][0] = b;
            mx[a][0] = cur;
        }
        else if (t == 2)
        {
            cin >> a;
            x[cur++] = a;
        }
        else if (t == 3)
        {
            cin >> a >> id;
            id--;
            q[id].pb(mp(a, i));
        }
    }
    l = ceil(log2(n));
    for (int j = 1; j <= l; j++)
        for (int i = 1; i <= n; i++)
            if (up[i][j-1] != -1)
                up[i][j] = up[up[i][j-1]][j-1],
                mx[i][j] = max(mx[i][j-1], mx[up[i][j-1]][j-1]);

    vector<pair<int, string> > ans;
    for (int i = 0; i < cur; i++)
    {
        //debug(i, q[i]);
        for (auto yf : q[i])
        {
            int y = yf.F;
            int mxh = get(x[i], y);
            //debug(i, x[i], y, mxh);
            if ((mxh != -1 && mxh <= i) || x[i] == y)   ans.pb(mp(yf.S, "YES"));
            else ans.pb(mp(yf.S, "NO"));
        }
    }
    sort(all(ans));
    for (auto i : ans) cout << i.S << endl;

    return 0;
}
