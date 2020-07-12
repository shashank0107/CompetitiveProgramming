/*
    Author : manu_sy
    Idea : dp knuth optimization
           See : http://maratona.ic.unicamp.br/MaratonaVerao2017/documents/dp.pdf
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
 
const int N = 250+7;
const int INF = 1e9;

/** Template Ends **/
int n;
int a[N];
int pa[N];
int dp[N][N];
int opt[N][N];

int calc(int i, int j) {
	if (i > j)	return 0;
	int &ret = dp[i][j];
	if (ret != -1)	return ret;
	if (i == j) {
		opt[i][j] = i;
		return ret = a[i];
	}
	calc(i, j - 1);
	calc(i + 1, j);
	ret = INF;
	FOR(k,opt[i][j - 1],opt[i+1][j]) {
		if (calc(i, k - 1) + calc(k + 1, j) + pa[j] - pa[i - 1] <= ret) {
			ret = calc(i, k - 1) + calc(k + 1, j) + pa[j] - pa[i - 1];
			opt[i][j] = k;
		}
	}
	return ret;
}

signed main() {
 
    IOS;
    while (cin >> n) {
    	FOR(i,1,n) cin >> a[i], pa[i] = pa[i - 1] + a[i];
    	memset(dp, -1, sizeof dp);
    	cout << calc(1, n) - pa[n] << endl;
    }

    return 0;
}
