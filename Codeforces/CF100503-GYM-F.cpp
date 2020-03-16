/*
    Author : manu_sy
    Idea : Just keep dp[val] - max length of valid subsequence ending at val 
          - Iterate i from 0 till n - 1 and keep updating dp[a[i]] and also store previous[i]
          - dp[a[i]] = max(dp[x]) x != a[i] +/- 1
          - max can be easily found using segment tree 
          - also store in tree the index at which val is present
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
 
const int N = 1e6+7;
 
/** Template Ends **/
int n, a[N], pr[N];

PII t[4*N];
void update(int node, int l, int r, int i, int val, int id) {
    if (l > i || r < i) return;
    if (l == r) {
        t[node] = mp(val, id);
        return;
    }
    int mid = (l + r) / 2;
    if (i <= mid)   update(    2 * node,       l, mid, i, val, id);
    else            update(2 * node + 1, mid + 1,   r, i, val, id);
    t[node] = max(t[2*node], t[2*node+1]);
}
PII query(int node, int l, int r, int ql, int qr) {
    if (l > qr || r < ql)   return mp(INT_MIN,-1);
    if (ql <= l && r <= qr) return t[node];
    int mid = (l + r) / 2;
    return max(query(2 * node, l, mid, ql, qr), query(2 * node + 1, mid + 1, r, ql, qr));
}
 
signed main() {
 
    // IOS;
    freopen("input.txt", "r", stdin); 
    freopen("output.txt", "w", stdout);     

    cin >> n;
    FOR(i,1,n) 
    {
        int x;  cin >> x; a[i] = x;
        PII pll = query(1, 0, N - 3, 0, x - 2);
        PII pcc = query(1, 0, N - 3, x, x);
        PII prr = query(1, 0, N - 3, x + 2, N - 3);

        PII p  = max({pll, pcc, prr});
        pr[i] = p.S;
        update(1, 0, N - 3, x, p.F + 1, i);
    }

    PII p = query(1, 0, N - 3, 0, N - 3);
    int id = p.S;

    vector<int> ans;
    while (id != 0)
    {
        ans.pb(a[id]);
        id = pr[id];
    }
    reverse(all(ans));
    cout << n - ans.size() << endl;
    for (auto i : ans) cout << i << " ";

    return 0;
}
