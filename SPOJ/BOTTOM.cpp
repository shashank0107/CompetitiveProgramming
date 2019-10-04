/*
    Author : manu_sy
    
    Idea : Observe that the bottom of the graph is connected component s.t 
          - there is no outgoing edge from the connected comp, i.e,
          - there does not exist any edge u->v where u belong to that connected component and v doesnot
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

const int N = 5e3+7;

/** Template Ends **/
int n, m, lowLink[N], dfn[N], ndfn, cmp[N], ncmp;
bool instack[N];
stack<int> st;
vector<int> g[N], ans;

void pre() {
    ndfn = 1, ncmp = 0;
    LP(i,n+2) dfn[i] = lowLink[i] = cmp[i] = -1, g[i].clear(), instack[i] = false;
    while (!st.empty()) st.pop();
    ans.clear();
}

void tarjan(int v) {
    dfn[v] = lowLink[v] = ndfn++, instack[v] = true, st.push(v);

    for (auto nb : g[v]) {

        if (dfn[nb] == -1) {
            tarjan(nb);
            lowLink[v] = min(lowLink[v], lowLink[nb]);
        } else {
            if (instack[nb])
                lowLink[v] = min(lowLink[v], dfn[nb]);
        }
    }

    if (dfn[v] == lowLink[v]) {
        vector<int> comp;
        ncmp++;

        while (st.top() != v) {
            comp.pb(st.top());  st.pop();
            cmp[comp.back()] = ncmp;
            instack[comp.back()] = false;
        }
        assert(st.top() == v);
        comp.pb(st.top());  st.pop();
        cmp[comp.back()] = ncmp;
        instack[comp.back()] = false;

        //debug(comp);

        bool valid = true;
        for (auto vv : comp) {
            for (auto nb : g[vv])
                if (cmp[nb] != ncmp) {
                    valid = false;
                    break;
                }
            if (!valid) break;
        }
        if (valid) {
            //debug(ncmp);
            for (auto v : comp) ans.pb(v);
        }
    }
}

signed main() {

    IOS;
    while (cin >> n) {

        if (n == 0) break;
        pre();

        cin >> m;
        LP(i,m) {
            int a, b;   cin >> a >> b;
            g[a].pb(b);
        }

        FOR(i,1,n) if (dfn[i] == -1) tarjan(i);

        sort(all(ans));
        for (int i = 0; i < ans.size(); i++) {
            if (i) cout << " ";
            cout << ans[i];
        } cout << endl;
    }

    return 0;
}
