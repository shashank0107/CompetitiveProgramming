/*
    Author : manu_sy
    Idea : mid = n / 2
          - Iterate from 1 to mid where each element has 3 choice to be included in left, right, donot include
            while changing the mask if it is include
          - When reach mid store (lsum - rsum, mask) in a vector v
          - Similarly do for mid to n and when you reach n :
            search for all values -(lsum-rsum, any_mask) in v and mark any_mask | mask as valid
          - Finally count all the valid masks
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

const int N = (1 << 23) + 5;

/** Template Ends **/
int n, a[25], mid, ans;
vector<pair<int, int> > v;
bool valid[N];

void make1(int idx, int lsum, int rsum, int mask) {
    if (idx == mid)
    {
        v.pb(mp(lsum - rsum, mask));
        return;
    }
    make1(idx + 1, lsum + a[idx], rsum, mask | (1 << idx));
    make1(idx + 1, lsum, rsum + a[idx], mask | (1 << idx));
    make1(idx + 1, lsum, rsum, mask);
}
void make2(int idx, int lsum, int rsum, int mask) {
    if (idx == n)
    {
        int x = lsum - rsum;
        PII shi = mp(-x, 1e9), slo = mp(-x, -2);
        int hi = upper_bound(all(v), shi) - v.begin();
        int lo = lower_bound(all(v), slo) - v.begin();
        
        FOR(i,lo,hi-1) valid[mask | v[i].S] = true;
        return;
    }
    make2(idx + 1, lsum + a[idx], rsum, mask | (1 << idx));
    make2(idx + 1, lsum, rsum + a[idx], mask | (1 << idx));
    make2(idx + 1, lsum, rsum, mask);
}

signed main() {

    IOS;
    cin >> n;
    LP(i,n) cin >> a[i];
    mid = n / 2;

    make1(0, 0, 0, 0);
    sort(all(v));
    make2(mid, 0, 0, 0);

    FOR(i,1,((1<<n)-1)) if (valid[i]) ans++;
    cout << ans << endl;

    return 0;
}
