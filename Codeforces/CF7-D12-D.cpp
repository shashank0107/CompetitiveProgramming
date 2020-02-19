/*
    Author : manu_sy
    Idea : Similar to comment - https://codeforces.com/blog/entry/239?#comment-555969
           - For finding if a substring is palindrome : manacher is used
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
string s;
int n, deg[N];
vector<int> v1, v2;

// Usage:
// Manacher("abacaba", 1) => {0, 1, 0, 3, 0, 1, 0}
// Manacher("aabbaa", 0) => {1, 0, 3, 0, 1}
vector<int> Manacher(string s, bool parity) {
    int n = s.size(), z = parity, l = 0, r = 0;
    vector<int> ret(n - !z, 0);
    
    for (int i = 0; i < n - !z; ++i) {
        if (i + !z < r) ret[i] = min(r - i, ret[l + r - i - !z]);
        int L = i - ret[i] + !z, R = i + ret[i];
        while (L - 1 >= 0 && R + 1 < n && s[L - 1] == s[R + 1]) 
            ++ret[i], --L, ++R;
        if (R > r) l = L, r = R;
    }
    
    return ret;
}
bool palin(int idx) {
	if (idx & 1)
	{
		return v2[idx / 2] == idx / 2 + 1;
	}
	else
	{
		return v1[idx / 2] == idx / 2;
	}
}

signed main() {

    IOS;
    cin >> s;
    n = s.size();
    v1 = Manacher(s, 1);
    v2 = Manacher(s, 0);

    ll ans = 0;
    FOR(i,1,n)
    {
    	if (palin(i - 1))	deg[i] = deg[i / 2] + 1;
    	ans += deg[i];
    }
    cout << ans << endl;

    return 0;
}
