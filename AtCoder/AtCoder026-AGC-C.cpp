/*
    Author : manu_sy
    Idea : meet in middle
           - Similar to https://github.com/SpeedOfMagic/CompetitiveProgramming/blob/master/AtCoder/AtCoder026-AGC-C.cpp
             just done without any hasing : to store a pair of strings - place a delimiter in between
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

const int N = 18+2;

/** Template Ends **/
int n;
char a[N], b[N];

signed main() {

    IOS;
    cin >> n;
    LP(i,n) cin >> a[i];
    LP(i,n) cin >> b[i];
    map<string, int> m;
    LP(mask,(1 << n)) {
        string r1 = "", b2 = "";
        LP(bit,n) ((mask>>bit)&1) ? r1 += a[bit] : b2 += a[bit];
        reverse(all(b2));
        m[r1+"#"+b2]++;
    }
    ll ans = 0;
    LP(mask,(1<<n)) {
        string b1 = "", r2 = "";
        LP(bit,n) ((mask>>bit)&1) ? r2 += b[bit] : b1 += b[bit];
        reverse(all(b1));
        ans += m[b1+"#"+r2];
    }
    cout << ans << endl;

    return 0;
}
