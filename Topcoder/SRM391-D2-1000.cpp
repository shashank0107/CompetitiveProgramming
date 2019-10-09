/* 
    Author : manu_sy 
    Idea : Just convert to component graph and apply dfs-dp to calculate the answer
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
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
/* Debug Ends */

const int N = 1000+7;

class MarbleCollectionGame {
public:
	vector<vector<int> > g, adj;
	int nn, ni, mi;
	vector<int> val;
	
	int ver(int i, int j) {
		return i*mi+j;
	}
	    /* Tarjan */
    int dfn[N], lowLink[N], ndfn, comp[N], instack[N], profit[N], dp[N];
    stack<int> st;
    vector<vector<int> > comps;
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
                profit[comps.size()-1] += val[x];
            }
        }
    }
    /* Tarjan Ends */
    int calc(int v) {
    	if (dp[v] != -1)	return dp[v];
    	dp[v] = 0;
    	for (auto nb : adj[v])	dp[v] = max(dp[v], calc(nb));
    	dp[v] += profit[v];
    	return dp[v];
    }
	
	int collectMarble(vector <string> board) {
		
		ni = board.size();
		if (ni == 0)	return 0;
		mi = board[0].size();
		nn = ni*mi;
		g.clear();	g.resize(nn);
		val = vector<int>(nn, 0);
		
		LP(i,ni) LP(j,mi) {
			if (board[i][j] == '#')	continue;
			if (i != ni-1)	g[ver(i,j)].pb(ver(i+1,j));
			if (j != mi-1) 	g[ver(i,j)].pb(ver(i,j+1));
			if (board[i][j] == 'U' && i != 0 && board[i-1][j] != '#')		g[ver(i,j)].pb(ver(i-1,j));
			else if (board[i][j] == 'L' && j != 0 && board[i][j-1] != '#')	g[ver(i,j)].pb(ver(i,j-1));
			else if (board[i][j] >= '0' && board[i][j] <= '9') val[ver(i,j)] = board[i][j]-'0';
		}
		//debug(val);
		//debug(g);
		
		comps.clear();
		ndfn = 0;
		FOR(i,0,nn-1) dfn[i] = comp[i] = -1,  dp[i] = -1, profit[i] = 0;
		FOR(i,0,nn-1) if (dfn[i] == -1) tarjan(i);
		
		//debug(comps);
		adj.clear();	adj.resize(comps.size());
		FOR(i,0,nn-1) for (auto nb : g[i]) if (comp[i] != comp[nb]) adj[comp[i]].pb(comp[nb]);
		
		int ans = calc(comp[0]);
		//LP(i,comps.size()) debug(i, profit[i], dp[i]);
		
		return ans;
	}
};

<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
