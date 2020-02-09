/*
    Author : manu_sy
    Idea : greedy 
          - As new element comes replace the max element and calculate new mean
          - Now keep adding new elements from the last left position till the time new mean decreases and update the mean
*/
#include "bits/stdc++.h"
using namespace std;

/** Template Begins **/
#define int ll
#define double long double
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

const int N = 1e5+7;

/** Template Ends **/
int c, x, mx, pos;
double mean, pre;

vector<int> v;

double dcmp(double a, double b) {
    return abs(a - b) <= 1e-15 ? 0 : (a > b ? 1 : 0);
}

signed main() {

    IOS;
    cout << fixed << setprecision(13);
    
    int q;  cin >> q;   q--;
    cin >> c >> x;
    mean = x;
    mx = x;
    v.pb(x);

    while (q--)
    {
        cin >> c;
        if (c == 1)
        {
            cin >> x;
            v.pb(x);
            mx = x;

            mean = (pre + mx) / (pos + 1);
            while (pos < (int)v.size() - 1)
            {
                double n_mean = (pre + mx + v[pos]) / (pos + 2);
                if (dcmp(n_mean, mean) <= 0) {
                    pre += v[pos];
                    pos++;
                    mean = (pre + mx) / (pos + 1);
                } else break;
            } 
        }
        else
        {
            cout << mx - mean << endl;
        }
    }

    return 0;
}
