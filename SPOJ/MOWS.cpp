/*
    Author : manu_sy
    
    Idea : For each scc find the lowest id hotel and the no. of places of interests in it. 
           Then get the answer
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

const int N = 5e6+7;

/** Template Ends **/
int h, p, s;

int ndfn, dfn[N], lowLink[N], instack[N];
PII ans;
stack<int> st;
vector<PII> ed;
vector<int> g[N];

void tarjan(int v) {
    dfn[v] = lowLink[v] = ndfn++, instack[v] = 1;
    st.push(v);

    for (auto nb : g[v]) {

        if (dfn[nb] == -1) {
            tarjan(nb);
            lowLink[v] = min(lowLink[nb], lowLink[v]);
        } else {
            if (instack[nb])
                lowLink[v] = min(lowLink[v], dfn[nb]);
        }
    }

    if (dfn[v] == lowLink[v]) {
        vector<int> comp;

        while (v != st.top()) {
            comp.pb(st.top());  st.pop();
            instack[comp.back()] = 0;
        }
        comp.pb(st.top());  st.pop();
        instack[comp.back()] = 0;

        int cnt = 0, myv = INT_MAX;
        for (auto vv : comp) {
            if (vv >= 1001 && vv <= 1000+p) cnt++;
            else if (vv >= 1 && vv <= h) myv = min(vv, myv);
        }
        if (myv != INT_MAX)
            ans = max(ans, mp(cnt, -myv));
    }
}

signed main() {

    IOS;
    int t;  cin >> t;
    while (t--) {

        cin >> h >> p >> s;

        ed.clear();
        LP(i,s) {
            int a, b;   cin >> a >> b;
            ed.pb(mp(a,b));
            g[a].clear(), dfn[a] = lowLink[a] = -1, instack[a] = false;
            g[b].clear(), dfn[b] = lowLink[b] = -1, instack[b] = false;
        }         
        FOR(i,1,h) g[i].clear(), dfn[i] = lowLink[i] = -1, instack[i] = false;
        
        for (auto e : ed) g[e.F].pb(e.S);

        ans = mp(0, 0);
        ndfn = 1;
        
        FOR(i,1,h) if (dfn[i] == -1) tarjan(i);

        if (ans == mp(0,0)) cout << 1 << " " << 0 << endl;
        else cout << -ans.S << " " << ans.F << endl;
    }

    return 0;
}
