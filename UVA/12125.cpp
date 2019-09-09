/*
    Author : manu_sy
    
    Idea : split each vertex as in-out . So if a penguin wants to jump from i then it must go to out(i) from in(i)
          Now model flow graph. 
        - source to each in(i) with edge ni
        - in(i) to out(i) with edge mi
        - join out(i) to in(j) with capacity INF where dist(i,j) <= d 
        
        Loop over all indices as sink and check if flow is equal to cnt
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

const int N = 1e2+7;
const int INF = 1e8;

/** Template Ends **/
int n, ni, mi;	
double d, x[N], y[N];

int in(int i) {
	return i;
}
int out(int i) {
	return n+i;
}
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
double sq(double x) {
	return x*x;
}
double dist(int i, int j) {
	return sq(x[i]-x[j]) + sq(y[i]-y[j]);
}

signed main() {

    IOS;
    int t;	cin >> t;
    while (t--) {

    	cin >> n >> d;
    	MF mf(2*n+2);

    	int source = 0, sink = 2*n+1, cnt = 0;
    	for (int i = 1; i <= n; i++) {
    		cin >> x[i] >> y[i] >> ni >> mi;
    		mf.insertEdge(source, in(i), ni);
    		mf.insertEdge(in(i), out(i), mi);
    		cnt += ni;
    	}

    	for (int i = 1; i <= n; i++) {
    		for (int j = i+1; j <= n; j++) {
    			if (dist(i,j) <= d*d) {
    				mf.insertEdge(out(i), in(j), INF);
    				mf.insertEdge(out(j), in(i), INF);
    			}
    		}
    	}

    	vector<int> ans;
    	for (int i = 1; i <= n; i++) {
    		MF temp(mf);
    		temp.insertEdge(in(i),sink,INF);
    		if (temp.maxFlow(source, sink) == cnt)	ans.pb(i-1);
    	}

    	if (ans.size() == 0) cout << -1 << endl;
    	else {
    		for (int i = 0; i < (int)ans.size()-1; i++) cout << ans[i] << " ";
    		cout << ans.back() << endl;
    	} 
    }

    return 0;
}
