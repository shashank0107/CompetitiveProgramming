/*
    Author : manu_sy
    
    Idea : We'll sort the queries and then process.
           - Think of array a[] as contributing 1 for all the first occorences and make segtree for this
           - So initially we can answer all queries of type 0,r
           Now as you move forward in the leftmost idx:
           if cur is a[i], then we now have make contribution of the next occurence of a[i] as 1. Do it
       
           - Answer queries sequentially like this
*/
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
template<class TH> void _dbg(const char *sdbg, TH h){ cerr<<sdbg<<'='<<h<<endl; }
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
  while(*sdbg!=',')cerr<<*sdbg++;
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
const int Q = 1e6+7;
const int A = 1e6+7;

/** Template Ends **/
int n, a[N], q, ans[Q];
deque<int> g[A];

int tree[4*N];
void update(int s, int e, int nd, int idx) {
    if (s == e) {   
        tree[nd] = 1;
        return;
    }
    int md = (s+e)/2;
    if (idx <= md)  update(s, md, 2*nd, idx);
    else update(md+1, e, 2*nd+1, idx);
    tree[nd] = tree[2*nd] + tree[2*nd+1];
}
int query(int s, int e, int nd, int l, int r) {
    if (r < s || e < l) return 0;
    if (l <= s && e <= r)   return tree[nd];
    int mid = (s+e)/2;
    int ret = query(s, mid, 2*nd, l, r) + query(mid+1, e, 2*nd+1, l, r);
    return ret;
}

signed main() {

    IOS;
    cin >> n;
    LP(i,n) { 
        cin >> a[i];
        if (g[a[i]].empty())    update(0,n-1,1,i);
        g[a[i]].push_back(i);
    }
    cin >> q;
    vector<pair<PII, int> > qry;
    LP(i,q) {
        int a, b;   cin >> a >> b;
        a--, b--;    
        qry.pb(mp(mp(a,b),i));
    }
    sort(all(qry));
    int st = 0;
    for (auto q : qry) {
        int l = q.F.F, r = q.F.S, idx = q.S;
        while (st < l) {
            g[a[st]].pop_front();
            if (!g[a[st]].empty())  update(0,n-1,1,g[a[st]].front());
            st++;
        }
        ans[idx] = query(0,n-1,1,l,r);
    }
    LP(i,q) cout << ans[i] << endl;
    return 0;
}
