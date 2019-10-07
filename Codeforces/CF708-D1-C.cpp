/*
    Author : manu_sy
    
    Idea : Keep for each node the top 3 size of subtrees which are <= n/2 ( using dfs1 )
          Now use dfs to calculate ans
          - So if we are currently at root then check for each child if its size is greater than n/2 
            if it is then check if we can find a subtree of that child with size s.t removing it makes the size 
            of child <= n/2. We can do it in O(1) since we precompute it in dfs1
          - Do rerooting while travelling
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

const int N = 4e5+7;

/** Template Ends **/
int n, sz[N], ans[N];
vector<int> g[N];
vector<PII> szch[N];
bool vis[N];

void dfs1(int v, int par) {

    sz[v] = 1;
    for (auto nb : g[v])
        if (nb != par) {
            dfs1(nb, v);
            sz[v] += sz[nb];
            szch[v].pb(mp(szch[nb][0].F, nb));
        }
    if (sz[v] <= n/2)   szch[v].pb(mp(sz[v], v));
    sort(all(szch[v]), greater<PII>());
    if (szch[v].size() > 3)    szch[v].resize(3);
}
void dfs2(int v, int par) {

    int valid = 1;
    for (auto nb : g[v]) {
        if (nb != par) {
            if (sz[nb]-szch[nb][0].F > n/2) {
                debug(nb, szch[nb]);
                valid = 0;
            } 
        } else {
            int ch2 = 0;
            for (auto c : szch[par]) if (c.S != par && c.S != v){ ch2 = c.F; break; }
            
            if (sz[par]-sz[v]-ch2 > n/2) {
                valid = 0;
            }
        }
    }
    ans[v] = valid;

    if (par != -1) {
        if (szch[v][0].S == v) {
            if (sz[par] > n/2)    szch[v].erase(szch[v].begin());   
        }
        for (auto c : szch[par]) {
            if (c.S != par && c.S != v) {
                //debug(c);
                szch[v].pb(mp(c.F, par));
            }
        }
        if (sz[par]-sz[v] <= n/2)   szch[v].pb(mp(sz[par]-sz[v], par));
        sort(all(szch[v]), greater<PII>());
        if (szch[v].size() > 3)    szch[v].resize(3);

        sz[v] = sz[par];
    }
    debug(v, szch[v]);

    for (auto nb : g[v]) if (nb != par) dfs2(nb, v);
}

signed main() {

    IOS;
    cin >> n;
    LP(i,n-1) {
        int a, b;   cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    dfs1(1, -1);
    dfs2(1, -1);

    FOR(i,1,n) cout << ans[i] << " ";   cout << endl;

    return 0;
}
