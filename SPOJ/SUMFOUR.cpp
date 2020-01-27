/*
    Author : manu_sy
    Idea : meet in middle
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

const int N = 1e5+7;

/** Template Ends **/
int n;
vector<int> v;

int count(int x) {
    int r = upper_bound(all(v), x) - v.begin() - 1;
    if (r >= v.size() || r < 0 || v[r] != x) return 0;
    int l = lower_bound(all(v), x) - v.begin();
    return r - l + 1;
}

signed main() {

    IOS;
    cin >> n;
    vector<int> a(n), b(n), c(n), d(n);
    LP(i,n) cin >> a[i] >> b[i] >> c[i] >> d[i];
    map<int, int> m;
    for (auto i : a) for (auto j : b)   v.pb(i + j);
    sort(all(v));
    ll ans = 0;
    for (auto i : c) for (auto j : d)   ans += count(- i - j);
    cout << ans << endl;

    return 0;
}
