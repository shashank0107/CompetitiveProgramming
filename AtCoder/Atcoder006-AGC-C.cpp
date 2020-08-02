/*
    Author : manu_sy
    Idea : Same as https://github.com/Ahmed-Zaher/CompetitiveProgramming/blob/master/AtCoder/Atcoder006-AGC-C.cpp#L150
*/
#include "bits/stdc++.h"
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
int n, m, k;
double x[N], d[N];
int p[N];
bool vis[N];
int df[N];

signed main() {
 
    IOS;
    cout << fixed << setprecision(15);
    cin >> n;
    FOR(i,1,n) cin >> x[i];
    FOR(i,1,n-1) d[i] = x[i + 1] - x[i];
    FOR(i,1,n) p[i] = i;

    cin >> m >> k;
    LP(i,m) {
        int x; cin >> x;
        swap(p[x], p[x - 1]);
    }

    FOR(i,1,n-1) {
        vector<int> cyc;
        int cur = i;
        while (!vis[cur]) {
            cyc.pb(cur);
            vis[cur] = 1;
            cur = p[cur];
        }
        for (int j = 0; j < cyc.size(); j++) {
            int p = cyc[j];
            int q = cyc[(j + k) % cyc.size()];
            df[cyc[j]] = d[cyc[(j + k) % cyc.size()]]; 
        }
    }
    cout << x[1] << endl;
    FOR(i,2,n) {
        x[i] = x[i - 1] + df[i - 1];
        cout << x[i] << endl;
    }

    return 0;
}
