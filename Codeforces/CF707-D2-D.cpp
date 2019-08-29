/*
    Author : manu_sy
    
    Idea : If ith query is of type <= 3 then it depends on (i-1)th query else it depends on the kth query. Sp
           make a dependency tree using above observation and solve queries in dfs manner
          - For handling each query a segtree has been used. Could even just brute force. Since queries - 1e5 and 
            each query op at max 1e3
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

const int N = 1e5+7;
const int M = 1e3+7;

/** Template Ends **/

int n, m, q, ans[N], cnt;
vector<pair<int, PII> > ops;

vector<int> g[N];
bool vis[N];

/* Segtree Code */
int tree[M][4*M];
int lazy[M][4*M];

void lazify(int st, int en, int nd, int rw) {
	if (lazy[rw][nd]) {
		int len = en-st+1;
		tree[rw][nd] = len - tree[rw][nd];
		if (st != en) {
			lazy[rw][2*nd] ^= 1;
			lazy[rw][2*nd+1] ^= 1;
		}
		lazy[rw][nd] = 0;
	}
}
void update(int st, int en, int nd, int idx, int rw, int val) {
	lazify(st, en, nd, rw);
	if (st == en) {
		tree[rw][nd] = val;
		return;
	}
	int md = (st+en)/2;
	lazify(st, md, 2*nd, rw);
	lazify(md+1, en, 2*nd+1, rw);
	if (idx <= md)	update(st, md, 2*nd, idx, rw, val);
	else 			update(md+1, en, 2*nd+1, idx, rw, val);
	tree[rw][nd] = tree[rw][2*nd] + tree[rw][2*nd+1];
}
void flip(int rw) {
	lazy[rw][1] ^= 1;
	lazify(0, m-1, 1, rw);
}
int query(int rw) {
	lazify(0, m-1, 1, rw);
	return tree[rw][1];
}
/* Segtree Code Ends */

int perform(int v) {
	auto p = ops[v];
	if (p.F == 0)	return 0;
	int rw = p.S.F-1, col = p.S.S-1;

	int old = query(rw);
	if (p.F == 0)	return 0; 
	else if (p.F == 1) {
		update(0, m-1, 1, col, rw, 1);
	} 
	else if (p.F == 2) {
		update(0, m-1, 1, col, rw, 0);
	}
	else if (p.F == 3) {
		flip(rw);
	}
	int nw = query(rw);
	debug(v,p,old,nw);

	return nw-old;
}
int unperform(int v) {
	auto p = ops[v];
	if (p.F == 0)	return 0;
	int rw = p.S.F-1, col = p.S.S-1;

	int old = query(rw);
	if (p.F == 0)	return 0; 
	else if (p.F == 1) {
		update(0, m-1, 1, col, rw, 0);
	} 
	else if (p.F == 2) {
		update(0, m-1, 1, col, rw, 1);
	}
	else if (p.F == 3) {
		flip(rw);
	}
	int nw = query(rw);
	debug(2, v, p, old, nw);

	return nw-old;
}

void dfs(int v) {
	vis[v] = true;
	int c1 = cnt;
	cnt += perform(v);
	ans[v] = cnt;

	for (auto nb : g[v]) {
		// assert(!vis[nb]);
		dfs(nb);
	}
	if ((ops[v].F == 2 || ops[v].F == 1) && cnt == c1);
	else	cnt += unperform(v);
	debug(v, c1, cnt);
	assert(cnt == c1);
}

signed main() {

    IOS;
    cin >> n >> m >> q;
    
    ops.pb(mp(0,mp(0,0)));

    FOR(i,1,q) {
    	int t,l=0,r=0;	cin >> t >> l;
    	if (t <= 2)	cin >> r;
    	if (t <= 3) {
    		g[i-1].pb(i);
    		ops.pb(mp(t, mp(l,r)));
    	} else {
    		g[l].pb(i);
    		ops.pb(mp(0, mp(0, 0)));
    	}
    }
    dfs(0);

    FOR(i,1,q) cout << ans[i] << endl;
    
    return 0;
}
