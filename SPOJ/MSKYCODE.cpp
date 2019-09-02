/*
    Author : manu_sy
    
    Idea : Same as https://github.com/aboodJAD/CompetitiveProgramming/blob/master/SPOJ/MSKYCODE-%20Sky%20Code.cpp
    
    Solution using mobius funcition :
      https://github.com/thackerhelik/spoj/blob/master/SPOJ_MSKYCODE.cpp
*/
#include <bits/stdc++.h>
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

const int N = 1e4+7;

/** Template Ends **/

int n, ans[N], cnt[N];

int nc4(int n) {
    return (n*(n-1)*(n-2)*(n-3))/(24);
}

signed main() {

    IOS;
    while (cin >> n) {
        int mx = -1;
        LP(i,n) {
            int x;  cin >> x;
            cnt[x]++;
            mx = max(mx, x);
        }

        int ret = 0;
        for (int g = mx; g > 1; g--) {

            int c = 0;
            for (int i = g; i <= mx; i+=g)  c += cnt[i];
            ans[g] += nc4(c);
            ret += ans[g];

            for (int i = 2; i*i <= g; i++) {
                if (g%i == 0) {
                    ans[i] -= ans[g];
                    if (i*i != g)   ans[g/i] -= ans[g];
                }
            }
        }
        for (int i = 0; i <= mx; i++)   ans[i] = 0, cnt[i] = 0;
        cout << nc4(n) - ret << endl;
    }

    return 0;
}
