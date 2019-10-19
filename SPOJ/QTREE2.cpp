/*
    Author : manu_sy
    Idea : To get kth node just find
          1. find the lca of a, b
          2. check if the kth node lies in the lca to a/b path
          3. get the required parent using kthparent function
          
          To get dist, store dup[v][i] - dist from v to 1<<i th parent 
          1. then its just like getting lca just you have to add dup[v][i] when you go from v to up[v][i]
          2. So just go from a to lca and b to lca and keep adding doing pt 1.
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
int n, L[N];
vector<vector<PII> > g;

/* LCA Code */
int l, timer;
vector<int> tin, tout;
vector<vector<int> > up, dup;

void dfs(int v, int p, int lvl, int cost) {
    L[v] = lvl;
    tin[v] = ++timer;
    up[v][0] = p;
    dup[v][0] = cost;
    for (int i = 1; i <= l; i++) 
        up[v][i] = up[up[v][i-1]][i-1],
        dup[v][i] = dup[up[v][i-1]][i-1] + dup[v][i-1];

    for (auto u : g[v])
        if (u.F != p) dfs(u.F, v, lvl+1, u.S);
    tout[v] = ++timer;
}
bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}
int lca(int u, int v) {
    if (is_ancestor(u, v))   return u;
    if (is_ancestor(v, u))   return v;
    for (int i = l; i >= 0; i--) {
        if (!is_ancestor(up[u][i],v))
            u = up[u][i];
    }
    return up[u][0];
}

void preProcess(int root) {
    timer = 0;
    tin.resize(n+1);
    tout.resize(n+1);
    l = ceil(log2(n));
    up.assign(n+1, vector<int>(l+1));
    dup.assign(n+1, vector<int>(l+1));
    dfs(root,root,0,0);
}
/* LCA ends */
int kthParent(int v, int k) {
    if (k == 0) return v;
    for (int i = l; i >= 0; i--) {
        if (1<<i <= k) 
            k -= (1<<i), v =  up[v][i];
    }
    return v;
}
int get_dist(int u, int v) {
    if (u == v) return 0;
    int ans = 0;
    if (is_ancestor(u, v)) swap(u,v);
    if (!is_ancestor(v, u)) {
        for (int i = l; i >= 0; i--) 
            if (!is_ancestor(up[v][i], u)) 
                ans += dup[v][i], v = up[v][i];
        ans += dup[v][0], v = up[v][0];
    } 
    assert(is_ancestor(v, u));
    for (int i = l; i >= 0; i--)
        if (L[up[u][i]] >= L[v])
            ans += dup[u][i], u = up[u][i];
    assert(u == v);
    return ans;
}

signed main() {

    IOS;
    int t;  cin >> t;
    while (t--) {
        cin >> n;
        g.clear();  g.resize(n+1);    
        LP(i,n-1) {
            int a, b, c;    cin >> a >> b >> c;
            g[a].pb(mp(b, c));
            g[b].pb(mp(a, c));
        }
        preProcess(1);
        
        string inp;
        while (cin >> inp) {
            if (inp == "DONE")  break;
            else if (inp == "DIST") {
                int a, b;   cin >> a >> b;
                cout << get_dist(a,b) << endl;
            } else {
                int a, b, k;    cin >> a >> b >> k;
                int lcca = lca(a,b);
                if (k <= L[a]-L[lcca]+1)    cout << kthParent(a,k-1) << endl;
                else {
                    k -= (L[a]-L[lcca]+1);
                    int pos = L[b]-L[lcca]-k;
                    cout << kthParent(b,pos) << endl;
                }   
            }
        }
        cout << endl;
    }
    return 0;
}
