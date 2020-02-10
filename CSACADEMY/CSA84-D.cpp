/*
    Author : manu_sy
    Idea : Just do ternary on x.
    Note : Although this gets AC but i think the problem isn't ternary searchable
A test case which breaks the ternary :
11 3
0 5
1 5
2 1
3 0
4 1
5 6
6 7
8 8
10 0
10 0
10 0
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

#ifdef LOCAL
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif

/* Debug Ends */

const int N = 1e5+7;

/** Template Ends **/
int n, k;
PII p[N];

int f(int idx) {
    int x = p[idx].F;
    priority_queue<int> q;
    int ret = 0;
    LP(i,n) 
    {
        int dd = p[i].S + abs(p[i].F - x);
        q.push(dd);
        ret += dd;
    }
    while (q.size() > k) ret -= q.top(), q.pop();
    return ret;
}

signed main() {

    IOS;
    cin >> n >> k;
    LP(i,n) cin >> p[i].F >> p[i].S;
    sort(p, p + n);

    int lo = 0, hi = n - 1;
    FOR(i,0,n-1) debug(i,f(i));
    while (hi - lo > 3)
    {
        int m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
        debug(m1, m2, f(m1), f(m2));
        if (f(m1) > f(m2))  lo = m1;
        else hi = m2;  
    }
    int ans = 1e18;
    FOR(i,lo,hi) ans = min(ans, f(i));
    cout << ans << endl;

    return 0;
}
