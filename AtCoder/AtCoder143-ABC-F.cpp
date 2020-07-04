/*
    Author : manu_sy
    Idea : Same as https://codeforces.com/blog/entry/70675?#comment-551801
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
 
const int N = 3e5+7;
 
/** Template Ends **/
int n, a[N], cnt[N];
vector<int> c, pre;

int calc(int m)
{
    int pos = lower_bound(all(c), m) - c.begin();
    int tot = (int)c.size() - pos;
    if (pos != 0)   tot += pre[pos - 1] / m;
    debug(m, tot, pos);
    return tot;
}

signed main() {
 
    IOS;
    cin >> n;
    LP(i,n)
    {
        int x;  cin >> x;
        cnt[x]++;
    }

    FOR(i,1,n) if (cnt[i] > 0) c.pb(cnt[i]);
    sort(all(c));
    pre.pb(c.front());
    FOR(i,1,(int)c.size() - 1) pre.pb(c[i] + pre[i - 1]);
    debug(c, pre);

    FOR(i,1,n)
    {
        int lo = 0, hi = n;
        while (hi - lo > 1)
        {
            int m = (hi + lo) / 2;
            if (calc(m) >= i)   lo = m;
            else hi = m;
        }
        // debug(i, lo, hi);
        if (calc(hi) >= i)  cout << hi << endl;
        else cout << lo << endl;
    }

    return 0;
}
