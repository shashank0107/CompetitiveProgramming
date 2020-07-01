/*
  Author : manu
  Idea : Sort a[i] in decreasing order
      - No. of steps = mxn = (a[1] == a[2] ? a[1] + 1 : a[1]) 
      - Initially we have mxn equal steps (sets)
      - Now for each i:
        - we will try to make atleast 1 set different by assigning it a different value (0/1)
        - update the sets
      - After i == n -> definately all sets are different since we differentiated atleast 1 set in each i
*/

#include "bits/stdc++.h"
using namespace std;
 
/** Template Begins **/
 
typedef long long        ll;
typedef pair<int,int>    PII;
typedef vector<int>      vi;

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
 
const int N = 1e3+7;
 
/** Template Ends **/
int n;
PII a[N];
int ans[N][N];

bool comp(const vi& v1, vi& v2) {
    return v1.size() > v2.size();
}
void fil(int i, int j, int k) {
    ans[i][j] = k;
}
signed main() {
 
    IOS;
    cin >> n;
    FOR(i,1,n) cin >> a[i].F, a[i].S = i;
    sort(a + 1, a + n + 1, greater<PII>());

    if (n == 1)
    {
    	cout << 1 << endl << 1 << endl;
    	return 0;
    }
    vector<vector<int>> v(1);
	
	int mxn;	    
    if (a[1].F == a[2].F)	mxn = a[1].F + 1;
    else mxn = a[1].F; 
    FOR(i,1,mxn) v[0].pb(i);
    debug(v);

    FOR(i,1,n)
    {
        debug(i);
        int c1 = a[i].F, c0 = mxn - a[i].F, pos = a[i].S;
        vector<vector<int>> tv;

        for (auto vv : v)
        {
            int sz = vv.size();
            vector<int> tmp1;
            vector<int> tmp0;
            assert(c1 + c0 >= sz);

            if (c1 == 0)
            {
                LP(k,sz)    fil(vv[k], pos, 0), tmp0.pb(vv[k]);
                c0 -= sz;
            }
            else if (c0 == 0)
            {
                LP(k,sz)    fil(vv[k], pos, 1), tmp1.pb(vv[k]);
                c1 -= sz;
            }
            else 
            {
                int tf1 = min(c1, sz - 1);
                int tf0 = sz - tf1;

                LP(k,tf1)       fil(vv[k], pos, 1), tmp1.pb(vv[k]);
                FOR(k,tf1,sz-1) fil(vv[k], pos, 0), tmp0.pb(vv[k]);

                c1 -= tf1;
                c0 -= tf0;
            }
            if (tmp1.size())    tv.pb(tmp1);
            if (tmp0.size())    tv.pb(tmp0);
        }
        sort(all(tv), comp);
        debug(v, tv);
        v = tv;
    }
    cout << mxn << endl;
    FOR(i,1,mxn) {
        FOR(j,1,n) cout << ans[i][j]; cout << endl;
    }
 
    return 0;
}
