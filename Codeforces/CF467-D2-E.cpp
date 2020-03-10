/*
    Author : manu_sy
    Idea : - Observe that we can greedy make sequences of the form a,b,a,b and join them to form answer
           We move i from index n to 1 -
            - we check what is the maximum starting point whose ending lies between i - nxt[i] (using segment tree)
            - We update starting point for a sequence ending at nxt[i]
            
            - Store that i's previous is present at pr[i] in segment tree
            
           - Finally make the answer greedily
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
 
const int N = 5e6+7;
 
/** Template Ends **/
int n, a[N], pr[N], st[N], nxt[N];
map<int, int> m;

int t[4*N];
int query(int v, int tl, int tr, int l, int r) {
    if (l > r) 
        return 0;
    if (l == tl && r == tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    return max(query(v*2, tl, tm, l, min(r, tm)), query(v*2+1, tm+1, tr, max(l, tm+1), r));
}
void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = max(t[v*2], t[v*2+1]);
    }
}
int query(int l, int r) {
    return query(1, 1, n, l, r);
}
void update(int idx, int val) {
    update(1, 1, n, idx, val);
}

signed main() {
 
    IOS;
    cin >> n;
    FOR(i,1,n)
    { 
        cin >> a[i];
        pr[i] = m[a[i]];
        nxt[m[a[i]]] = i;
        m[a[i]] = i;
        // handle equal
        int i1 = pr[i], i2 = pr[i1], i3 = pr[i2];
        if (i3) st[i] = i3;
    }
    memset(t, -1, sizeof t);

    priority_queue<PII> q;
    for (int i = n; i >= 1; i--)
    {
        if (nxt[i])
        {
            st[nxt[i]] = max(st[nxt[i]], query(1, nxt[i] - 1));
            update(nxt[i], -1);
        }
        if (pr[i])
        {
            update(i, pr[i]);
        }
    }
    // for (int i = 1; i <= n; i++) cout << st[i] << " ";   cout << endl;

    int en = 0;
    vector<int> ans;
    FOR(i,1,n)
    {
        if (st[i] > en)
        {
            ans.pb(a[st[i]]);   ans.pb(a[i]);
            ans.pb(a[st[i]]);   ans.pb(a[i]);
            en = i;
        }
    }
    cout << ans.size() << endl;
    for (auto i : ans) cout << i << " ";
 
    return 0;
}
