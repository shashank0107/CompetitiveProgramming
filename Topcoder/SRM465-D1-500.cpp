/*
  Author : manu_sy
  
  Idea : Consider a graph as follows : 
    - All plants are connected to source with capcacity as the cost of destroying the plant
    - All bases are connected to sink with capacity as the cost of destroying the base
    - Connect all plants to bases with capacity infinity ( only those which are applicable ).
    - The mincut of the graph gives us the minimum cost.
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long    ll;
typedef pair<int, int> PII;

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

int sq(int x) { return x*x; }
int dist(int x1, int y1, int x2, int y2) {
  return sq(x1-x2) + sq(y1-y2);
}

class GreenWarfare {
public:
  int minimumEnergyCost(vector <int> canonX, vector <int> canonY, vector <int> baseX, vector <int> baseY, vector <int> plantX, vector <int> plantY, int energySupplyRadius) {
    
    int n = baseX.size(), m = plantX.size(), p = canonX.size();
    MF mf(m+n+2);
    int source = 0, sink = m+n+1;
    
    for (int i = 0; i < n; i++) {
      int cost = INF;
      for (int j = 0; j < p; j++) {
        cost = min(cost, dist(baseX[i], baseY[i], canonX[j], canonY[j]));
      }
      if (cost != INF)
      	mf.addEdge(m+i+1, sink, cost);
    }
    
    for (int i = 0; i < m; i++) {
      int cost = INF;
      for (int j = 0; j < p; j++) {
        cost = min(cost, dist(plantX[i], plantY[i], canonX[j], canonY[j]));
      }
      if (cost != INF)
      	mf.addEdge(source, 1+i, cost);
    }
    
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if ( dist(plantX[i], plantY[i], baseX[j], baseY[j]) <= sq(energySupplyRadius) ) {
          mf.addEdge(1+i, m+j+1, INF);
        }
      }
    }
    return mf.maxFlow(source, sink);
  }
};

<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
