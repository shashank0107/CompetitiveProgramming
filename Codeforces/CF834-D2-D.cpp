/*
    Author : manu_sy
    Idea : Similar to editorial idea1
*/
#include "bits/stdc++.h"
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
#define FOR(i,a,b)  for(int i=a;i<=b;++i)
#define LP(i,n)     for(int i=0;i< n;++i)
 
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
 
const int N = 4e4+7;
const int K = 52;

/** Template Ends **/
int n;
int k;
int a[N];
int dp[N][K];
int prv[N];
int li[N];

struct SegTreeLazy {
    #define N (1 << 16)
    int t[4 * N + 7];
    int lazy[4 * N + 7];
    void init() {
        memset(t, 0, sizeof t);
        memset(lazy, 0, sizeof lazy);
    }
    void push(int v, int tl, int tr) {
        t[v] += lazy[v];
        if (tl != tr) {
            lazy[2 * v] += lazy[v];
            lazy[2 * v + 1] += lazy[v]; 
        }
        lazy[v] = 0;
    }
    void add(int v, int tl, int tr, int l, int r, int val) {
        push(v, tl, tr);
        if (tl > r || tr < l)   return;
        if (l <= tl && tr <= r) {
            lazy[v] += val;
            push(v, tl, tr);
            return;
        }
        int mid = (tl + tr) / 2;
        add(2 * v, tl, mid, l, r, val);
        add(2 * v + 1, mid + 1, tr, l, r, val);
        t[v] = max(t[2 * v], t[2 * v + 1]);
    }
    void add(int l, int r, int val) {
        add(1, 0, n, l, r, val);
    }
    int query(int v, int tl, int tr, int l, int r) {
        push(v, tl, tr);
        if (tl > r || tr < l)   return -10000000;
        if (l <= tl && tr <= r) return t[v];
        int mid = (tl + tr) / 2;
        return max(query(2*v, tl, mid, l, r), query(2*v+1, mid+1, tr, l, r));
    }
    int query(int l, int r) {
        return query(1, 0, n, l, r);
    }
}seg;

signed main() {
 
    IOS;
    cin >> n >> k;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,n) {
        prv[i] = li[a[i]];
        li[a[i]] = i;
    }
    FOR(i,0,k-1) {
        seg.init();
        FOR(j,1,n) seg.add(j, j, dp[i][j]);
        FOR(j,1,n) {
            int x = prv[j];
            seg.add(x, j - 1, 1);
            dp[i + 1][j] = seg.query(0, j - 1);
        }
    }
    cout << dp[k][n] << endl;

    return 0;
}
