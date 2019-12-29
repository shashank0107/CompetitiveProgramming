/*
    Author : manu_sy
    
    Idea : For each idx i we need to find the maximum value of idx j s.t 
           prefix[i] - prefix[j] >= x, i.e, prefix[j] <= prefix[i] - x;
           
           - So we need to do queries of type max(0, i) and do point updations
           - Can use BIT because point updations here only increase the result of query
*/
#include <bits/stdc++.h>
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

const int N = 5e5+7;

/** Template Ends **/
ll n, x, a[N];
int bit[2*N];

struct BIT {
    int n;

    BIT(int n): n(n+1) {
        for (int i = 0; i <= n + 1; i++)
            bit[i] = -1;
    }
    void update(int idx, int val) {
        for (++idx; idx < n; idx += idx & -idx)
            bit[idx] = max(val, bit[idx]);
    }
    int getmax(int idx) {
        int ret = -1;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret = max(ret, bit[idx]);
        return ret;
    }
};

signed main() {

    IOS;
    int t;  cin >> t;
    while (t--)
    {
        map<ll, int> mx;
        vector<ll> v;

        cin >> n >> x;
        for (int i = 0; i <= n; i++) 
        {
            if (i) cin >> a[i], a[i] += a[i - 1];
            v.pb(a[i]), v.pb(a[i] - x);
        }
        sort(all(v));
        v.resize(unique(all(v)) - v.begin());
        for (int i = 0; i < v.size(); i++)  mx[v[i]] = i;
        
        int nn = v.size() + 2;
        BIT bt(nn);

        int ans = INT_MAX;
        for (int i = 0; i <= n; i++) 
        {
            int j = bt.getmax(mx[a[i] - x]);
            if (j >= 0)  ans = min(ans, i - j);
            bt.update(mx[a[i]], i);
        }

        if (ans != INT_MAX) cout << ans << endl;
        else cout << -1 << endl;
    }

    return 0;
}
