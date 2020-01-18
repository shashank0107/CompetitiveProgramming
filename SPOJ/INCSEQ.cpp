/*
    Author : manu_sy
    
    Idea : Iterate from i = 0 to n - 1 
          - find count of seq of length j (0 < j <= k) which can end at a[i]
          - achieved simply by keeping k bits
          - update bit for the next iteration
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
const int K = 50+3;
const int hell = 5e6;

/** Template Ends **/
int n, a[N], k;

struct BIT {
    vector<int> bit;
    int n;
    
    BIT(): n(N-1) {
        bit.assign(N-1, 0);
    }
    void add(int idx, int val) {
        for (++idx; idx < n; idx += idx & -idx)
            bit[idx] = (bit[idx] + val) % hell;
    }
    int sum(int idx) {
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret = (ret + bit[idx]) % hell;
        return ret;
    }
    int sum(int l, int r) {
        return sum(r) - sum(l-1);
    }
} bt[K];


signed main() {

    IOS;
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i], a[i]++;

    bt[0].add(0, 1);
    for (int i = 0; i < n; i++)
    {
        for (int j = k; j > 0; j--)
        {
            int cur = bt[j - 1].sum(a[i] - 1);
            bt[j].add(a[i], cur);
        }
    }
    int ans = bt[k].sum(0, N - 3);
    cout << ans << endl;

    return 0;
}
