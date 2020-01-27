/*
    Author : manu_sy
    Idea : meet in middle
          Similar to editorial https://codeforces.com/blog/entry/17119
*/
#include "bits/stdc++.h"
using namespace std;

/** Template Begins **/
#define int              ll
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

const int N = 25+2;

/** Template Ends **/
int n, k, s, f[N], a[N], mf, ans;
map<int, int> m[N];

void comp_fac() 
{
    f[0] = 1;
    FOR(i,1,30) 
    {
        f[i] = f[i - 1] * i;
        if (f[i] > s){   mf = i; break; }
    }
}
void make(int pos, int sum, int used) 
{
    if (sum > s)    return;
    if (pos == n / 2)
    {
        m[used][sum]++;
        return;
    }
    make(pos + 1, sum + a[pos], used);
    make(pos + 1, sum, used);
    if (a[pos] < mf && used < k)    make(pos + 1, sum + f[a[pos]], used + 1);    
}
void make2(int pos, int sum, int used)
{
    if (sum > s)    return;
    if (pos == n)
    {
        ans += m[k - used][s - sum];
        return;
    }
    make2(pos + 1, sum + a[pos], used);
    make2(pos + 1, sum, used);
    if (a[pos] < mf && used < k)    make2(pos + 1, sum + f[a[pos]], used + 1);  
}

signed main() {

    IOS;
    cin >> n >> k >> s;
    comp_fac();
    LP(i,n) cin >> a[i];
    sort(a, a + n);

    make(0,0,0);
    FOR(i,0,k-1) for (auto s : m[i]) {
        m[i+1][s.F] += m[i][s.F];
    }
    make2(n / 2, 0, 0);
    cout << ans << endl;

    return 0;
}
