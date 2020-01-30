/*
    Author : manu_sy
    Idea : meet in middle 
           Cover half (n + m) / 2 steps from top and store all xors ending at pos i,j in v[i][j]
           Cover the rest half steps from bottom right and at every ending position i,j check if xr ^ k is present in v[i][j]
*/
#include "bits/stdc++.h"
using namespace std;
 
/** Template Begins **/
#define int              ll 
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
 
const int N = 20+3;
 
/** Template Ends **/
int n, m, k, a[N][N], ans;
vector<int> v[N][N];
 
int count(vector<int>& v, int x) {
    int u = upper_bound(all(v), x) - v.begin() - 1;
    if (u >= v.size() || u < 0 || v[u] != x)    return 0;
    int l = lower_bound(all(v), x) - v.begin();
    return u - l + 1;
}
void move1(int i, int j, int steps, int xr) {
    xr ^= a[i][j];
    if (steps == (n + m) / 2)
    {
        v[i][j].pb(xr);
        return;
    }
    if (i + 1 < n)  move1(i + 1, j, steps + 1, xr);
    if (j + 1 < m)  move1(i, j + 1, steps + 1, xr);
}
void move2(int i, int j, int steps, int xr) {
    if (steps == (n + m + 1) / 2)
    {
        ans += count(v[i][j], xr ^ k);
        return;
    }
    xr ^= a[i][j];
    if (i - 1 >= 0)  move2(i - 1, j, steps + 1, xr);
    if (j - 1 >= 0)  move2(i, j - 1, steps + 1, xr);
}
signed main() {
 
    IOS;
    cin >> n >> m >> k;
    LP(i,n) LP(j,m) cin >> a[i][j];
    move1(0, 0, 1, 0);
    LP(i,n) LP(j,m) sort(all(v[i][j]));
    
    move2(n - 1, m - 1, 1, 0);
    cout << ans << endl;
 
    return 0;
}
