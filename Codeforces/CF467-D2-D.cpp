/*
    Author : manu_sy
    
    Idea : Make a DAG of all the words in dictionery and then find its component graph.
          - Find min cost of a component in component graph using dfs since its acyclic.
          - Add the required costs.
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
int n, nn, m, in[N];
PII cost[N], compCost[N], finalCost[N];
vector<string> dict, final_words, need;
map<string, int> idx;
vector<int> g[N], adj[N], freq, topo;

int dfn[N], lowLink[N], ndfn, comp[N];
bool inStack[N], vis[N];
stack<int> st;
vector<vector<int> > comps;

string tolower(string s) {
    string ret = s;
    for (int i = 0; i < s.size(); i++)
        ret[i] = tolower(s[i]);
    return ret;
}

void tarjan(int v) {
    dfn[v] = lowLink[v] = ndfn++, inStack[v] = 1;
    st.push(v);

    for (auto ch : g[v]) {
        if (dfn[ch] == -1) {
            tarjan(ch);
            lowLink[v] = min(lowLink[v], lowLink[ch]);
        } else if (inStack[ch]) {
            lowLink[v] = min(lowLink[v], dfn[ch]);
        }
    }

    if (lowLink[v] == dfn[v]) {
        comps.pb(vector<int>());

        int x = -1;
        PII cst = mp(INT_MAX, INT_MAX);
        while (x != v) {
            x = st.top(), st.pop(), inStack[x] = 0;
            comps.back().pb(x);
            comp[x] = comps.size()-1;
            cst = min(cst, cost[x]);
        }
        compCost[comps.size()-1] = cst;
    }
}
void makeComponentGraph() {
    LP(i,n) {
        for (auto nb : g[i]) {
            if (comp[i] != comp[nb]) {
                adj[comp[i]].pb(comp[nb]);
                in[comp[nb]]++;
            }
        }
    }
}
void dfs(int v) {
    vis[v] = true;
    finalCost[v] = compCost[v];

    for (auto nb : adj[v]) {
        if (!vis[nb]) {
            dfs(nb);
        }
        finalCost[v] = min(finalCost[v], finalCost[nb]);
    }
}

signed main() {

    IOS;
    cin >> nn;
    LP(i,nn) {
        string s; cin >> s;  
        need.pb(tolower(s)); 
    }

    cin >> m;
    vector<pair<string, string> > ed;
    LP(i,m) {
        string a, b;    cin >> a >> b;
        a = tolower(a), b = tolower(b);
        dict.pb(a), dict.pb(b);
        ed.pb(mp(a, b));
    }

    sort(all(dict));
    dict.resize(unique(all(dict))- dict.begin());
    n = dict.size();
    
    LP(i,n) {
        idx[dict[i]] = i;
        for (auto c : dict[i]) {
            if (c == 'r') cost[i].F++;
        } 
        cost[i].S = dict[i].size();
    }
    for (auto e : ed) {
        g[idx[e.F]].pb(idx[e.S]);
    }

    LP(i,n) dfn[i] = -1;
    LP(i,n) if (dfn[i] == -1) tarjan(i);

    makeComponentGraph();
    LP(i,comps.size()) if (!vis[i]) dfs(i);

    ll len = 0, r = 0;
    for (auto s : need) {
        if (idx.find(s) == idx.end()) {
            len += s.size();
            for (auto i : s) if (i == 'r') r++;
        } else {
            auto cc = finalCost[comp[idx[s]]];
            len += cc.S;
            r += cc.F;
        }
    }
    cout << r << " " << len << endl;

    return 0;
}
