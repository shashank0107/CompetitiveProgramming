/*
    Author : manu_sy
    
    Idea : Similar to editorial - https://codeforces.com/blog/entry/10476
          - Break the tree into 2 trees on basis of parity
          - Now the problem just reduces to making queries on subtree
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

const int N = 2e5+7;

/** Template Ends **/

int n, m, a[N], par[N], in[N], out[N], id[N], timer;
vector<int> adj[N], g[2][N], nodes[2];

struct BIT {
    vector<int> bit;
    int n;
    BIT () {
        this->n = N + 5;
        bit.assign(this->n + 5, 0);
    }
    void add(int idx, int val) {
        for (++idx; idx < n; idx += idx & -idx)
            bit[idx] += val;
    }
    void range_add(int l, int r, int val) {
        add(l, val);
        add(r + 1, -val);
    }
    int query(int idx) {
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }
} bt[2];

void init(int v, int lvl, int p) {
    if (p)  par[v] = p;
    id[v] = lvl & 1;
    nodes[id[v]].pb(v);

    for (auto ch : adj[v])
        if (ch != p)
        {
            g[id[p]][p].pb(ch);
            init(ch, lvl + 1, v);
        }
}

void dfs(int v, int ii) {
    in[v] = ++timer;

    for (auto ch : g[ii][v])
        dfs(ch, ii);
        
    out[v] = timer;
}

void add(int v, int val) {
    bt[id[v]].range_add(in[v], out[v], val);
}

int query(int v) {
    return bt[id[v]].query(in[v]);
}

signed main() {

    IOS;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    BIT bt[2];

    for (int i = 0; i < n-1; i++)
    {
        int u, v;   cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    init(1, 0, 0);

    for (int i = 0; i < 2; i++) 
    {
        timer = 0;
        for (auto v : nodes[i]) if (!in[v]) dfs(v, i);
    }

    while (m--)
    {
        int q, x, val;  cin >> q >> x;
        
        if (q == 1)
        {
            cin >> val;
            add(x, val);
        }
        else
        {
            cout << a[x] + query(x) - (par[x] ? query(par[x]) : 0) << endl;
        }
    }
    return 0;
}
