/*
    Author : manu_sy
    Idea : meet in the middle
            iterate from left to right 
          - we will change the the last m / 2 bits of number and store it in cnt[num][dist]
          - Iterate over the changes in the first m / 2 bits and then use cnt[num][dist] to get answers 
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
#define FOR(i,a,b)  for(int i=(a), _b=(b);i<=_b;++i)
#define LP(i,n)     for(int i=0, _n=(n);i< _n;++i)

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

const int N = 2e5+7;
const int M = 18;

/** Template Ends **/
int n, a[N], m, ans[N][M];
int cnt[N][M];

signed main() {

    IOS;
    cin >> n >> m;
    LP(i,n) cin >> a[i];
    int mid = m / 2;

    LP(i,n)
    {
        LP(mask,(1 << mid))
        {
            int num = a[i] ^ mask;
            int ham = __builtin_popcount(mask);
            LP(dist,m-mid+2)    
            {
                ans[i][ham + dist] += cnt[num][dist];    
            }
        }
        LP(mask,(1 << (m - mid)))
        {
            int n_mask = mask << mid;
            int num = a[i] ^ n_mask;
            int ham = __builtin_popcount(mask);
            cnt[num][ham]++;
        }
    }
    LP(i,n) {
        LP(j,m+1) {
            if (j) cout << " ";
            cout << ans[i][j];
        } cout << endl;
    }

    return 0;
}
