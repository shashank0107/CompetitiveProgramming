/*
  Author : manu_sy
  
  Idea : Same as editorial -
        https://apps.topcoder.com/wiki/display/tc/SRM+460
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

const int N = 11;

class TheCitiesAndRoadsDivTwo {
public:
    int parent[N], n, ans;
    vector<PII> edges;

    int find_set(int v) {
        if (parent[v] == v) return v;
        return find_set(parent[v]);
    }
    void union_sets(int u, int v) {
        u = find_set(u), v = find_set(v);
        if (u != v)
            parent[u] = v;
    }
    
    void go(int idx, int taken) {
        if (taken == n-1) {
            ans++;  return;
        }
        if (idx == edges.size())  return;

        int u = edges[idx].F, v = edges[idx].S;
        if (find_set(u) == find_set(v)) {
            go(idx+1, taken);
        } else {
            int uu = find_set(u), vv = find_set(v);
            union_sets(uu,vv);
            go(idx+1, taken+1);
            parent[uu] = uu, parent[vv] = vv;
            
            go(idx+1, taken);
        }
    }
    
    int find(vector <string> g) {
        
        n = g.size();
        for (int i = 0; i < n; i++) parent[i] = i;
        
        edges.clear();
        int taken = 0;
        for (int i = 0; i < n; i++) for (int j = i+1; j < n; j++) if (g[i][j] == 'Y') {
            assert(find_set(i) != find_set(j));
            if (find_set(i) == find_set(j)) cout << "Yo" << endl;
            union_sets(i,j), taken++;
        } else edges.pb(mp(i,j));
    
        ans = 0;        
        go(0, taken);

        return ans;
    }
};

<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
