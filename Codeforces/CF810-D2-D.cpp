/*
    Author : manu_sy
    Idea : Same as editorial - https://codeforces.com/blog/entry/52099
*/
#include "bits/stdc++.h"
using namespace std;
 
/** Template Begins **/
 
typedef long long        ll;
typedef pair<int,int>    PII;
 
#define IOS         ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
// #define endl        '\n'
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
 
/** Template Ends **/

 
signed main() {
 
    IOS;
    int n;
    int k;
    cin >> n >> k;
    auto q = [&] (int x, int y) {
        cout << 1 << " " << x << " " << y << endl;
        string res;
        cin >> res;
        return (res == "TAK" ? 1 : 0);
    };
    auto is_valid = [&] (int x) {
        if (x != 1 && !q(x, x -1)) {
            return 0;
        }
        if (x != n && !q(x, x + 1)) {
            return 0;
        }
        return 1;
    };
    auto bs = [&] (int l, int r) {
        debug(l, r);
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (q(m, m + 1)) r = m;
            else l = m;
        }
        debug("final : ", l, r);
        FOR(i,l,r) if (is_valid(i)) {
            debug(i);
            return i;
        }
        debug(-1);
        return -1;
    };
    int p = bs(1, n);
    int left = bs(1, p - 1);
    debug(left);
    int right = (left == -1 ? bs(p + 1, n) : -1);
    cout << 2 << " " << p << " " << (left != -1 ? left : right) << endl;

    return 0;
}
