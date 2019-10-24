/*
    Author : manu_sy
    
    Idea : Just precompute the sizes of subtree of each node with 1 as root
           - If query of type : R a - change root variable to a
           - To find sum of subtree of a, only 2 cases :
             - either the node a is not ancestor of current root : ans is subtree[a]
             - a is ancestor of current root 
                -> walk(root) upwards to a lvl of L[a]+1. Let this node be u
                -> answer is total - subtree[u]
*/
#include <bits/stdc++.h>
using namespace std;

/** Template Begins **/
#define int ll
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
int n, up[N][22], l, timer, root, in[N], out[N], L[N];
ll sz[N], w[N];
vector<int> g[N];

void dfs(int u, int p, int lvl)
{
    in[u] = timer++;
    L[u] = lvl;
    if (p) assert(up[u][0] == p);

    for (int i = 1; i <= l; i++)
        if (up[u][i-1] != -1)
            up[u][i] = up[up[u][i-1]][i-1];

    sz[u] = w[u];
    for (auto ch : g[u]) 
    {
        dfs(ch, u, lvl+1);
        sz[u] += sz[ch];
    }
    out[u] = timer++;
}
bool is_ancestor(int u, int v)
{
    return in[u] <= in[v] && out[u] >= out[v];
}
int walk(int u, int k)
{
    for (int i = l; i >= 0; i--)
        if ((k>>i)&1)
            u = up[u][i];
    return u;
}
signed main() {

    IOS;
    memset(up, -1, sizeof up);
    cin >> n;
    FOR(i,1,n) cin >> w[i];
    FOR(i,2,n) 
    {
        cin >> up[i][0];
        g[up[i][0]].pb(i);
    }

    root = 1;
    l = ceil(log2(n));
    dfs(1, 0, 0);

    int q;  cin >> q;
    while (q--)
    {
        char t; int a;  cin >> t >> a;
        if (t == 'R')
        {
            root = a;
        }
        else
        {
            if (a == root)
            {
                cout << sz[1] << endl;
            }
            else if (!is_ancestor(a, root))
            {
                cout << sz[a] << endl;
            }
            else 
            {
                int last = walk(root, L[root] - L[a] - 1);
                //debug(last);
                cout << sz[1] - sz[last] << endl;
            }
        }
    }

    return 0;
}
