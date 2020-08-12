/*
    Author : manu_sy
    Idea : parallel binary search
           Similar to http://ideone.com/Dm2x4M
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
 
const int N = 5e6+7;
const int MOD = 1e9 +7;

/** Template Ends **/

struct query {
    int l, r, m, k, res;
} q[105];

int qn;
int cnt[105];


class LimitedMemorySeries1{
public:
    void upd(int x) {
        int lo = 0, hi = qn - 1, p = qn;
        while (lo <= hi) {
            int mid = (hi + lo) >> 1;
            if (q[mid].m < x)   
                lo = mid + 1;
            else {
                p = min(p, m);
                hi = mid - 1;
            }
        }
        cnt[p]++;
    }
    long long getSum(int n, int x0, int a, int b, vector <int> que) {
        sort(all(que));
        qn = que.size();
        for (int i = 0; i < qn; i++)    q[i] = {0, MOD - 1, 0, que[i], MOD - 1};
        
        for (int t = 0; t < 32; t++) {
            for (int i = 0; i < qn; i++)    q[i].m = (q[i].l + q[i].r) >> 1;
            sort(q, q + qn, [] (query a, query b) {
                return a.m < b.m;
            });
            memset(cnt, 0, sizeof cnt);

            ll x = x0;
            for (int i = 0; i < n; i++) {
                upd(x);
                x = (a * x + b) % MOD;
            }
            for (int i = 1; i < qn; i++) cnt[i] += cnt[i - 1];
            for (int i = 0; i < qn; i++) {
                if (cnt[i] > q[i].k)
                    q[i].r = q[i].m - 1, q[i].res = min(q[i].res, q[i].m);
                else 
                    q[i].l = q[i].m + 1;
            }
        }
        ll ans = 0;
        for (int i = 0; i < qn; i++)    ans += q[i].res;

        return 0LL;
    }
};
