/*
    Author : manu_sy
    Idea : Same as editorial https://codeforces.com/blog/entry/48582
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
 
const int N = 3e5+7;
 
/** Template Ends **/
int n, m, a[N], arr[N];

struct Node {
    int lval, rval, mx;
};
Node tr[4 * N];

int sign(int x) {
    return (x > 0 ? 1 : (x < 0 ? -1 : 0));
}

void calc(int cur, int l, int r) {
    int m = (l + r) >> 1;
    tr[cur].mx = max(tr[2 * cur].mx, tr[2 * cur + 1].mx);
    tr[cur].lval = tr[2 * cur].lval;
    tr[cur].rval = tr[2 * cur + 1].rval;

    if (!(a[m] == 0) && !(a[m + 1] == 0) && sign(a[m]) >= sign(a[m + 1])) {
        tr[cur].mx = max(tr[cur].mx, tr[2 * cur].rval + tr[2 * cur + 1].lval);
        
        if (tr[2 * cur].mx == m - l + 1)
            tr[cur].lval += tr[2 * cur + 1].lval;

        if (tr[2 * cur + 1].mx == r - m)
            tr[cur].rval += tr[2 * cur].rval;
    }
}

void build(int cur, int l, int r) {
    if (l == r) {
        int x = !!a[l];
        tr[cur] = {x, x, x};
    } else {
        int m = (l + r) >> 1;
        build(2 * cur, l, m);
        build(2 * cur + 1, m + 1, r);
        calc(cur, l, r);
    }
}
void update(int cur, int l, int r, int idx, int val) {
    if (l == r) {
        a[l] += val;
        int x = !!val;
        tr[cur] = {x, x, x};
    } else {
        int m = (l + r) >> 1;
        if (idx <= m)   update(2 * cur, l, m, idx, val);
        else            update(2 * cur + 1, m + 1, r, idx, val);
        calc(cur, l, r);
    }
}
 
signed main() {
 
    IOS;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    for (int i = 1; i <= n - 1; i++) a[i] = arr[i + 1] - arr[i];

    if (n > 1)  build(1, 1, n - 1);
    
    cin >> m;
    while (m--) {
        int l, r, d;    cin >> l >> r >> d;
        if (n == 1) {
            cout << 1 << endl;
            continue;
        }
        if (l != 1) update(1, 1, n - 1, l - 1, d);
        if (r != n) update(1, 1, n - 1, r, -d);

        cout << tr[1].mx + 1 << endl;
    }
 
    return 0;
}
