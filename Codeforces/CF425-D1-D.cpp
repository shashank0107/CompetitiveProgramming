/*
    Author : manu_sy
    Idea : Same as editorial 
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
int n;
int rn;
ll ans;
vector< vector<int> > p(2*N);
vector< vector<int> > p2(2*N);

bool present(int x, int y, vector< vector<int> >& p) {
    if (x < 0 || x >= p.size()) return 0;
    return binary_search(all(p[x]), y);
} 

void calc(vector< vector<int> >& p) {
    LP(x,N) sort(all(p[x]));
    LP(x,N) {
        if (p[x].size() > rn)   continue;
        LP(i,p[x].size()) {
            int y2 = p[x][i];
            LP(j,i) {
                int y1 = p[x][j];
                int k = y2 - y1;
                if (present(x - k, y1, p) && present(x - k, y2, p))
                    ans++;
                if (present(x + k, y1, p) && present(x + k, y2, p))
                    ans++;
            }
        }
        p[x].clear();
    }
}

signed main() {
 
    IOS;
    cin >> n;
    rn = sqrt(n);
    LP(i,n) {
        int x, y;   cin >> x >> y;
        p[x].pb(y);
    }
    calc(p);
    LP(x,N) {
        for (auto y : p[x]) {
            p2[y].pb(x);
        }
    }
    calc(p2);
    cout << ans << endl;

    return 0;
}
