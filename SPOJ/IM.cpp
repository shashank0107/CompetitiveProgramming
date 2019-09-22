/*
    Author : manu_sy
    
    Idea : similar to 
         https://github.com/ilyesLtifi/Competitive-Programming/blob/master/SPOJ/SPOJ%20IM.cpp
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
int n, m;
 
int in(int v) {
	return v;
}
int out(int v) {
	return n+v;
}
struct MF {
    int n;
    vector<vector<int> > adj;
    vector<map<int,int> > cap;
    vector<int> vis;
 
    MF(int nn) {
        n = nn;
        adj.resize(n);
        vis.resize(n);
        cap.resize(n);
    }
    void insertEdge(int s, int e, int capacity) {
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
    int t;	cin >> t;
    while (t--) {
    	cin >> n >> m;
 
    	MF mf(2*n+2);
    	for (int i = 1; i <= n; i++) mf.insertEdge(in(i),out(i),(i==2?2:1));
 
    	for (int i = 0; i < m; i++) {
    		int a, b;	cin >> a >> b;
    		if (a >= 1 && a <= n && b >= 1 && b <= n) {
	    		mf.insertEdge(out(a),in(b),5);
	    		mf.insertEdge(out(b),in(a),5);
	   		}
    	}
    	if (n == 2) {
    		cout << "NO" << endl;
    		continue;
    	}
 
    	mf.insertEdge(0,in(2),2);
    	mf.insertEdge(out(1),2*n+1,1);
    	mf.insertEdge(out(3),2*n+1,1);
 
    	int flow = mf.maxFlow(0,2*n+1);
    	if (flow == 2)	cout << "YES" << endl;
    	else cout << "NO" << endl;
    }
 
 
    return 0;
}
