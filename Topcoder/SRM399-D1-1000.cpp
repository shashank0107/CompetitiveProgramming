/*
    Author : manu_sy
    
    Idea : Represent the graph as follows
        - each boy node as 2 vertices - inb(i), oub(i) 
            source -> inb(i) : 1 unit and inb(i) -> oub(i) : k units
        - each girl node as 2 vertices - ing(i), oug(i)
            oug(i) -> sink : 1 unit and ing(i) -> oug(i) : k units
        
        if boy i and girl j like then inb(i) -> oug(j) : 1 unit
        else oub(i) -> ing(j) : 1 unit
    
    ans = 0
    // to simulate a dance matching : just find flow
    Find flow in each round :
        if flow == n :
            ans++
            add 1 to cap[source][inb(i)], cap[oug(i)][sink] so that next round can have flow n again if possible
        else break
	
   To better understand : see editorial (same approach)
   https://www.topcoder.com/tc?module=Static&d1=match_editorials&d2=srm399
*/


#include <bits/stdc++.h>
using namespace std;

typedef long long    ll;
typedef pair<int,int> PII;

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


class DancingParty {
public:
	int n, source, sink;
	int inb(int i) {	return i;	  }
	int oub(int i) {	return n+i;   }
	int ing(int i) {	return 2*n+i; }
	int oug(int i) {	return 3*n+i; }
	
	int maxDances(vector <string> likes, int k) {
		
		n = likes.size();
		source = 0, sink = 4*n+1;
		
		MF mf_init(4*n+2);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (likes[i-1][j-1] == 'Y') {
					mf_init.insertEdge(inb(i), oug(j), 1);
				} else {
					mf_init.insertEdge(oub(i), ing(j), 1);
				}
			}
		}
		
		for (int i = 1; i <= n; i++) {
			mf_init.insertEdge(source, inb(i), 1);
			mf_init.insertEdge(inb(i), oub(i), k);
			mf_init.insertEdge(ing(i), oug(i), k);
			mf_init.insertEdge(oug(i), sink, 1);
		}  
		
		int ans = 0;
		
		while (1) {
		
			int flow = mf_init.maxFlow(source, sink);
			
			if (flow != n)	break;
			ans++;
			
			for (int i = 1; i <= n; i++) {
				mf_init.cap[source][inb(i)]++;
				mf_init.cap[oug(i)][sink]++;
			}
		}
		return ans;
	}
};

<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
