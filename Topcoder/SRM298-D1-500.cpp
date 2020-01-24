/*
    Author : manu_sy
    Idea : Same as https://github.com/Huvok/CompetitiveProgramming/blob/master/Topcoder/SRM298-D1-500.cpp
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


/** Template Ends **/

// {0, no_euler} / {1, euler_path} / {2, euler tour}
pair<int, vector<int> > euler_directed_adj(vector<vector<int> >& adj) 
{
    assert(adj.size() != 0);
    int n = adj.size(), edge_cnt = 0, start = -1;
    vector<int> in(n), out(n);
    for (int i = 0; i < n; i++) for (auto nb : adj[i]) {
        if (start == -1)    start = i;
        in[nb]++, out[i]++, edge_cnt++;
    }
    vector<PII> deg;
    for (int i = 0; i < n; i++) {
        if ((in[i]-out[i])&1) deg.pb(mp(in[i]-out[i], i));
        else if (in[i] != out[i])   return mp(0, vector<int>());
    }
    int f = 0;
    if (deg.size() == 0)    f = 2;
    else if (deg.size() == 2) {
        sort(all(deg));
        if (deg[0].F == -1 && deg[1].F == 1)
            f = 1, adj[deg[1].S].pb(deg[0].S), edge_cnt++;
    }
    if (f == 0 || start == -1) return mp(0, vector<int>());
    assert(start != -1);

    vector<int> path;
    stack<int> st;
    st.push(start);
    vector<vector<int> > g(n);
    for (int i = 0; i < n; i++) for (auto nb : adj[i]) g[nb].pb(i);

    int ans = 0;
    while (!st.empty()) {
        int u = st.top();
        if (g[u].empty()) {
            path.pb(u);
            st.pop();
        }
        else {
            int v = g[u].back();
            g[u].pop_back();
            st.push(v);
        }
    }
    if (f == 1) adj[deg[1].S].pop_back();
    if (path.size() != edge_cnt + 1)    return mp(0, vector<int>());

    if (f == 1) {
        int pos = -1;
        for (int i = 0; i < (int)path.size() - 1; i++) {
            if (path[i] == deg[1].S && path[i + 1] == deg[0].S) {
                pos = i;
                break;
            }
        }
        assert(pos != -1);
        vector<int> temp;
        for (int i = pos + 1; i < path.size(); i++) temp.pb(path[i]);
        for (int i = 1; i <= pos; i++)  temp.pb(path[i]);
        path = temp;
    }
    return mp(f, path);
}

class OrderDoesMatter {
public:
    int getOrder(vector <int> N, vector <int> M) {
        int n = N.size();
        vector<vector<int> > adj(1007);
        int mx = INT_MIN;
        for (int i = 0; i < n; i++) {
            if (N[i] == 1 && M[i] == 1) continue;
            debug(N[i], M[i]);
            mx = max(mx, N[i]);
            adj[N[i]].pb(M[i]);
        }
        auto p = euler_directed_adj(adj);
        debug(p.F, p.S);
        if (p.F == 0) return -1;
        else if (p.F == 1) {
            return p.S[0] * p.S.back();
        } 
        else if (p.F == 2) {
            return mx * mx;
        }
    }
};
