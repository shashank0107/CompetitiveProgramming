/*
    Author : manu_sy
    
    Idea : Same as https://www.quora.com/How-can-I-solve-a-KPMATRIX-problem-on-SPOJ
        Note - Getting TLE although complexity is same.
*/
#pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>
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
const int INF = 1e9+7;

/** Template Ends **/

int n, m, mat[N][N], pre[N][N], a, b;

inline int sum(int i1, int j1, int i2, int j2) {
    return pre[i2][j2] + pre[i1 - 1][j1 - 1] - pre[i1 - 1][j2] - pre[i2][j1 - 1];
}

int bit[100000];

struct BIT {
    int n;
    BIT (int n) : n(n + 1) {
        for (int i = 0; i < n + 1; i++) bit[i] = 0;
    }
    void add(int idx, int val) {
        for (++idx; idx < n; idx += idx & -idx)
            bit[idx] += val;
    }
    inline int sum(int idx) {
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }
    inline int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

signed main() {

    IOS;
    cin >> n >> m;
    for (register int i = 1; i <= n; ++i) 
    {
        for (register int j = 1; j <= m; ++j)
        { 
            cin >> mat[i][j];
            pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + mat[i][j];
        }
    }
    cin >> a >> b;
    long long ans = 0;
    for (register int up = 1; up <= n; ++up)
    {
        for (register int dn = up; dn <= n; ++dn)
        {
            map<int, int> mx;
            vector<int> v;

            for (register int i = 1, cur = 0; i <= m; i++)
            {
                cur += sum(up, i, dn, i);
                v.pb(cur), v.pb(cur - a), v.pb(cur - b);
            }
            v.pb(0);
            
            sort(all(v));
            v.resize(unique(all(v)) - v.begin());
            for (int i = 0; i < v.size(); i++)  mx[v[i]] = i + 1;

            BIT bt(v.size() + 2);
            bt.add(mx[0], 1);
            for (register int i = 1, cur = 0; i <= m; i++)
            {
                cur += sum(up, i, dn, i);
                ans += bt.sum(0, mx[cur - a]) - bt.sum(0, mx[cur - b] - 1);
                bt.add(mx[cur], 1);
            }
        }
    }    
    cout << ans << endl;

    return 0;
}
