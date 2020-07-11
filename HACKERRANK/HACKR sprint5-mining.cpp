/*
    Author : manu_sy
    Idea : Dp can be easily reduced to dp[i][j] = min (k < j) {dp[i - 1][k] + C[k][j]}
           which can be solved using dp divide and conquer
           Note : This solution is TLE althought divide and conquer is correct (just the the TL is low)
*/
#include "bits/stdc++.h"
using namespace std;
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
/** Template Begins **/
// #define int ll
typedef long long        ll;
typedef pair<int,int>    PII;
 
#define IOS         ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl        '\n'
#define pb          push_back
#define F           first
#define S           second
#define mp          make_pair
#define all(a)      (a).begin(), (a).end()
#define FOR(i,a,b)  for(int i=a;i<=b;++i)
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
 
const int N = 5e3+7;
const ll INF = 1e15;

/** Template Ends **/
int n;
int k;
ll c[N][N];
ll dp[N][N];
ll x[N];
ll w[N], sxw[N], sw[N];

inline ll sum(int i, int j, ll a[]) {
    return a[j] - a[i - 1];
}
inline ll getc(int i, int j, int z) {
    ll pr = (z > i + 1 ? x[z] * sum(i + 1, z, sw) - sum(i + 1, z, sxw) : 0);
    ll af = (z < j ? sum(z + 1, j, sxw) - x[z] * sum(z + 1, j, sw) : 0);
    return pr + af;
}
inline ll cost(int i, int j) {
    return c[i - 1][j];
}
inline void compute(int i , int l , int r , int ql , int qr){
    if(r < l){
        return;
    }
    int mid = l + r >> 1;
    int idx = -1;
    ll val = INF;
    for(int j = ql ; j <= min(qr , mid) ; ++j){
        ll tmp = dp[i - 1][j - 1] + cost(j , mid);
        if(tmp <= val){
            val = tmp;
            idx = j;
        }
    }
    dp[i][mid] = val;
    compute(i , l , mid - 1 , ql , idx);
    compute(i , mid + 1 , r , idx , qr);
}
signed main() {
 
    IOS;
    cin >> n >> k;
    FOR(i,1,n) {
        cin >> x[i] >> w[i];
    }
    FOR(i,1,n) {
        sw[i] = sw[i - 1] + w[i];
        sxw[i] = sxw[i - 1] + w[i] * x[i];
    }
    FOR(i,0,n-1) {
        int z = i + 1;
        FOR(j,i+1,n) {
            while (z < j && getc(i, j, z + 1) <= getc(i, j, z))
                z++;
            c[i][j] = getc(i, j, z);
        }
    }
    FOR(i,1,n) dp[1][i] = cost(1,i);
    FOR(i,2,n) {
        compute(i, 1, n, 1, n);
    }
    cout << dp[k][n] << endl;
 
    return 0;
}
