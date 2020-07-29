/*
    Author : manu_sy
    Idea : Similar to editorial - diff is just when we have choice element <= c, then if we can remove elements using a and b also then do that else remove using a + b
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
 
const int N = 2e5+7;
 
/** Template Ends **/
int n, a[3];
multiset<int> m;

int rem(int x) {
    auto it = m.upper_bound(x);
    if (it == m.begin())    return 0;
    it--;
    m.erase(it);
    return 1;
}

signed main() {
 
    IOS;
    cin >> n;
    LP(i,3) cin >> a[i];
    LP(i,n) {
        int x;  cin >> x;
        m.insert(x);
    }
    sort(a, a + 3);
    if (*m.rbegin() > a[0] + a[1] + a[2]) {
        cout << -1 << endl;
        return 0;
    }
    int ans = 0;
    while (!m.empty()) {
        auto p = m.end();
        p--;
        int e = *p;
        m.erase(p);
        ans++;
        if (a[2] >= e) {
            auto it = m.upper_bound(a[1]);
            if (it != m.begin())    it--;
            if (it == m.begin()) {
                rem(a[0] + a[1]);
                continue;
            }
            it--;
            it = m.upper_bound(a[0]);
            if (it == m.begin()) {
                rem(a[0] + a[1]);
                continue;
            }
            rem(a[0]);
            rem(a[1]);
        } else if (a[0] + a[1] >= e) {  
            rem(a[2]); 
        } else if (a[0] + a[2] >= e) {
            rem(a[1]);
        } else if (a[1] + a[2] >= e) {
            rem(a[0]);
        }
    }
    cout << ans << endl;
    return 0;
}
