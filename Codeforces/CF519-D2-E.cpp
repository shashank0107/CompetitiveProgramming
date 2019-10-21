/*
    Author : manu_sy
    
    Idea : if dd = dist(a,b) is odd then no equidistant vertices
           else 
           - find the middle element between a & b. Three cases arise :
             1. if middle is lca then ans is subtree[middle] - subtree[middle->a] - subtree[middle->b]
             2. if middle is in path from a to lca, then ans is subtree[middle] - subtree[middle->a]
             3. same as 2. for b
             4. subtree[x->y] denotes the size of child subtree at x which contains y.
           We store last[x][i] denoting the 2nd last node from path x->2^ith parent to find 4. efficiently
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
int n, L[N], up[N][22], last[N][22], l, subtree[N];
vector<int> g[N];

void dfs(int v, int p, int dep)
{
    L[v] = dep;
    up[v][0] = p;
    last[v][0] = v;
    subtree[v] = 1;

    for (int i = 1; i <= l; i++)
        up[v][i] = up[up[v][i-1]][i-1],
        last[v][i] = last[up[v][i-1]][i-1];

    for (auto nb : g[v])
        if (nb != p) 
        {
            dfs(nb, v, dep+1);
            subtree[v] += subtree[nb];
        }
}
PII walk(int v, int k)
{
    int ed = 0;
    for (int i = l; i >= 0; i--)
        if ((k>>i)&1)
            ed = last[v][i], v = up[v][i];
    return mp(v, ed);
}
int lca(int u, int v) 
{
    if (L[u] < L[v]) swap(u, v);
    if (L[u] > L[v]) u = walk(u, L[u]-L[v]).F;
    if (u == v) return u;
    
    for (int i = l; i >= 0; i--)
        if (up[u][i] != up[v][i])
            u = up[u][i], v = up[v][i];
    return up[u][0];
}
int dist(int u, int v) 
{
    return L[u] + L[v] - 2 * L[lca(u, v)];
}

signed main() {

    IOS;
    cin >> n;
    LP(i,n-1)
    {
        int a, b;   cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    l = ceil(log2(n));
    dfs(1, 1, 0);

    int m; cin >> m;
    LP(i,m)
    {
        int a, b;   cin >> a >> b;
        int lc = lca(a, b);
        int dd = dist(a, b);

        if (dd & 1)
        {
            cout << 0 << endl;
        }
        else 
        {
            dd /= 2;
            if (dist(a, lc) == dd)
            {
                int left = walk(a, L[a] - L[lc]).S;
                int right = walk(b, L[b] - L[lc]).S;
                cout << n - subtree[left] - subtree[right] << endl;
            }
            else if (dist(a, lc) > dd)
            {
                PII left = walk(a, dd);
                cout << subtree[left.F] - subtree[left.S] << endl;
            }
            else 
            {
                PII right = walk(b, dd);
                cout << subtree[right.F] - subtree[right.S] << endl;
            }
        }
    }

    return 0;
}
