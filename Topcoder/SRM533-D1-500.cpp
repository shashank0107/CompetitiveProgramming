/*
    Author : manu_sy
    Idea : Consider each magicbox (a[i][j]='#') as an edge b/w row i to column j
           Our (sequence) path can be considered like this :
           col0 -> rowi -> colj -> rowk -> colm -> ... where each edge is indicated as above
          - Now we just have to check if a euler path/cylce exists in this graph
          - Also note that if a euler path exists (2 nodes of odd degrees) then atleast one node should be a column,
            bcz the starting location can only be a column since we then have to move to a row in first step
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

struct UNF {
    vector<int> par, sz;
    UNF(int n) {
        par.resize(n); sz.resize(n);
        for (int i = 0; i < n; i++) make_set(i);
    }
    void make_set(int v) {
        par[v] = v, sz[v] = 1;
    }
    int find_set(int v) {
        if (v == par[v])    return v;
        return par[v] = find_set(par[v]);
    }
    void union_sets(int u, int v) {
        u = find_set(u);
        v = find_set(v);
        if (u != v) {
            if (sz[u] < sz[v])  swap(u, v);
            par[v] = u;
            sz[u] += sz[v];
        }
    }
};

class MagicBoard {
public:
    string ableToUnlock(vector <string> board) {
        int n = board.size(), m = board[0].size();
        vector<int> deg(m + n, 0);
        UNF uf(m + n);
        int start = -1;
        set<int> nodes;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) { 
                if (board[i][j] == '#') {
                    deg[i]++, deg[n + j]++;
                    uf.union_sets(i, n + j);
                    if (start == -1)    start = i;
                    nodes.insert(i), nodes.insert(n + j);
                }
            }
        }

        if (uf.sz[uf.find_set(start)] != nodes.size())  return "NO";

        int cnt = 0, f = -1;
        for (int i = n + m - 1; i >= 0; i--) if (deg[i] & 1) {
            if (f == -1)    f = i;
            cnt++;
        }

        if (cnt == 0 || (cnt == 2 && f >= n))    return "YES";
        else return "NO";
    }
};
