/*
    Author : manu_sy
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

const int N = 34+5;

/** Template Ends **/

/* Policy based DS */
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<
PII,
null_type,
less<PII>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;
/* PBDS ends */

int n, a[N], l, r;
ordered_set s;
vector<int> s2;
map<int, int> m;

ll calc(int x) {
    ll ans = 0;
    for (auto ss : s2) {
        ans += s.order_of_key(mp(x - ss, INT_MAX));
    }
    return ans;
}

signed main() {

    IOS;
    cin >> n >> l >> r;
    LP(i,n) cin >> a[i];
    sort(a, a + n);
    vector<int> a1(a, a + n / 2);
    vector<int> a2(a + n / 2, a + n);
    // debug(a1, a2);

    int n1 = a1.size(), n2 = a2.size();
    for (int mask = 0; mask < (1 << n1); mask++) {
        int sum = 0;
        LP(bit,n1) if ((mask>>bit)&1)   sum += a1[bit];
        m[sum]++;
        s.insert(mp(sum, m[sum]));
    }
    LP(mask,(1<<n2)) {
        int sum = 0;
        LP(bit,n2)  if ((mask>>bit)&1)  sum += a2[bit];
        s2.pb(sum);
    }
    cout << calc(r) - calc(l - 1) << endl;

    return 0;
}
