/*
    Author : manu_sy
    Idea : meet in middle
          - Move from top selecting every possible combination and store the string formed, value of L, L-M, L-W, at pos n / 2
          - Traverse from bottom top mid - 1 in above fashion and at last check if the corresponding -(L-M), -(L-W) is available
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

const int N = 25+7;
const int INF = INT_MAX;

/** Template Ends **/
string ret;
int n, l[N], m[N], w[N], ansl, mid;
vector<pair<PII, pair<int, string> > > v;

void move1(int idx, int cl, int cm, int cw, string s) {
    if (idx == mid) 
    {
        v.pb(mp(mp(cl - cm, cl - cw), mp(cl, s)));
        return;
    }
    move1(idx + 1, cl + l[idx], cm + m[idx], cw, s + "LM");
    move1(idx + 1, cl + l[idx], cm, cw + w[idx], s + "LW");
    move1(idx + 1, cl, cm + m[idx], cw + w[idx], s + "MW");
}
void move2(int idx, int cl, int cm, int cw, string s) {
    if (idx == mid - 1)
    {
        int x = cl - cm, y = cl - cw;
        pair<PII, pair<int, string> > ele = mp(mp(-x, -y), mp(INF, ""));
        int pos = lower_bound(all(v), ele) - v.begin() - 1;
        if (pos >= 0 && pos < v.size() && v[pos].F == mp(-x, -y) && v[pos].S.F + cl > ansl)
        {
            ansl = v[pos].S.F + cl;
            reverse(all(s));
            ret = v[pos].S.S + s;
        }
        return;
    }
    move2(idx - 1, cl + l[idx], cm + m[idx], cw, s + "ML");
    move2(idx - 1, cl + l[idx], cm, cw + w[idx], s + "WL");
    move2(idx - 1, cl, cm + m[idx], cw + w[idx], s + "WM");
}
signed main() {

    IOS;
    cin >> n;
    LP(i,n) cin >> l[i] >> m[i] >> w[i];
    ansl = INT_MIN;
    mid = (n + 1) / 2;
    move1(0, 0, 0, 0, "");
    sort(all(v));
    move2(n-1,0,0, 0, "");
    
    if (ansl == INT_MIN)    cout << "Impossible" << endl;
    else 
    {
        for (int i = 0; i < ret.size(); i+=2)    cout << ret[i] << ret[i + 1] << endl;
    }    

    return 0;
}
