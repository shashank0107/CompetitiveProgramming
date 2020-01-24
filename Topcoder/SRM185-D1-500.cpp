/*
    Author : manu_sy
    Idea : just simulate the algorithm mentioned in the problem statement
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

const int N = 1e5+7;

/** Template Ends **/

void dfs(int v, int start, vector<string>& adj, vector<int>& path, int& edge_cnt, bool begin, vector<int>& deg) {
    path.pb(v);
    if (!begin && v == start)   return;

    for (int i = 0; i < adj.size(); i++) if (adj[v][i] == '1') {
        adj[v][i] = '0';
        adj[i][v] = '0';
        deg[i]--, deg[v]--;
        edge_cnt++;
        dfs(i, start, adj, path, edge_cnt, false, deg);
        return;
    }
}

class EulerianRace {
public:
    vector <int> planRoute(vector <string> bridges) {
        int n = bridges.size(), total = 0;
        vector<int> deg(n, 0);
        for (int i = 0; i < n; i++) 
            for (int j = i + 1; j < n; j++) 
                if (bridges[i][j] == '1')
                    total++, deg[i]++, deg[j]++;

        if (total == 0) return vector<int>(1, 0);
        vector<int> path;
        int edge_cnt = 0;
        path.pb(0);

        while (edge_cnt != total) {
            
            int pos = -1;
            for (int i = 0; i < path.size(); i++) {
                if (deg[path[i]]) {
                    pos = i;
                    break;
                }
            }
            assert(pos != -1);
            vector<int> temp;
            dfs(path[pos], path[pos], bridges, temp, edge_cnt, true, deg);
            path.insert(path.begin() + pos + 1, temp.begin() + 1, temp.end());
        }
        return path;
    }
};
