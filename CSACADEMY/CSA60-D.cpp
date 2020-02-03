/*
    Author : manu_sy
    Idea : Just basic meet-in-middle. 
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

const int N = 40+7;
const int INF = 1e9+7;
/** Template Ends **/
int n, r[N], b[N], ans, diff;
vector<pair<int, PII>> v;

void check(int can) {
    int on = __builtin_popcountll(can);
    int off = n - on;
    if (abs(on - off) < diff) {  
        ans = can, diff = abs(on - off);
    }
}

signed main() {

    IOS;
    cin >> n;
    LP(i,n) cin >> r[i] >> b[i];

    int mid = (n)/ 2;
    for (int mask = 0; mask < (1LL << mid); mask++)
    {
        int rr = 0, bb = 0, rcnt = 0;
        LP(bit,mid) 
        {
            if ((mask >> bit) & 1LL)  rr += r[bit], rcnt++;   
            else bb += b[bit];
        }
        v.pb(mp(rr - bb, mp(rcnt - (mid - rcnt), mask)));
    }
    sort(all(v));

    diff = INF;
    LP(mask, (1 << (n - mid)))
    {
        int rr = 0, bb = 0, rcnt = 0;
        LP(bit,n-mid)
        {
            if ((mask >> bit) & 1LL)  rr += r[bit + mid], rcnt++;   
            else bb += b[bit + mid];
        }
        int df = rr - bb;
        pair<int, PII> uu = mp(-df, mp(INF, 0)), dd = mp(-df, mp(-INF, 0));

        int u = upper_bound(all(v), uu) - v.begin();
        int l = lower_bound(all(v), dd) - v.begin();
        if (u == l) continue;

        pair<int, PII> lo = v[l];  assert(lo.F == -df);
        pair<int, PII> hi = v[u - 1];  assert(hi.F == -df);

        check(lo.S.S | (mask << mid));
        check(hi.S.S | (mask << mid));
    }

    if (diff == INF)   cout << -1 << endl;
    else 
    {
        int rr = 0, bb = 0;
        LP(i,n) 
            if ((ans >> i) & 1) cout << 0, rr += r[i];
            else cout << 1, bb += b[i];
        assert(rr == bb);
        cout << endl;
    }

    return 0;
}
