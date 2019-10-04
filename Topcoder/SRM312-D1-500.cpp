/*
    Author : manu_sy
    
    Idea : First make a component graph, where the cost of each component is the lowest cost present in that component.
           Now all the nodes in the component graph with in_degree = 0 definately need to be chosen :
           - After choosing these we can reach every other node
           
           But still we need to minimize the average cost of stations :
           - So greedily check if choosing the lowest cost station that isnt chosen yet can decrease the average
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long    ll;

#define pb           push_back
#define F            first
#define S            second
#define mp           make_pair
#define all(a)       (a).begin(),(a).end()
#define fr(i,a,b)    for(int i=a;i<=b;i++)
#define lp(i,a)      for(int i=0;i< a;i++)

#define trace(x)                 cout << #x << ": " << x << endl;
#define trace2(x, y)             cout << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)          cout << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl;


class AntarcticaPolice {
public:
	int n;
	int dfn[55], ndfn, lowLink[55], instack[55], comp_cnt, ans, comp[55], cst[55], deg[55], taken[55];
	stack<int> st;
	vector<int> cost;
	vector<string> g;
	vector<vector<int> > comps;
	
	void tarjan(int v) {
		dfn[v] = lowLink[v] = ndfn++, instack[v] = 1;
		st.push(v);
		
		for (int nb = 0; nb < n; nb++) {
			if ( g[v][nb] != 'Y')	continue;
			if (dfn[nb] == -1) {
				tarjan(nb);
				lowLink[v] = min(lowLink[v], lowLink[nb]);
			} else {
				if (instack[nb]) lowLink[v] = min(lowLink[v], dfn[nb]);
			}
		}
		
		if (dfn[v] == lowLink[v]) {
			comps.pb(vector<int>());
			
			int cur = INT_MAX;
			while (st.top() != v) {
				int vv = st.top();	st.pop(); instack[vv] = 0;
				cur = min(cur, cost[vv]);
				if (cur == cost[vv]) taken[comps.size()-1] = vv;
				comps.back().pb(vv);
				comp[vv] = comps.size()-1;
			}
			cur = min(cur, cost[v]); st.pop(); instack[v] = 0;
			comps.back().pb(v);
			comp[v] = comps.size()-1;
			if (cur == cost[v]) taken[comps.size()-1] = v;
			
			cst[comps.size()-1] = cur;
		}
	}
	
	double minAverageCost(vector <int> costs, vector <string> roads) {
		
		n = costs.size();
		cost = costs;
		g = roads;
		ndfn = 1;
		comps.clear();
		ans = 0;
		for (int i = 0; i <= n; i++) dfn[i] = lowLink[i] = -1, instack[i] = 0, comp[i] = -1, deg[i] = 0, taken[i] = -1;
		
		for (int i = 0; i < n; i++) if (dfn[i] == -1) tarjan(i);
		
		int cc = comps.size();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) 
				if (roads[i][j] == 'Y' && comp[i] != comp[j]) {
					deg[comp[j]]++;	
				} 
		
		int stations = 0;
		vector<bool> done(n, false);
		for (int i = 0; i < cc; i++) if (deg[i] == 0) ans += cst[i], stations++, done[taken[i]] = true;
		
		vector<pair<int, int> > p;
		for (int i = 0; i < n; i++) if (!done[i]) p.pb(mp(costs[i], i));
		
		sort(all(p));
		for (auto i : p) {
			double cur_mean = (1.0l*ans)/stations;
			double new_mean = (1.0l*(ans+i.F))/(stations+1);
			
			if (new_mean <= cur_mean) {
				ans += i.F;
				stations++;
			}
		}
		
		return (1.0l*ans)/stations;
	}
};

<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
