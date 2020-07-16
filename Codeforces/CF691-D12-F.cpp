/*
    Author : manu_sy
    Idea : Similar to editorial 
*/
#include "bits/stdc++.h"
using namespace std;
 
/** Template Begins **/
#define int ll 
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
 
#ifdef LOCALi
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif
 
/* Debug Ends */
 
const int N = 3e6+7;
 
/** Template Ends **/
int n;
int m;
int a[N];
ll cnt[N];

ll ans[N];

signed main() {
 
    IOS;
    cin >> n;
    LP(i,n) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    sort(a, a + n);

    for (int i = 1; i < N; i++) {
        if (cnt[i] == 0)    continue;
        for (int j = i; j < N; j += i) {
            int need = j / i;
            ll have = a + n - lower_bound(a, a + n, need);
            if (need <= i)  have--;

            ll contrib = have * cnt[i];
            // add contrib to [ans[j - i + 1].. ans[j]]
            auto add = [&] (int l, int r, ll val) {
                ans[l] += val;
                ans[r + 1] -= val;
            };
            add(j - i + 1, j, contrib); 
        }
    }
    FOR(i,1,N-1) ans[i] += ans[i - 1];

    cin >> m;
    LP(i,m) {
        int p;  cin >> p;
        cout << ans[p] << endl;
    }

    return 0;
}
