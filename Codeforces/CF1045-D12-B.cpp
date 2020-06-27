/*
  Author : manu
  Idea : Same as editorial except that for checking the palindrome in O(1) in [l,r] - used manachar instead of hashing
*/
#include "bits/stdc++.h"
using namespace std;
 
/** Template Begins **/

#define ll          long long 
#define IOS         ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl        '\n'
 
const int N = 5e6+7;
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
/** Template Ends **/

// Manacher's Algorithm
// 
// Given a string s, computes the length of the longest
// palindromes centered in each position (for parity == 1)
// or between each pair of adjacent positions (for parity == 0)
//
// Usage:
// Manacher("abacaba", 1) => {0, 1, 0, 3, 0, 1, 0}
// Manacher("aabbaa", 0) => {1, 0, 3, 0, 1}
vector<int> Manacher(vector<int> s, bool parity) {
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
int n, m;
vector<int> v1, v0;

bool palin(int l, int r)
{
    if (l >= r || l >= n) return true;
    bool ret;
    if ((r - l + 1) & 1)
    {
        int mid = (r + l) / 2;
        ret = 2 * v1[mid] + 1 == (r - l + 1);
    }
    else
    {
        int mid = (r + l) / 2;
        ret = 2 * v0[mid] == (r - l + 1);
    }
    return ret;
}

signed main() 
{ 
    IOS;
    cin >> n >> m;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) 
    {
        cin >> a[i];
        if (i)  {
            b[i] = a[i] - a[i - 1];
        }
    }
    v1 = Manacher(b, 1), v0 = Manacher(b, 0);

    vector<int> ans;
    for (int i = 1; i <= n; i++)
    {
        if(
            palin(1, i - 1) && palin(i + 1, n - 1) &&
            ((i < n ? ((a[0] + a[i - 1]) % m == (a[i] + a[n - 1]) % m) : 1)) 
          )
        {
            ans.push_back((a[0] + a[i - 1]) % m);
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (auto i : ans) cout << i << " ";


    return 0;
}
