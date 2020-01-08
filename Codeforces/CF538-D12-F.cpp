/*
    Author : manu_sy
    Idea : For each node from 1 to n - 1, we'll look at its parent in heaps of size 1, 2, ... n and update accordingly.
           - This is O(n^2) but we can observe that for a particular node its parent is same in a lot of heaps,
             eg: par(7) = 1 in heaps of size 4, 5, 6
             - So we update these together and move to the next heap size for which the parent is not the same
             - This optimization makes it pass in Time limit
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

int n, a[N], aux[N];

signed main() {

    IOS;
    cin >> n;
    for (register int i = 0; i < n; i++) cin >> a[i];

    for (register int i = 1; i < n; i++)
    {
    	for (register int c = 1, j = 1; c <= n - 1;)
    	{
    		int par = (i - 1) / c, hi;
    		
    		if (par == 0)	hi = n - 1;
    		else			hi = (i - 1) / par;

    		int add = (a[par] > a[i]);
    		aux[c] += add;
    		aux[hi + 1] -= add;

    		c = hi + 1;
    	}
    }
    for (register int i = 1; i <= n - 1; i++)	aux[i] += aux[i - 1], cout << aux[i] << " ";	cout << endl; 

    return 0;
}
