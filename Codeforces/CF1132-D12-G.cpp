/*
    Author : manu_sy
    Idea : Same as editorial 
          - Frame the problem in terms of tree queries and it is solved.
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
 
const int N = 1e6+7, INF = 1e9;
 
/** Template Ends **/
int n, k, timer, in[N], out[N], par[N], a[N];
vector<int> g[N];

void dfs(int v) {
	in[v] = ++timer;
	for (auto nb : g[v])
		dfs(nb);
	out[v] = timer;
}

int t[4*N], lazy[4*N]; 
void push(int v) {
    t[v*2] += lazy[v];
    lazy[v*2] += lazy[v];
    t[v*2+1] += lazy[v];
    lazy[v*2+1] += lazy[v];
    lazy[v] = 0;
}
void update(int v, int tl, int tr, int l, int r, int addend) {
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
int query(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return -INF;
    if (l <= tl && tr <= r)
        return t[v];
    push(v);
    int tm = (tl + tr) / 2;
    return max(query(v*2, tl, tm, l, min(r, tm)), query(v*2+1, tm+1, tr, max(l, tm+1), r));
}

void range_update(int l, int r, int val) {
	update(1, 0, n+1, l, r, val);
}
int query(int l, int r) {
	return query(1, 0, n+1, l, r);
}
void update(int idx, int val) {
	int x = query(idx, idx);
	range_update(idx, idx, val - x);
}

void insert(int v) {
	if (par[v] == -1)	update(in[v], 1);
	else {
		int prd = query(in[par[v]], in[par[v]]);
		update(in[v], prd + 1);
	}
}
void remove(int v) {
	range_update(in[v], out[v], -1);
}
void printd() {
	LP(i,n) {
		int k = query(in[i], in[i]);
		cout << k << " ";
	}
	cout << endl;
}


signed main() {
 
    IOS;
    cin >> n >> k;
    LP(i,n) cin >> a[i];

    memset(par, -1, sizeof par);
    stack<int> st;
    LP(i,n) 
    {
    	while (!st.empty() && a[st.top()] < a[i])
    	{
    		par[st.top()] = i;
    		g[i].pb(st.top());
    		st.pop();
    	}
    	st.push(i);
    }
    LP(i,n) if (par[i] == -1) dfs(i);

    LP(i,k-1) insert(n - i - 1);

    vector<int> ans;
    for (int i = n - k; i >= 0; i--)
    {
    	insert(i);
    	ans.pb(query(0, n+1));
    	remove(i + k - 1);
    }
    reverse(all(ans));
    for (auto i : ans) cout << i << " ";
 
    return 0;
}
