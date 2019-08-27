/*
    Author : manu_sy
    
    Idea : Same as editorial 
      https://codeforces.com/blog/entry/69314
*/
#include <bits/stdc++.h>
using namespace std;

/** Template Begins **/
//#define int ll
typedef long long        ll;
typedef pair<int,int>    PII;

#define IOS         ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl        '\n'
#define pb          push_back
#define F           first
#define S           second
#define mp          make_pair
#define FOR(i,a,b)  for(int i=a;i<=b;i++)

/* Debug */
template<class L, class R> ostream &operator<<(ostream &os, pair<L,R> P) {
  return os << "(" << P.st << "," << P.nd << ")";
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

const int N = 5e5+7;
const int NN = 710;

/** Template Ends **/
int q, idx, val;
ll ans[NN][NN];
ll a[N];

signed main() {

    IOS;
    int q;  cin >> q;
    while (q--) {
        int t;  cin >> t;
        
        if (t == 1) {
            cin >> idx >> val;  
            a[idx] += val; 

            for (int x = 1; x < NN; x++) {
                ans[x][idx%x] += val;
            }
        } else {
            int x, y;   cin >> x >> y;

            if (x < NN) {
                cout << ans[x][y] << endl;
            } else {
                ll ret = 0;
                for (int i = y; i < N; i+=x)
                    ret += a[i];
                cout << ret << endl;
            }
        }
    }

    return 0;
}
