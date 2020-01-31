/*
    Author : manu_sy
    Idea : Same as editorial - https://codeforces.com/blog/entry/8274
*/
#include "bits/stdc++.h"
using namespace std;

/** Template Begins **/
#define int              ll
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
const int hell = 1e9+7;
const int INF = 1e18+7;
/** Template Ends **/
int n, k, a[N], b[N], mid, ans12;
vector<PII> v;
map<PII, int> cnt1;
vector<pair<PII, PII> > v2;
map<pair<PII, PII>, int> cnt2;

/* Factorial */
const int MM = 24+5;
ll f[MM];
void comp_ft(){
    f[0]=1;
    for(ll i=1;i<MM;i++)
        f[i]=(f[i-1]*i)%hell;
}
/* Fact Ends */

int get(int pr) {
    int ret = 0;
    LP(mask,(1<<(n-mid)))
    {
        int sum = 0, lft = 0;
        LP(bit,(n-mid)) if ((mask >> bit) & 1) sum += a[bit + mid], lft++;

        PII upp = mp(pr - sum, INF), loo = mp(pr - sum, -1);
        int u = upper_bound(all(v), upp) - v.begin();
        int l = lower_bound(all(v), loo) - v.begin();
        FOR(i,l,u-1)
        {
            int tl = v[i].S + lft, tr = n - tl;
            ret = (ret + ((f[tl] * f[tr]) % hell) * cnt1[v[i]]) % hell;
        }
    }
    return ret;
}
void make1(int idx, int sl, int sm, int cl, int cm) {
    if (idx == mid) 
    {
        v2.pb(mp(mp(sl, sm), mp(cl, cm)));
        return;
    }
    make1(idx + 1, sl + a[idx], sm, cl + 1, cm);
    make1(idx + 1, sl, sm + a[idx], cl, cm + 1);
    make1(idx + 1, sl, sm, cl, cm);
}
void make2(int idx, int sl, int sm, int cl, int cm) {
    if (idx == mid - 1)
    {
        auto need = mp(b[0] - sl, b[1] - b[0] - sm);
        pair<PII, PII> upp = mp(need, mp(INF, INF)), loo = mp(need, mp(-1, -1));
        int u = upper_bound(all(v2), upp) - v2.begin();
        int l = upper_bound(all(v2), loo) - v2.begin();
        FOR(i,l,u-1)
        {
            int tl = cl + v2[i].S.F, tm = cm + v2[i].S.S;
            int add = (((((f[tl] * f[tm]) % hell) * f[n - tl - tm]) % hell)* cnt2[v2[i]]) % hell;
            ans12 = (ans12 + add) % hell;
        }
        return;
    }
    make2(idx - 1, sl + a[idx], sm, cl + 1, cm);
    make2(idx - 1, sl, sm + a[idx], cl, cm + 1);
    make2(idx - 1, sl, sm, cl, cm);
}
int get(int p1, int p2) {
    make1(0, 0, 0, 0, 0);
    sort(all(v2));
    for (auto i : v2) cnt2[i]++;
    v2.resize(unique(all(v2)) - v2.begin());
    make2(n - 1, 0, 0, 0, 0);   
    return ans12;
}
signed main() {

    IOS;
    comp_ft();
    cin >> n;
    LP(i,n) cin >> a[i];
    cin >> k;
    LP(i,k) cin >> b[i];
    sort(a, a + n);
    sort(b, b + k);

    if (k == 0) 
    {
        cout << f[n] << endl;
        return 0;
    } 
    mid = (n + 1)/ 2;
    LP(mask,(1<<mid))
    {
        int sum = 0, lft = 0;
        LP(bit,mid) if ((mask >> bit) & 1)  sum += a[bit], lft++;
        v.pb(mp(sum, lft));
    }
    sort(all(v));
    for (auto i : v)    cnt1[i]++;
    v.resize(unique(all(v)) - v.begin());

    int ans = 0;
    if (k == 1)
    {
        int ans = get(b[0]);
        cout << (f[n] - ans) % hell << endl;
    }
    else
    {
        int s1 = get(b[0]);
        int s2 = get(b[1]);
        int s12 = get(b[0], b[1]);
        cout << (f[n] - s1 - s2 + s12 + 2 * hell) % hell << endl;
    }

    return 0;
}
