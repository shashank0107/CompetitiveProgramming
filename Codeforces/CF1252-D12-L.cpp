/*
    Author : manu_sy
    Idea : Just simulate the problem using maxflow
          - Idea similar to https://github.com/farmerboy95/CompetitiveProgramming/blob/master/Codeforces/CF1252-D12-L.cpp
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
 
#ifdef LOCALI
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif
 
/* Debug Ends */
 
const int N = 1e4+7;
 
/** Template Ends **/
int n, k, a[N], par[N], cylen, co[N];
vector<int> g[N], b[N], v;
map<int, vector<int> > w;
bool cy[N], vis[N];
PII ans[N];

int findp(int val) {
    int p = lower_bound(all(v), val) - v.begin();
    assert(v[p] == val);    return p;
}

void dfs(int v, int p) {
    debug(v, p);
    vis[v] = true;
    par[v] = p;
    for (auto nb : g[v]) if (nb != p) 
    {
        if (vis[nb] && cylen == 0)
        {
            // debug(nb);
            int cur = v;
            while (cur != nb) {
                debug(cur, par[cur]);
                cy[cur] = true, cylen++;
                cur = par[cur];
            } cy[cur] = nb, cylen++; debug(cur);
        }
        else if (!vis[nb]) dfs(nb, v);
    }
}

struct MF {
    int n;
    vector<vector<int>> adj;
    vector<map<int, int> > cap;
    vector<int> vis;

    MF(int nn) {
        n = nn;
        adj.resize(n);
        vis.resize(n);
        cap.resize(n);
    }
    void addEdge(int s, int e, int capacity) {
        debug(s, e, capacity);
        adj[s].pb(e);
        adj[e].pb(s);
        cap[s][e] = capacity;
    }
    int bfs(int s, int e, vector<int>& parent) {
        fill(all(parent), -1);
        parent[s] = -2;
        queue<PII> q;
        q.push(mp(s, INT_MAX));

        while (!q.empty()) {
            PII p = q.front();  q.pop();
            int cur = p.F;
            int flow = p.S;

            for (auto next : adj[cur]) {
                if (parent[next] == -1 && cap[cur][next]) {
                    parent[next] = cur;
                    int newflow = min(flow, cap[cur][next]);
                    if (next == e)
                        return newflow;
                    q.push(mp(next, newflow));
                }
            }
        }
        return 0;
    }
    int maxFlow(int source, int sink) {
        int flow = 0;
        vector<int> parent(n);
        int newflow;

        while (newflow = bfs(source, sink, parent)) {
            flow += newflow;

            for (int cur = sink; cur != source; cur = parent[cur]) {
                int prev = parent[cur];
                cap[prev][cur] -= newflow;
                cap[cur][prev] += newflow;
            }
        }
        return flow;
    }
};

signed main() {
 
    IOS;
    cin >> n >> k;
    FOR(i,1,n)
    {
        int m;  cin >> a[i] >> m;
        g[a[i]].pb(i);    g[i].pb(a[i]);    

        b[i].resize(m);
        LP(j,m) cin >> b[i][j], v.pb(b[i][j]);
    }
    FOR(i,1,k) cin >> co[i],   v.pb(co[i]);   
    sort(all(v)); v.resize(unique(all(v)) - v.begin());

    FOR(i,1,k) {
        int x = findp(co[i]) + 1;
        w[x].pb(i);
    }

    dfs(1, 0);
    int d = v.size();
    debug(cylen);
    // FOR(i,1,n) cout << cy[i] << " "; cout << endl;

    MF mf(2 + n + d + 2);
    int src = 1, snk = 2 + n + d + 1;
    mf.addEdge(1, 2, cylen - 1);

    FOR(i,1,n)
    {
        if (cy[i] && cy[a[i]])  mf.addEdge(2, i + 2, 1);
        else                    mf.addEdge(1, i + 2, 1);

        debug(i, cy[i], cy[a[i]]);
        for (auto x: b[i])
        {
            int p = findp(x) + 1;
            mf.addEdge(i + 2, 2 + n + p, 1);
        }
    }
    FOR(i,1,d)  mf.addEdge(2 + n + i, snk, w[i].size());

    int flow = mf.maxFlow(src, snk);
    debug(flow);
    if (flow != n-1) cout << -1 << endl;
    else
    {
        FOR(i,1,n)
        {
            int nb = -1;
            for (auto x: b[i])
            {
                int p = findp(x) + 1;
                if (mf.cap[2 + n + p][i + 2] == 1) {
                    assert(nb == -1);   nb = p;
                }
            }
            debug(i, nb);
            if (nb != -1)
            {
                assert(!w[nb].empty());
                int haha = w[nb].back();    w[nb].pop_back();
                ans[haha] = {i, a[i]};
            }
        }
        FOR(i,1,k) cout << ans[i].F << " " << ans[i].S << endl;
    }
 
    return 0;
}
