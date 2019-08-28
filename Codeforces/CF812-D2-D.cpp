/*
    Author : manu_sy

    Idea : Same as editorial
        https://codeforces.com/blog/entry/52318
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
#define FOR(i,a,b)  for(int i=a;i<=b;i++)

/* Debug */
template<class L, class R> ostream &operator<<(ostream &os, pair<L,R> P) {
  return os << "(" << P.st << "," << P.nd << ")";
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
int n, m, k, q, own[N], in[N], out[N], sz[N], t;
bool root[N];
vector<int> g[N];

void dfs(int v) {
    in[v] = t++;
    sz[v] = 1;
    for (auto ch : g[v]) {
        dfs(ch);
        sz[v] += sz[ch];
    }
    out[v] = t++;
}

signed main() {

    IOS;
    cin >> n >> m >> k >> q;
    memset(root, true, sizeof root);

    while (k--) {
        int a, b;   cin >> a >> b;
        assert(root[a]);
        if (own[b]) {
            g[own[b]].pb(a);
            root[a] = false;
        }
        own[b] = a;
    }
    t = 1;
    FOR (i,1,n) if (root[i]) dfs(i);

    while (q--) {
        int x, y;   cin >> x >> y;
        y = own[y];
        if (in[y] >= in[x] && out[y] <= out[x]) 
            cout << sz[x] << endl;
        else cout << 0 << endl;
    }

    return 0;
}
