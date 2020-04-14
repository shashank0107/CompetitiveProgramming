/*
    Author : manu_sy
    Idea : To find the answer for k :
          - bring all of them (1,2,..k) together in min swaps and count inversions
          - Just write brute force and them optimize
          - Inspiration from https://youtu.be/RrzIwj5k6cY
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
int n, p[N], pos[N];

struct BIT {
	vector<int> bit;
	int n;
	BIT(int n): n(n + 1) {
		bit.assign(n + 1, 0);
	}
	void add(int idx, int val) {
		for (++idx; idx < n; idx += idx & -idx)
			bit[idx] += val;
	}
	int sum(int idx) {
		int ret = 0;
		for (++idx; idx > 0; idx -= idx & -idx)
			ret += bit[idx];
		return ret;
	}
	int sum(int l, int r) {
		return sum(r) - sum(l - 1);
	}
};
 
signed main() {
 
    IOS;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i], pos[p[i]] = i;

    ordered_set v;
	BIT bt(n + 5), bt2(n + 5);
	int inv = 0;
    for (int i = 1; i <= n; i++)
    {
    	bt.add(pos[i], pos[i]);
    	bt2.add(pos[i], 1);
    	inv += bt2.sum(pos[i] + 1, n);
    	v.insert(pos[i]);

    	int md = i / 2;
    	int vmd = *v.find_by_order(md);
    	int ans = 0;
    	ans += bt.sum(vmd + 1, n);
    	ans += (md - vmd) * (i - md - 1);
    	ans -= (i + md) * (i - md - 1) / 2;

    	ans -= bt.sum(1, vmd - 1);
    	ans += (vmd - md) * (md);
    	ans += (md - 1) * (md) / 2; 

    	cout << ans + inv << " ";
    }
 
    return 0;
}
