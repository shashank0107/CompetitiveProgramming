/*
	Author : manu_sy
	Idea : We have to select the minimum no. of nodes such that their reachability is atleast n-1
		- Make component graph 
		- the nodes to be selected will definately be source, so select all of them
		- Now all nodes are reachable
		- Now check if after removal of any source the reachabilility count only decreases to n-1,
		  if yes then we can deselect this node and then done
		- Probabilty = 1 - (taken/n)
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long    ll;

#define pb           push_back
#define F            first
#define S            second
#define mp           make_pair
#define all(a)       (a).begin(),(a).end()
#define FOR(i,a,b)    for(int i=a;i<=b;i++)
#define LP(i,a)      for(int i=0;i< a;i++)
#define cerr cout 

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
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)

const int N = 50+7;

class CarrotBoxes {
public:
	int n;
	vector<int> g[N];

/* Tarjan */
int dfn[N], lowLink[N], ndfn, comp[N], instack[N], inDeg[N], reach[N];
map<int, int> adj[N];
stack<int> st;
vector<vector<int> > comps;

void pre() {
    comps.clear();
    ndfn = 0;
    LP(i,n+2) dfn[i] = -1, comp[i] = -1, g[i].clear(), adj[i].clear(), inDeg[i] = 0, reach[i] = 0;
}
void tarjan(int v) {
    dfn[v] = lowLink[v] = ndfn++, instack[v] = 1;
    st.push(v);

    for (auto ch : g[v]) {
        if (dfn[ch] == -1) {
            tarjan(ch);
            lowLink[v] = min(lowLink[v], lowLink[ch]);
        } else if (instack[ch]) {
            lowLink[v] = min(lowLink[v], dfn[ch]);
        }
    }
    if (lowLink[v] == dfn[v]) {
        comps.pb(vector<int>());

        int x = -1;
        while (x != v) {
            x = st.top(), st.pop(), instack[x] = 0;
            comps.back().pb(x);
            comp[x] = comps.size()-1;
        }
    }
}
void makeCompGraph() {
    FOR(v,0,n-1) for (auto nb : g[v]) if (comp[nb] != comp[v]) adj[comp[v]][comp[nb]] = 1, inDeg[comp[nb]]++;
}

void dfs(int v) {
	reach[v]++;
	for (auto nb : adj[v]) dfs(nb.F);
}
int undfs(int v) {
	reach[v]--;
	int ret = (reach[v] == 0);
	for (auto nb : adj[v]) ret += undfs(nb.F);
	reach[v]++;
	return ret;
}
/* Tarjan Ends */
	
	double theProbability(vector <string> a) {
		
		n = a.size();
		pre();
		for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (a[i][j] == 'Y' && i != j) g[i].pb(j);
		for (int i = 0; i < n; i++) if (dfn[i] == -1)	tarjan(i);
		makeCompGraph();
		
		int taken = 0;
		for (int i = 0; i < comps.size(); i++) if (inDeg[i] == 0)	taken++, dfs(i);
		
		for (int i = 0; i < comps.size(); i++) if (comps[i].size() == 1 && inDeg[i] == 0 && undfs(i) == 1){ 
			taken--; 
			break;
		}
		return 1 - taken*(1.0L/n);
	}
};

<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
