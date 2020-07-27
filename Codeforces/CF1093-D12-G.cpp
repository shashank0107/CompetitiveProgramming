/*
    Author : manu_sy
    Idea : just store all posibilites in different segtree.
           similar to https://codeforces.com/contest/1093/submission/47602077
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
 
#ifdef LOCALi
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif
 
/* Debug Ends */
 
const int N = 2e5+7;
const int INF = 1e9+7;

/** Template Ends **/
struct SegTree {
    int n;
    int t[4*N];
    // SegTree(int n): n(n) {
 //        LP(i,n) t[i] = {-INF, INF};
 //    }

    int combine(const int& x, const int& y) {
        return max(x, y);
    }
    void build(int a[], int v, int l, int r) {
        if (l == r) {
            t[v] = {a[l], a[l]};
            return;
        } 
        int m = (l + r) / 2;
        build(a, 2 * v, l, m);
        build(a, 2 * v + 1, m + 1, r);
        t[v] = combine(t[2 * v], t[2 * v + 1]);
    }
    int query(int v, int l, int r, int ql, int qr) {
        if (r < ql || l > qr) return -INF;
        if (ql <= l && r <= qr) {
            return t[v];
        }
        int m = (l + r) / 2;
        auto ret = combine(query(2 * v,         l, m, ql, qr), 
                           query(2 * v + 1, m + 1, r, ql, qr));
        return ret;
    }
    void update(int v, int l, int r, int idx, int val) {
        if (l == r) {
            t[v] = val;
            return;
        }
        int m = (l + r) / 2;
        if (idx <= m)   update(2 * v,         l, m, idx, val);
        else            update(2 * v + 1, m + 1, r, idx, val);
        t[v] = combine(t[2 * v], t[2 * v + 1]);
    }
}seg[33];

int n;
int k;
int mm;
vector<int> p[N];
int q;

void insert(int idx) {
    debug(idx);
    LP(msk,mm) {
        int sum = 0;
        LP(j,k) {
            if ((msk >> j) & 1) sum += p[idx][j];
            else sum -= p[idx][j];
        }
        debug(msk, sum);
        seg[msk].update(1, 0, n - 1, idx, sum);
    }
}

signed main() {
 
    IOS;
    cin >> n >> k;
    mm = (1 << k);
    LP(i,n) {
        p[i].resize(k);
        LP(j,k) {
            cin >> p[i][j];
        }
        insert(i);
    }
    cin >> q;
    LP(qr,q) {
        int ty; cin >> ty;
        if (ty == 1) {
            int idx;    cin >> idx;
            idx--;
            LP(j,k) cin >> p[idx][j];
            insert(idx);
        } else {
            int l, r;   cin >> l >> r;
            l--, r--;
            int ans = -INF;
            LP(msk,mm) {
                PII q1 = seg[msk].query(1, 0, n - 1, l, r);
                int cans = q1.F - q1.S;
                ans = max(ans, cans);
            }
            cout << ans << endl;
        }
    }
 
    return 0;
}
