/*
    Author : manu_sy
    
    Idea : We can have circle in 2 forms
          1. The circle is a connected component (it would definately be a circle in this case) with size > 2
          2. Or we may have sequence like this :
              A->B->C<->D<-E-<F G->H<->I<-J
          Check both of these to get ans
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

const int N = 1e3+7;

/** Template Ends **/
int nxt[N], n, dp[N];
vector<int> g[N];

/* Tarjan */
int dfn[N], lowLink[N], ndfn, instack[N];
stack<int> st;
vector<vector<int> > comps;

void tarjan(int v) {
    dfn[v] = lowLink[v] = ndfn++, instack[v] = 1;
    st.push(v);

    int ch = nxt[v];
    if (dfn[ch] == -1) {
        tarjan(ch);
        lowLink[v] = min(lowLink[v], lowLink[ch]);
    } else if (instack[ch]) {
        lowLink[v] = min(lowLink[v], dfn[ch]);
    }

    if (dfn[v] == lowLink[v]) {
        comps.pb(vector<int>());

        int x = -1;
        while (x != v) {
            x = st.top(), st.pop(), instack[x] = 0;
            comps.back().pb(x);
        } 
        //debug(comps.back());
    }
}
/* Tarjan End */

void pre() {
    ndfn = 0;
    comps.clear();
    LP(i,n+3) g[i].clear(), dfn[i] = lowLink[i] = -1, instack[i] = 0, dp[i] = -1;
}
int get(int v, int par) {
    if (dp[v] != -1)    return dp[v];

    dp[v] = 0;
    for (auto nb : g[v]) {
        if (nb != par)  dp[v] = max(dp[v], get(nb, -1));
    }
    return ++dp[v];
}
signed main() {

    IOS;
    freopen("input.in", "r", stdin);
    freopen("output.txt", "w", stdout);
    int tt;  cin >> tt;
    FOR(tc,1,tt) {
        
        cin >> n;
        pre();
        FOR(i,1,n) { 
            cin >> nxt[i];
            g[nxt[i]].pb(i);
        }
        FOR(i,1,n) if (dfn[i] == -1) tarjan(i);

        int ans = 0;
        int ans2 = 0;
        for (auto comp : comps) {
            ans = max(ans, (int)comp.size());
            if (comp.size() == 2) {
                int cur = get(comp[0], comp[1]) + get(comp[1], comp[0]);
                ans2 += cur;
            }
        } 
        ans = max(ans, ans2);
        cout << "Case #" << tc << ": " << ans << endl; 
    }

    return 0;
}
