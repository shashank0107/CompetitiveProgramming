/*
    Author : manu_sy
    
    Idea : same as 	
      https://www.quora.com/How-do-I-solve-SPOJ-com-Problem-MSE06H-using-BIT
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

/** Template Ends **/

struct BIT {
    vector<int> bit;
    int n;

    BIT (int n): n(n+1) {
        bit.assign(this->n, 0);
    } 
    void add (int idx, int val) {
        for (int j = idx+1; j < n; j += j & -j)
            bit[j] += val;
    }
    int sum (int idx) {
        int ret = 0;
        for (int j = idx+1; j > 0; j -= j & -j)
            ret += bit[j];
        return ret;
    }
    int sum (int x, int y) {
        return sum(y) - sum(x-1);
    }
};

signed main() {

    IOS;
    int t;  cin >> t;
    for (int tc = 1; tc <= t; tc++)
    {
        int n, m, k;    cin >> n >> m >> k;
        
        vector<PII> edges(k);
        for (int i = 0; i < k; i++) cin >> edges[i].F >> edges[i].S;
        sort(all(edges));

        BIT bt(m+1);
        debug(edges);

        ll ans = 0;
        for (auto e : edges)
        {
            int x = e.F, y = e.S;
            ans += bt.sum(y+1, m);
            bt.add(y, 1);
        }
        cout << "Test case " << tc << ": " << ans << endl;
    }

    return 0;
}
