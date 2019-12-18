/*
    Author : manu_sy
    
    Idea : We just have to do range updates and point queries. 
          - Store all elements in sorted order in BIT
          - Now for every 1 X : Point Update ( Take care while handling duplicates, s.t the array always remains sorted after update)
          - 2 X : Binary Search for point after which all ele >= x
          - 3 X : B.S and then range update
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
int n, q, a[N], pos[N], ele[N];
PII p[N];

struct BIT {
	vector<int> bit;
	int n;
	BIT (int n) : n(n + 1) {
		bit.assign(n + 1, 0);
	}
	void add(int idx, int val) {
		for (++idx; idx < n; idx += idx & -idx)
			bit[idx] += val;
	}
	void range_add(int l, int r, int val) {
		add(l, val);
		add(r + 1, -val);
	}
	int query(int idx) {
		int ret = 0;
		for (++idx; idx > 0; idx -= idx & -idx)
			ret += bit[idx];
		return ret;
	}
} bt(N);

int lower_bound(int val) {
	int lo = 0, hi = n - 1;
	while (hi - lo > 1)
	{
		int mid = (hi + lo) / 2;
		if (bt.query(mid) >= val)	hi = mid;
		else lo = mid;
	}
	if (bt.query(lo) >= val)	return lo;
	else if (bt.query(hi) >= val)	return hi;
	else return n;
}

signed main() {

    IOS;
    cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> a[i], p[i] = mp(a[i], i);
    sort(p, p + n);
	for (int i = 0; i < n; i++) pos[p[i].S] = i, ele[i] = p[i].S, bt.range_add(i, i, p[i].F);

	while (q--)
	{
		int t, x;	cin >> t >> x;
		if (t == 1)
		{
			x--;
			int val = bt.query(pos[x]);
			int yy = lower_bound(val + 1) - 1;
			int y = ele[yy];
			assert(pos[y] == yy);

			swap(pos[x], pos[y]);
			swap(ele[yy], ele[pos[y]]);
			bt.range_add(pos[x], pos[x], 1);
		}
		else if (t == 2)
		{
			int p = lower_bound(x);
			cout << n - p << endl;
		}
		else 
		{
			int p = lower_bound(x);
			bt.range_add(p, n - 1, -1);
		}
	}

    return 0;
}
