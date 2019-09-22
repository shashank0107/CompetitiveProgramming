/*
    Author : manu_sy
    
    Idea : Using maxflow-mincut
        - person1 is the source, person2 is the sink
        - for person1 and person2 to be 3 friends - path of length less than 3 edges :
           1. A -> v1 -> B
           2. A -> v1 -> v2 -> B
        - We definately need to remove vertices of type 1. So remove them and add to ans
        - Then build a graph of where edges only include paths of form 2. 
        - Put capacity 1 on vertices
        - Add mincut to ans
*/

#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int>    PII;

#define pb          push_back
#define F           first
#define S           second
#define mp          make_pair
#define all(a)      (a).begin(), (a).end()
#define FOR(i,a,b)  for(int i=a;i<=b;i++)
#define LP(i,n)     for(int i=0;i< n;i++)
#define cerr 		cout 

#define trace(x)                 cout << #x << ": " << x << endl;
#define trace2(x, y)             cout << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)          cout << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl;

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

const int INF = 1e9+7;

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


class PeopleYouMayKnow {
public:
	int n;
	int in(int v) {	return v; }
	int out(int v) {	return v+n;  }
	
	int maximalScore(vector <string> friends, int p1, int p2) {
		
		n = friends.size();
		MF mf(2*n);
		
		int ans = 0;
		for (int i = 0; i < n; i++) {
			if (i != p1 && i != p2 && friends[p1][i] == 'Y' && friends[p2][i] == 'Y') {
				friends[p1][i] = friends[p2][i] = friends[i][p1] = friends[i][p2] = 'N', ans++;  
			}
		}
		for (int i = 0; i < n; i++) {
			if (friends[p1][i] == 'Y')	mf.addEdge(p1, in(i),INF);
			if (friends[i][p2] == 'Y')  mf.addEdge(out(i), p2, INF);
		}
		for (int i = 0; i < n; i++) {
			if (i != p1 && i != p2) 
				mf.addEdge(in(i), out(i), 1);
		}
		LP(i,n) LP(j,n) {
			if (friends[p1][i] == 'Y' && friends[p2][j] == 'Y' && friends[i][j] == 'Y') {
				mf.addEdge(out(i), in(j), INF);
			}
		}
		
		int flow = mf.maxFlow(p1, p2);
		//debug(flow, ans);
		return ans + flow;
	}
};

<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
