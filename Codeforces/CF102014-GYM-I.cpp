/*
    Author : manu_sy
    Idea : Same as https://github.com/ZeyadKhattab/Competitive-Programming/blob/master/Codeforces/Gyms/102014/CF102014-GYM-I.java
          - Observe that you can divide a[] into independent sequences and solve them seperately :
            - Like seq1 = 1, 2, 4, 8, 16, ... belong to one whereas seq2 = 3, 6, 12, 24, ... belong to another and so one
            - Observe that if a tree is composed of no.s from seq1 then it can't have any other no.s other than those from seq1
            - Also seq like : a*1, a*2, a*4, a*8, ... (a % 2 != 0) is same as 1, 2, 4, 8, ...
          - So we just need to solve the reduced problem :
            Given a sequence of powers of 2, find the max length of seq that can form the tree
            - This is solved using dp[i][j] : max length of subsequence with sum = j using elements from 0 till i
            - Answer will be max(dp[n - 1][k]) where k is a power of 2 (observe that only when k is a power of 2 that you can have a tree, since left = right always) 
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
 
const int N = 5e5+7, M = 5e2 + 5;
 
/** Template Ends **/
int n;
vector<int> adj[M];
int dp[N];

int solve(vector<int>& v) {
    if (v.empty())  return 0;
    debug(v);
    int tot = 0;
    for (auto i : v) tot += i;
    LP(i,N) dp[i] = -N;
    dp[0] = 0;
    for (auto x : v)
        for (int sum = (tot / x) * x; sum >= x; sum -= x)
            dp[sum] = max(dp[sum], 1 + dp[sum - x]);
    int ans = 1;
    for (int i = 1; i <= tot; i <<= 1) ans = max(ans, dp[i]);
    return ans;
} 

signed main() {
 
    IOS;
    while (cin >> n) {
        if (n == 0)
            break;
        LP(i,M) adj[i].clear();
        LP(i,n) {
            int x;  cin >> x;
            int pw = 1;
            while (x % 2 == 0) {
                x /= 2;
                pw <<= 1;
            }
            adj[x].pb(pw);
        }
        int ans = 1;
        LP(i,M) ans = max(ans, solve(adj[i]));
        cout << ans << endl;
    }
    return 0;
}
