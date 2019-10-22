/*
    Author : manu_sy
    
    Idea : same as 
    https://github.com/BRAINOOOO/CompetitiveProgramming/blob/master/TIMUS/TIMUS%201752
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

const int N = 2e4+7;

/** Template Ends **/
int n, q, up[N][20], l, L[N], h[N], last[N];
vector<int> g[N];
pair<int, PII> dia;

void dfs(int v, int p, int lvl)
{
    L[v] = lvl;
    up[v][0] = p;
    for (int i = 1; i <= l; i++)
        up[v][i] = up[up[v][i-1]][i-1];

    PII mx1 = mp(-1, -1), mx2 = mp(-1, -1);
    for (auto nb : g[v]) 
        if (nb != p)
        {
            dfs(nb, v, lvl + 1);
            PII hnb = mp(h[nb], last[nb]);
            if (hnb > mx1) mx2 = mx1, mx1 = hnb;
            else if (hnb > mx2) mx2 = hnb;
        }

    if (mx1 == mp(-1, -1))
    {
        auto cur_dia = mp(1, mp(v, v));
        dia = max(dia, cur_dia);
        h[v] = 1;
        last[v] = v;
    }
    else if (mx2 == mp(-1, -1))
    {
        auto cur_dia = mp(mx1.F + 1, mp(v, mx1.S));
        dia = max(dia, cur_dia);
        h[v] = mx1.F + 1;
        last[v] = mx1.S;
    }
    else 
    {
        auto cur_dia = mp(mx1.F + mx2.F + 1, mp(mx1.S, mx2.S));
        dia = max(dia, cur_dia);
        h[v] = mx1.F + 1;
        last[v] = mx1.S;
    } 
}
int walk(int u, int k) 
{
    for (int i = l; i >= 0; i--)
        if ((k>>i)&1)
            u = up[u][i];
    return u;
}
int lca(int u, int v) 
{
    if (L[u] < L[v]) swap(u, v);
    u = walk(u, L[u]-L[v]);
    if (u == v) return u;

    for (int i = l; i >= 0; i--)
        if (up[u][i] != up[v][i])
            u = up[u][i], v = up[v][i];
    return up[u][0];
}
int dist(int a, int b) {
    return L[a] + L[b] - 2 * L[lca(a, b)];
}

signed main() {

    IOS;
    cin >> n >> q;
    LP(i,n-1)
    {
        int a, b;   cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    dia = mp(-1, mp(-1, -1));
    l = ceil(log2(n));
    dfs(1,1,0);

    //debug(dia);
    while (q--)
    {
        int v, d;   cin >> v >> d;
        int d1 = dist(v, dia.S.F);
        int d2 = dist(v, dia.S.S);

        if (d <= d1)
        {
            int lc = lca(v, dia.S.F);
            if (d <= L[v] - L[lc])  cout << walk(v, d) << endl;
            else                    cout << walk(dia.S.F, d1 - d) << endl;
        }
        else if (d <= d2)
        {
            int lc = lca(v, dia.S.S);
            if (d <= L[v] - L[lc])  cout << walk(v, d) << endl;
            else                    cout << walk(dia.S.S, d2 - d) << endl;
        }
        else 
        {
            cout << 0 << endl;
        }
    }

    return 0;
}
