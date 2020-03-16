/*
    Author : manu_sy
    Idea : Same as editorial - https://codeforces.com/blog/entry/10157
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
 
const int N = 1e2+7;
const int M = 1e7;
/** Template Ends **/

int dp[M], n, m, a[N], id[N];
char q[N];

int calc(int mask, int ii) 
{
	if (mask == 0 || ii == m)	return 0;
	int &ret = dp[mask];
	if (ret != -1)	return ret;
	ret = id[ii] == 1 ? INT_MIN : INT_MAX;
	LP(bit,m) if ((mask >> bit)&1) 
	{
		int nmask = mask ^ (1 << bit);
		if (id[ii] == 1)
		{
			if (q[ii] == 'p')	ret = max(ret, calc(nmask, ii + 1) + a[bit]);
			else 				ret = max(ret, calc(nmask, ii + 1));
		}
		else
		{
			if (q[ii] == 'p')	ret = min(ret, calc(nmask, ii + 1) - a[bit]);
			else 				ret = min(ret, calc(nmask, ii + 1));
		}
	}
	return ret;
} 

signed main() {
 
    IOS;
    cin >> n;
    LP(i,n) cin >> a[i];
    cin >> m;
    LP(i,m) cin >> q[i] >> id[i];

    sort(a, a + n, greater<int>());
    memset(dp, -1, sizeof dp);
    cout << calc((1 << m) - 1, 0) << endl;
 
    return 0;
}
