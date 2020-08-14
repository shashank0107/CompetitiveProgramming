/*
    Author : manu_sy
    Idea : Same as editorial
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
 
    // IOS;
    int t; cin >> t;
    while (t--) {
        int n, b, f;    cin >> n >> b >> f;

        vector<int> res(n);
        for (int bit = 0; bit < 4; bit++) {
            string cur = "";
            
            for (int i = 0; i < n; i++) {
                int num = i % 16;

                int cb = (num >> bit) & 1;
                cur += to_string(cb); 
            }
            cout << cur << endl;
            
            string tmp; cin >> tmp;
            // assert(tmp != "-1");

            LP(i,n-b) res[i] |= ((int)(tmp[i] - '0')) << bit;
        }

        for (int i = 0, ci = 0; i < n; i++) {
            int num = i % 16;

            if (res[ci] == num) ci++;
            else cout << i << " ";
        }
        cout << endl;
        string q; cin >> q;
        // assert(q = "1");
    }  

    return 0;
}
