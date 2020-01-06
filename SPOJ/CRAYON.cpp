/*
    Author : manu_sy
    Idea : Same as - https://github.com/tr0j4n034/SPOJ/blob/master/CRAYON.cpp
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

const int N = 3e5+7;

/** Template Ends **/
char c[N];
PII p[N];
int n;
vector<int> v;
vector<PII> qry;

struct BIT {
    vector<int> bit;
    int n;
    
    BIT(int n): n(n+1) {
        bit.assign(n+1, 0);
    }
    void add(int idx, int val) {
        for (++idx; idx < n; idx += idx & -idx)
            bit[idx] += val;
    }
    int sum(int idx) {
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }
    int sum(int l, int r) {
        return sum(r) - sum(l-1);
    }
};

int find_pos(int x) {
    return lower_bound(all(v), x) - v.begin();
}

signed main() {

    IOS;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> c[i];
        if (c[i] != 'C') cin >> p[i].F >> p[i].S, v.pb(p[i].F), v.pb(p[i].S), v.pb(p[i].F - 1);
        else cin >> p[i].F, p[i].F--;
        if (c[i] == 'D')    qry.pb(p[i]);
    }
    sort(all(v));
    v.resize(unique(all(v)) - v.begin());
    BIT btl(v.size() + 1), btr(v.size() + 1);

    for (int i = 0, cnt = 0; i < n; i++)
    {
        if (c[i] == 'D')
        {
            btl.add(find_pos(p[i].F), 1);
            btr.add(find_pos(p[i].S), 1);
            cnt++;
        }
        else if (c[i] == 'C')
        {
            btl.add(find_pos(qry[p[i].F].F), -1);
            btr.add(find_pos(qry[p[i].F].S), -1);
            cnt--;
        }
        else if (c[i] == 'Q')
        {
            int lft = btr.sum(0, find_pos(p[i].F - 1));
            int rht = btl.sum(0, find_pos(p[i].S));
            cout << rht - lft << endl;
        }
        else assert(false);
    }

    return 0;
}
