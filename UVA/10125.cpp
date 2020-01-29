/*
    Author : manu_sy
    Idea : - First store all sums a + b in fqand for each i store v[i] + v[j] (0 <= j <= n - 1) in array m[i] and sort
           - Now for each c, d : sum = d - c
             Check if sum can be formed without using c and d : 
                  - fq.count(sum) > m[i].count(sum) + m[j].count(sum)  
                  Note that there will not be any overcounting in  m[i].count(sum) + m[j].count(sum) term
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

const int N = 1e3+7;

/** Template Ends **/
int n, v[N];
vector<int> m[N], fq;

void pre() {
    LP(i,n) m[i].clear();
    fq.clear();
}
int count(vector<int>& v, int x) {
    int u = upper_bound(all(v), x) - v.begin() - 1;
    if (u < 0 || u >= v.size() || v[u] != x) return 0;
    int l = lower_bound(all(v), x) - v.begin();
    return u - l + 1;
}
signed main() {

    IOS;
    while (cin >> n)
    {
        if (n == 0) break;
        pre();

        LP(i,n) cin >> v[i];
        LP(i,n) FOR(j,i+1,n-1) 
        {
            m[j].pb(v[i] + v[j]);
            m[i].pb(v[i] + v[j]);
            fq.pb(v[i] + v[j]);
        }
        LP(i,n) sort(all(m[i]));
        sort(all(fq));

        int ans = INT_MIN;
        LP(i,n) LP(j,n) if (i != j)
        {
            int c = v[i], d = v[j];
            int sum = d - c;
            int present = count(fq, sum);
            int cc = count(m[i], sum), cd = count(m[j], sum);

            if (present > cc + cd)
                ans = max(ans, d);
        }

        if (ans != INT_MIN) cout << ans << endl;
        else cout << "no solution" << endl;
    }

    return 0;
}
