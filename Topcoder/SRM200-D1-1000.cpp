/*
    Author : manu_sy
    Idea : Model the problem as a maxflow problem :
          - Each requirement is like a source node with capacity equal to requiremnt need and all edges of capacity 1 going to 
            the characters included in requirement.
          - Each character is a destination node with capacity equal to 1
          - Firstly make capacity of all characters in classesTaken as 1 and all other 0
          - We just have to find the minimum character uptil we make capacities 1, such that the needed flow is reached.
          - Can do binary search or like i have done (iteratively)
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
 
#ifdef LOCAL
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif
 
/* Debug Ends */
 
const int N = 5e6+7;
 
/** Template Ends **/
struct MF {
    int n;
    vector<vector<int> > adj, cap;
    vector<int> vis;

    MF(int nn) {
        n = nn;
        adj.resize(n);
        vis.resize(n);
        cap = vector<vector<int> >(n, vector<int>(n, 0));
    }
    void addEdge(int s, int e, int capacity) {
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
class Graduation {
public:
	string moreClasses(string classesTaken, vector <string> requirements) {

		MF mf(200);
		int src = 0, snk = 197;
		vector<bool> present(130, false);
		for (auto i : classesTaken) {
			mf.addEdge(i + 51, snk, 1), present[(int)i] = true;
		}
		

		int need = 0;
		for (int j = 0; j < requirements.size(); j++)
		{
			auto i = requirements[j];
			stringstream ss;
			ss << i;
			int cnt; string nbr;
			ss >> cnt >> nbr;
			
			need += cnt;
			mf.addEdge(src, 1 + j, cnt);
			for (auto i : nbr)
				mf.addEdge(1 + j, i + 51, 1);
		}

		int flow = mf.maxFlow(src, snk);
		if (flow == need) return "";

		for (char c = 33; c <= 126; c++) if (!present[(int)c])
		{
			mf.addEdge(c + 51, snk, 1);
			int nflow = mf.maxFlow(src, snk);
			flow += nflow;

			if (flow == need)
			{
				string ans;
				for (char c = 33; c <= 126; c++) if (!present[c])
				{
					if (mf.cap[snk][c + 51] == 1)	ans += (char)c;
				}
				return ans;
			} 
		}
		return "0";
	}
};

 
signed main() {
 
    IOS;
    Graduation g;
    auto s = g.moreClasses("A", {"2ABC","2CDE"});
    debug(s);
    s = g.moreClasses("+/NAMT",{"3NAMT","2+/","1M"});
    debug(s);
    s = g.moreClasses("A",{"100%*Klju"});
    debug(s);
    s = g.moreClasses("CDH",{"2AP", "3CDEF", "1CDEFH"});
    debug(s);

 
    return 0;
}
