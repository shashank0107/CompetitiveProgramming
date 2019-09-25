/*
    Author : manu_sy

    Idea : Mincut in an undirected graph 
          - Stoer wagner algorithm
*/
#include <bits/stdc++.h>
using namespace std;

/** Template Begins **/
#define int ll
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
const int maxN = 300+7;
const int maxint = 1e9+7;

/** Template Ends **/
int n, m;

/* Stoer Wagner */
int g[maxN][maxN], v[maxN], d[maxN], vis[maxN];

int stoer_wagner(int n) {
  int res = maxint;
  for (int i = 1; i <= n; i++) v[i] = i, vis[i] = 0;
  while (n > 1) {
    int p = 2, prev = 1;
    for (int i = 2; i <= n; ++i) {
      d[v[i]] = g[v[1]][v[i]];
      if (d[v[i]] > d[v[p]]) p = i;
    }
    vis[v[1]] = n;
    for (int i = 2; i <= n; ++i) {
      if (i == n) {
        res = min(res, d[v[p]]); // if d[v[p]] < res, then s = v[p] & t = v[prev]
        for (int j = 1; j <= n; ++j) {
          g[v[prev]][v[j]] += g[v[p]][v[j]];
          g[v[j]][v[prev]] = g[v[prev]][v[j]];
        }
        v[p] = v[n--];
        break;
      }
      vis[v[p]] = n;
      prev = p;
      p = -1;
      for (int j = 2; j <= n; ++j) {
        if (vis[v[j]] != n) {
          d[v[j]] += g[v[prev]][v[j]];
          if (p == -1 || d[v[p]] < d[v[j]]) p = j;
        }
      }
    }
  }
  return res;
}
/* Stoer Wagner Ends */

signed main() {

    IOS;
    int s;
    while (cin >> n >> m >> s) {
        if (n == 0 && m == 0 && s == 0) break;

        memset(g, 0, sizeof g);
        while (m--) {
            int a, b, w;    cin >> a >> b >> w;
            g[a][b] += w;
            g[b][a] += w;
        }
        cout << stoer_wagner(n) << endl;
    }

    return 0;
}
