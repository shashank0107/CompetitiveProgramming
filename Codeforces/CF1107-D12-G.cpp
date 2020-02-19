/*
    Author : manu_sy
    Idea : We'll iterate over i and find cost of all segments (i,j) j >= i. Keep e[i] = (d[i+1]-d[i])^2
           - For each i find the range where e[i] will make effect starting from ith. This range will be from i+1 to nge[i]
           - Now calculate answer for all j when start is 1
           - As you move forward keep updating the answers. nge[i] is used there (specifically for calculating the range in
             where to add / subtract e[i]) These ranges would total 2 * n
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

const int N = 3e5+7;
const ll INF = 1e18+700;

/** Template Ends **/
int n, nge[N];
ll a, d[N], c[N], e[N];

ll t[4*N], lazy[4*N];

void push(int v) {
    t[v*2] += lazy[v];
    lazy[v*2] += lazy[v];
    t[v*2+1] += lazy[v];
    lazy[v*2+1] += lazy[v];
    lazy[v] = 0;
}
void update(int v, int tl, int tr, int l, int r, ll addend) {
    if (l > r) 
        return;
    if (l == tl && tr == r) {
        t[v] += addend;
        lazy[v] += addend;
    } else {
        push(v);
        int tm = (tl + tr) / 2;
        update(v*2, tl, tm, l, min(r, tm), addend);
        update(v*2+1, tm+1, tr, max(l, tm+1), r, addend);
        t[v] = max(t[v*2], t[v*2+1]);
    }
}
ll query(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return -INF;
    if (l <= tl && tr <= r)
        return t[v];
    push(v);
    int tm = (tl + tr) / 2;
    return max(query(v*2, tl, tm, l, min(r, tm)), 
               query(v*2+1, tm+1, tr, max(l, tm+1), r));
}

void add(int l, int r, ll val) {
	update(1, 0, n, l, r, val);
}
ll query(int l, int r) {
	return query(1, 0, n, l, r);
}
void calc_nge() {
	stack<int> st;
	e[n] = 1e18+700;
	for (int i = 1; i <= n; i++) {
		while (!st.empty() && e[st.top()] <= e[i]) {
			nge[st.top()] = i;
			st.pop();
		}
		st.push(i);
	}
	assert(st.size() == 1);
}
signed main() {

    IOS;
    cin >> n >> a;
    FOR(i,1,n) cin >> d[i] >> c[i];

    FOR(i,1,n) add(i, n, a - c[i]);
    FOR(i,1,n-1) e[i] = (d[i + 1] - d[i]) * (d[i + 1] - d[i]);
    calc_nge();

    int last = n;	
    ll ans = 0;
    FOR(i,1,n)
    {
    	// debug(i);
    	int cur = i;
    	if (i != n)
    	{
	    	while (cur != last)
	    	{
	    		add(cur + 1, nge[cur], -e[cur]);
	    		// debug(cur+1,nge[cur], -e[cur]);
	    		cur = nge[cur];
	    	}
	    }
    	ll c_ans = query(i,n);
    	ans = max(ans, c_ans);
    	// debug(i, c_ans);

    	if (i < n)
    	{
    		add(i + 1, n, c[i] - a);
    		add(i + 1, nge[i], e[i]);
    		last = nge[i];
    	}
    }
    cout << ans << endl;

    return 0;
}
