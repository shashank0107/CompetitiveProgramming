/*
    Author : manu_sy
    
    Idea : solve greedily 2 arrays at a time. Similar to the given link : 
      
      Note : the link has better complexity i think
      https://github.com/AliOsm/CompetitiveProgramming/blob/master/UVA/11997%20-%20K%20Smallest%20Sums.cpp
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
#define FOR(i,a,b)  for(int i=a;i<=b;i++)

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

const int N = 750+7;

/** Template Ends **/
int k, a[N], b[N], temp[N];

void apply() {
    set<pair<int, PII> > s;
    s.insert(mp(a[0]+b[0], mp(0,0)));

    for (int tt = 0; tt < k; tt++) {

        auto p = *s.begin();    s.erase(p);
        int i = p.S.F, j = p.S.S, val = p.F;
        temp[tt] = val;
        auto p1 = mp(val-a[i]+a[i+1], mp(i+1, j));
        auto p2 = mp(val-b[j]+b[j+1], mp(i, j+1));
        s.insert(p1);
        s.insert(p2);
    }
    swap(a, temp);
}

signed main() {

    IOS;
    while (cin >> k) {
        for (int i = 0; i < k; i++) cin >> a[i];
        sort(a, a+k);
        for (int tt = 0; tt < k-1; tt++) {
            for (int i = 0; i < k; i++) cin >> b[i];
            sort(b, b+k);
            apply();
        }
        for (int i = 0; i < k; i++) { 
            cout << a[i];
            if (i+1 < k) cout << " ";
        } cout << endl;
    }

    return 0;
}
