/*
    Author : manu_sy
    Idea : Observe that there are only 33 special numbers below 1e10
           Just divide these in 2 array and mark all the possible sums of first(smaller elements) array. O(2^17)
           Also calculate all the possible sums of the 2nd array. O(2^17)
           For each query just iterate through all the possible sums of 2nd array and check if the difference is marked. O(2e17)
           Complexity : O(2^17) * testcases
*/
#include "bits/stdc++.h"
using namespace std;

/** Template Begins **/
#define int 			 ll
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

const int N = 1e10+7;
const int M = 3e7+7;

/** Template Ends **/
vector<int> v = {0, 2, 7}, a[2], temp;
bool present[M];

signed main() {

    IOS;
    for (int i = 3; i <= N; i++) 
    {
    	int cur;
    	if (i&1)	cur = v[i - 1] + 3 * v[i - 2];
    	else 		cur = v[i - 1] + 7;
    	if (cur <= N)	v.pb(cur);
    	else break;
    }
    a[0].insert(a[0].begin(), v.begin(), v.begin() + v.size() / 2);
    a[1].insert(a[1].begin(), v.begin() + v.size() / 2, v.end());

    int n1 = a[0].size(), n2 = a[1].size();
    for (int mask = 0; mask < (1 << n1); mask++)
    {
    	int sum = 0;
    	for (int bit = 0; bit < n1; bit++)	if ((mask >> bit)&1) sum += a[0][bit];
    	assert(sum < M);
    	present[sum] = true;
    }
    for (int mask = 0; mask < (1 << n2); mask++)
    {
    	int sum = 0;
    	FOR(bit,0,n2-1) if ((mask >> bit)&1) sum += a[1][bit];
    	temp.pb(sum);
    }
    sort(all(temp));
    int t;	cin >> t;
    while (t--)
    {
    	int n;	cin >> n;
    	bool valid = false;
    	for (auto i : temp)	
    	{
    		if (i > n)	break;
    		if (n - i < M && n - i >= 0 && present[n - i])
    		{
    			valid = true;
    			break;
    		}
    	}
    	cout << (valid ? "YES" : "NO") << endl;
    }

    return 0;
}
