/*
    Author : manu_sy
    Idea : 1. Choose highest ranked player - we have handled n / 2 players now
           2. Now choose next player from n / 2 - 1 till n - 1 ranks - now we have handled n / 4 more players
           3. Do above till you handle all players above our friend
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
 
#ifdef LOCALi
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif
 
/* Debug Ends */
 
const int N = 5e6+7;
 
/** Template Ends **/
int n, a[N], idx;
 
signed main() {
 
    IOS;
    cin >> n;
    FOR(i,1,n) {
        cin >> a[i];
        if (a[i] == -1) idx = i;
    }
    int left = n - idx;
    int ans = 0, cur = n;
    priority_queue<int, vector<int>, greater<int> > q;
    for (int x = n / 2; x >= 1 && left > 0; x >>= 1) {
        debug(a[cur]);
        q.push(a[cur--]);
        left--;
        ans += q.top(); debug(q.top()); q.pop();
        LP(i,min(x - 1, left)) debug(a[cur]), q.push(a[cur--]);
        left -= (x - 1);
    }
    cout << ans << endl;
 
    return 0;
}
