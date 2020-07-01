/*
  Author : manu
  Idea : Think of dp[i][j] - min amount of connections such that ith leaf from main and jth from reserve is selected
       - Observe that if you are at (i,j) (assume i < j) then it is optimal to update only (i, j + 1) and (j + 1, j)
         and this can be done in O(logn) using lca.
       - Complexity - O(n^2logn)
*/

#include "bits/stdc++.h"
using namespace std;
 
/** Template Begins **/
 
typedef long long        ll;
typedef pair<int,int>    PII;
typedef vector<int>      vi;

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
 
const int N = 1e3+7;

/** Template Ends **/
struct tree {
    vector<vi> g, up;
    int n;
    int l, timer, root;
    vector<int> L, in, out;

    tree(int n, int root = 1) : n(n + 1), root(root) {
        g.resize(n + 1); L.resize(n + 1); in.resize(n + 1); out.resize(n + 1);
        up = vector<vi>(n + 1, vi(22, -1));
        timer = 0;
        l = ceil(log2(n));
    }
    void add_edge(int u, int v) {
        g[u].pb(v);
    }
    void pre_compute() {
        dfs(root, 0, 1);
    }
    void dfs(int u, int p, int lvl) {
        in[u] = ++timer;
        L[u] = lvl;
        if (p)  up[u][0] = p;

        for (int i = 1; i <= l; i++)
            if (up[u][i - 1] != -1)
                up[u][i] = up[up[u][i - 1]][i - 1];

        for (auto ch : g[u]) if (ch != p) {
            dfs(ch, u, lvl + 1);
        }
        out[u] = ++timer;
    }
    int walk(int u, int k) {
        for (int i = l; i >= 0; i--) if ((k >> i) & 1) u = up[u][i];
        return u;
    }
    int lca(int u, int v) {
        if (L[u] < L[v])    swap(u, v);
        u = walk(u, L[u] - L[v]);
        if (u == v) return u;

        for (int i = l; i >= 0; i--)
            if (up[u][i] != up[v][i])
                u = up[u][i], v = up[v][i];

        return up[u][0];
    }
    int dist(int a, int b) {
        return L[a] + L[b] - 2 * L[lca(a, b)];
    }
};
int dp[N][N];

signed main() {
 
    IOS;
    int n; cin >> n;
    int a;  cin >> a;
    tree main(a);
    FOR(i,2,a) 
    {
        int x;  cin >> x;
        main.add_edge(x, i);
    }
    vi ml(n + 1), rl(n + 1);
    FOR(i,1,n) cin >> ml[i];

    int b;  cin >> b;
    tree res(b);
    FOR(i,2,b)
    {
        int x;  cin >> x;
        res.add_edge(x, i);
    }
    FOR(i,1,n) cin >> rl[i];

    main.pre_compute();
    res.pre_compute();

    auto upd = [&](int i, int j, int i1, int j1) {
        if (i1 > n || j1 > n)   return;
        if (i != i1)
        {
            int li = (i > 0 ? ml[i] : 1);
            dp[i1][j1] = min(dp[i1][j1], dp[i][j] + main.dist(main.lca(li, ml[i1]), ml[i1]));
        }
        else
        {
            int lj = (j > 0 ? rl[j] : 1);
            dp[i1][j1] = min(dp[i1][j1], dp[i][j] + res.dist(res.lca(lj, rl[j1]), rl[j1]));
        }
        // debug(i, j, i1, j1, dp[i1][j1], dp[i][j]);
    };
    FOR(i,0,n) FOR(j,0,n) dp[i][j] = 1e8;
    dp[0][0] = 0;

    FOR(j,0,n) // leaf in res
    {
        FOR(i,0,n) // leaf in main
        {
            if (i != 0 && i == j) continue;
            if (i > j)
            {
                upd(i, j, i + 1, j);
                upd(i, j, i, i + 1);
            }
            else
            {
                upd(i, j, i, j + 1);
                upd(i, j, j + 1, j);
            }
        }
    }
    int ans = INT_MAX;

    FOR(i,0,n) ans = min(ans, min(dp[i][n], dp[n][i]));
    cout << a - 1 + b - 1 - ans << endl;
 
    return 0;
}
