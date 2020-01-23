/*
    Author : manu_sy
    Idea : Treat every string XYZ as an edge from node XY to node YZ. 
          - There are only 62 * 62 possible nodes ( 26 + 26 + 10 valid chars ) .
          - Now just have to find the euler tour / path through this graph
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

const int K = 63, N = 65 * 65;

/** Template Ends **/
int n;
vector<vector<int> > g(N);

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
    for (int i = 0; i < n; i++) if ((in[i]-out[i])&1) deg.pb(mp(in[i]-out[i], i));

    int f = 0;
    if (deg.size() == 0)    f = 2;
    else if (deg.size() == 2) {
        sort(all(deg));
        if (deg[0].F == -1 && deg[1].F == 1)
            f = 1, adj[deg[1].S].pb(deg[0].S), edge_cnt++;
    }
    if (f == 0) return mp(0, vector<int>());
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
    if (f == 1) {
        adj[deg[0].S].pop_back(), adj[deg[1].S].pop_back();
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
        edge_cnt--;
    }
    if (path.size() != edge_cnt + 1)    return mp(0, vector<int>());
    return mp(f, path);
}
int val(char c) {
    if (c >= 'a' && c <= 'z')       return c - 'a';
    else if (c >= 'A' && c <= 'Z')  return c - 'A' + 26;
    else if (c >= '0' && c <= '9')  return c - '0' + 52;
    else assert(false);
}
int node(string s) {
    return val(s[0]) * K + val(s[1]);
}
char ch(int v) {
    if (v < 26) return ((char)('a' + v));
    else if (v < 52)    return ((char)('A' + v - 26));
    else if (v < 62)    return ((char)('0' + v - 52));
    else assert(false);
}
string st(int v) {
    string s = "";
    s += ch(v / K);
    s += ch(v % K);
    return s;
}

signed main() {

    IOS;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string a;   cin >> a;
        int v1 = node(a.substr(0, 2)), v2 = node(a.substr(1));
        g[node(a.substr(0, 2))].pb(node(a.substr(1)));
    }

    auto p = euler_directed_adj(g);
    if (p.F == 0)   cout << "NO" << endl;
    else {
        cout << "YES" << endl;
        for (auto v : p.S) cout << st(v)[0];
        cout << st(p.S.back())[1] << endl;
    }
    
    return 0;
}
