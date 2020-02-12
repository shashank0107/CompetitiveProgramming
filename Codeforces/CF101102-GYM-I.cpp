/*
    Author : manu_sy
    Idea : ternary search for optimal position for x and y independently
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

const int N = 2e5+7;

/** Template Ends **/
int n, r, c, x, y, xans, yans;
string s;

int fr(int xx) {
    int ret = 0;
    for (auto i : s) {
        if (i == '^') {
            if (xx == 1)    ret++;
            else xx--;
        } else if (i == 'v') {
            if (xx == r)    ret++;
            else xx++;
        }
        assert(xx >= 1 && xx <= r);
    }
    xans = min(xans, ret);
    return ret;
}
int fc(int yy) {
    int ret = 0;
    for (auto i : s) {
        if (i == '<') {
            if (yy == 1)    ret++;
            else yy--;
        } else if (i == '>') {
            if (yy == c)    ret++;
            else yy++;
        }
        assert(yy >= 1 && yy <= c);        
    }
    yans = min(yans, ret);
    return ret;
}


signed main() {

    IOS;
    int t;  cin >> t;
    while (t--)
    {
        cin >> r >> c >> s;

        xans = INT_MAX, yans = INT_MAX;
        int lo = 1, hi = r;
        while (hi - lo > 3)
        {
            int m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
            if (fr(m1) < fr(m2))  hi = m2;
            else lo = m1;
        }
        FOR(i,lo,hi) fr(i);

        lo = 1, hi = c;
        while (hi - lo > 3)
        {
            int m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
            if (fc(m1) < fc(m2))    hi = m2;
            else lo = m1;
        }
        FOR(i,lo,hi) fc(i);
        
        cout << xans + yans << endl;
    }

    return 0;
}
