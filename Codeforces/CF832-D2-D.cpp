/*
    Author : manu_sy
    
    Idea : There are 3 cases when analysing common in s->f & t->f path :
          1. lca(s,f) == lca(s,t) : ans is dist(lca(f,t), f)
          2. lca(f,s) == lca(f,t) : ans is dist(lca(f,t), f)
          3. lca(t,f) == lca(t,s) : ans is dist(lca(s,f), f)
          Just find for all possible combinations.
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
#ifdef LOCALI
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif
/* Debug Ends */

const int N = 1e5+7;
const int ML = 22;

/** Template Ends **/
int n, p[N], q;
vector<int> g[N];

int up[N][ML], l, lvl[N];

int walk(int v, int k) {
    for (int i = l; i >= 0; i--)
        if ((k>>i)&1)
            v = up[v][i];
    return v;
}
int L(int v) {
    if (lvl[v] != -1)   return lvl[v];
    return lvl[v] = L(p[v]) + 1;
}
int LCA(int u, int v) {
    if (L(u) < L(v)) swap(u, v);
    if (L(u) > L(v)) u = walk(u, L(u) - L(v));
    if (u == v) return u;

    for (int i = l; i >= 0; i--)
        if (up[u][i] != up[v][i])
            u = up[u][i], v = up[v][i];
    return up[u][0];
}
int dist(int u, int v) {
    return L(u) + L(v) - 2*L(LCA(u,v)) + 1;
}
int calc(int s, int f, int t) {
    if (LCA(f, s) == LCA(f, t)) return dist(LCA(s, t), f);
    else if (LCA(s, f) == LCA(s, t)) return dist(LCA(f,t), f);
    else if (LCA(t, f) == LCA(t, s)) return dist(LCA(s, f), f);
    else assert(false);
}

signed main() {

    IOS;
    cin >> n >> q;
    FOR(i,2,n)  cin >> p[i], up[i][0] = p[i];
    l = ceil(log2(n));
    memset(lvl, -1, sizeof lvl);

    lvl[1] = 0;    
    up[1][0] = 1;
    for (int j = 1; j <= l; j++)
        for (int i = 1; i <= n; i++)
            up[i][j] = up[up[i][j-1]][j-1];

    while (q--)
    {
        int a[3];   cin >> a[0] >> a[1] >> a[2];
        sort(a, a+3);
        vector<pair<PII,int> > v;
        do {
            v.pb(mp(mp(a[0], a[1]), a[2]));
        } while (next_permutation(a, a+3));
        sort(all(v));
        v.resize(unique(all(v))-v.begin());

        int mx = 0;
        for (auto i : v) {
            int cur = calc(i.F.F, i.F.S, i.S);
            mx = max(mx, cur);
        }
        cout << mx << endl;
    }
    return 0;
}
