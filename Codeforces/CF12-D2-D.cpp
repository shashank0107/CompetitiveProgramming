/*
    Author : manu_sy
    
    Idea : Same as https://codeforces.com/blog/entry/339?#comment-4637.
          - Just i have used segment tree to find maximum
*/
#include <bits/stdc++.h>
using namespace std;

/** Template Begins **/

typedef long long        ll;
typedef pair<int,int>    PII;
typedef pair<int, PII>   PIII;
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
int n, sz;
PIII l[N];
vector<int> I;
map<int, int> mi;

void compress_I() {
    sort(all(I));
    I.resize(unique(all(I)) - I.begin());
    for (int i = 0; i < I.size(); i++) mi[I[i]] = i;
    sz = I.size();
}

int tree[4*N];
 
int combine(int left, int right){
    return max(left, right);
}

void update(int start, int end, int node, int idx, int val){
    if (start == end){
        tree[node] = max(val, tree[node]);
        return;
    }
    int mid = (start+end)/2;
    if (idx <= mid) update(start, mid, 2*node, idx, val);
    else            update(mid+1, end, 2*node+1, idx, val);
    tree[node] = combine(tree[2*node], tree[2*node+1]);
} 

int query(int start, int end, int node, int l, int r){
    if (start > r || end < l)   return INT_MIN;
    if (l <= start && end <= r) return tree[node];
    int mid = (start+end)/2;
    int lf = query(start, mid, 2*node, l, r);
    int rh = query(mid+1, end, 2*node+1, l, r);
    return combine(lf, rh);
}

signed main() {

    IOS;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> l[i].F;
    for (int i = 1; i <= n; i++) cin >> l[i].S.F, I.pb(l[i].S.F);
    for (int i = 1; i <= n; i++) cin >> l[i].S.S;
    sort(l + 1, l + n + 1);
    
    compress_I();

    vector<PIII> que;
    PIII last = mp(-1, mp(-1, -1));
    int ans = 0;
    for (int i = n; i >= 1; i--)
    {
        if (l[i].F != last.F)
        {
            for (auto x : que)  
            {
                // debug(x, mi[x.S.F]);
                update(0, sz - 1, 1, mi[x.S.F], x.S.S);
            }
            que.clear(); 
        }
        que.pb(l[i]);
        last = l[i];

        // debug(i, l[i], query(0, sz - 1, 1, mi[l[i].S.F] + 1, sz - 1));
        if (query(0, sz - 1, 1, mi[l[i].S.F] + 1, sz - 1) > l[i].S.S)   ans ++;
    }
    cout << ans << endl;

    return 0;
}
