/*
    Author : manu_sy
    Idea : Same as editorial 
           https://codeforces.com/blog/entry/64078
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

const int N = 2e5+7;

/** Template Ends **/
int n, q;
char a[N];
set<int> s[3];

struct BIT {
    vector<int> bit;
    int n;
    
    BIT(): n(N-1) {
        bit.assign(N-1, 0);
    }
    void add(int idx, int val) {
        for (++idx; idx < n; idx += idx & -idx)
            bit[idx] += val;
    }
    int sum(int idx) {
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }
    int sum(int l, int r) {
        return sum(r) - sum(l-1);
    }
} bt[3];

int shape(char c) {
    if (c == 'S')   return 0;
    else if (c == 'P')  return 1;
    else if (c == 'R')  return 2;
    else assert(false);
}
int frnd(int x) {
    return (x + 1) % 3;
}
int enmy(int x) {
    return (x + 2) % 3;
}
int lose(int x) {
	if (s[enmy(x)].empty())	return 0;
	if (s[frnd(x)].empty())	return s[x].size();

	int l = *s[enmy(x)].begin();
	int r = *s[frnd(x)].begin();
	int left = l < r ? bt[x].sum(l, r) : 0;

	int rr = *s[enmy(x)].rbegin();
	int ll = *s[frnd(x)].rbegin();
	int right = ll < rr ? bt[x].sum(ll, rr) : 0;
	return left + right; 
}
int losers() {
	int ans = 0;
	for (int i = 0; i < 3; i++)	ans += lose(i);
	return ans;
}
signed main() {

    IOS;
    cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> a[i], bt[shape(a[i])].add(i, 1), s[shape(a[i])].insert(i);

    cout << n - losers() << endl;
    while (q--)
    {
        int id; char c; cin >> id >> c;
        id--;

        bt[shape(a[id])].add(id, -1);
        s[shape(a[id])].erase(id);
        a[id] = c;
        bt[shape(a[id])].add(id, 1);
        s[shape(a[id])].insert(id);
        
        cout << n - losers() << endl;
    }
    
    return 0;
}
