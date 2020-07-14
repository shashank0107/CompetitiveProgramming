/*
    Author : manu_sy
    Idea : Same as https://ideone.com/KCCz60
          - Just reduce the problem to queries finding the no. of elements in [l, r] which also belong to [l,r] 
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
 
#ifdef LOCALi
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif
 
/* Debug Ends */
 
const int N = 2e5+7;
 
/** Template Ends **/
int n;
int q;
vector<int> g[N];
int par[N];
vector<int> sg[4 * N];

void dfs(int v, int p) {
    par[v] = p;
    for (auto nb : g[v])
        if (nb != p)
            dfs(nb, v);
}
void build(int s=0, int e=n, int p=1) {
    sg[p].clear();
    if (s == e) {
        sg[p].pb(par[s]);
        return;
    }
    int m = (s + e) / 2;
    build(s, m, 2 * p);
    build(m + 1, e, 2 * p + 1);
    vector<int> &v1 = sg[2 * p], &v2 = sg[2 * p + 1], &v = sg[p];
    int p1 = 0, p2 = 0;
    while (p1 < v1.size() || p2 < v2.size()) {
        if (p1 == v1.size())
            v.pb(v2[p2++]);
        else if (p2 == v2.size())
            v.pb(v1[p1++]);
        else {
            if (v1[p1] <= v2[p2]) {
                v.pb(v1[p1++]);
            }
            else {
                v.pb(v2[p2++]);
            }
        }
    }
}
int query(int l, int r, int s=0, int e=n, int p=1) {
    if (s > r || e < l)
        return 0;
    if (l <= s && e <= r) {
        int li = lower_bound(all(sg[p]), l) - sg[p].begin();
        int ri = upper_bound(all(sg[p]), r) - sg[p].begin();
        return ri - li;
    }
    int m = (s + e) / 2;
    return query(l, r, s, m, 2 * p) + query(l, r, m + 1, e, 2 * p + 1);
}
 
signed main() {
 
    IOS;
    int t;  cin >> t;
    while (t--) {
        cin >> n >> q;
        LP(i,n+3)   g[i].clear();
        LP(i,n-1) {
            int u, v;   cin >> u >> v;
            g[u].pb(v);
            g[v].pb(u);
        }
        dfs(1, 0);
        build();
        LP(i,q) {
            int l, r;   cin >> l >> r;
            int res = query(l, r);
            cout << r - l + 1 - res << endl;
        }
    }

    return 0;
}
