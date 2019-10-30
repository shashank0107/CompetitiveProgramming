/*
    Author : manu_sy
    
    Idea : for each element find the number of elements before it and greater than it.
           if summation of above is odd then Marcelo wins else Carlos.
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

/** Template Ends **/
int n;

struct BIT {
    vector<int> bit;
    int n;

    BIT (int n): n(n+1) {
        bit.assign(n+1, 0);
    }
    void add (int idx, int delta) {
        for (++idx; idx < n; idx += idx & -idx)
            bit[idx] += delta;
    } 
    int sum (int idx) {
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }
    int sum (int l, int r) {
        return sum(r) - sum(l-1);
    }
};

signed main() {

    IOS;
    while (cin >> n)
    {
        if (n == 0) break;

        BIT bt(n+1);
        ll cnt = 0;
        for (int i = 0; i < n; i++)
        {
            int x;  cin >> x;
            cnt += bt.sum(x+1, n);
            bt.add(x, 1);
        }
        //debug(cnt);
        cout << (cnt&1 ? "Marcelo" : "Carlos") << endl;
    }  

    return 0;
}
