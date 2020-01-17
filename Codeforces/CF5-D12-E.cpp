/*
    Author : manu_sy
    Idea : Similar to editorial. 
          - Firstly transform array like mentioned in editoria
          - Now for i find its nearest left largest and right larger element. Add them to ans and also 
            add the frequency of that element b/w left largest and till current index to ans.
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

const int N = 2e6+7;

/** Template Ends **/
int n, a[N], rge[N], lge[N];
map<int, vector<int> > occ;

void calc_rge() {
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] < a[i]) {
            rge[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    while (!st.empty()) rge[st.top()] = -1, st.pop();
}
void calc_lge() {
    stack<int> st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.top()] < a[i]) {
            lge[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    while (!st.empty()) lge[st.top()] = -1, st.pop();
}
int count(int x, int l, int r) {
    if (l > r)  return 0;
    vector<int>& v = occ[x];
    int ll = lower_bound(all(v), l) - v.begin();
    int rr = lower_bound(all(v), r) - v.begin();
    return rr - ll;
}

signed main() {

    IOS;
    cin >> n;
    int mxi = 0;
    for (int i = 0; i < n; i++) 
    {
        cin >> a[i];
        a[i + n] = a[i];
        if (a[i] > a[mxi])  mxi = i;
    }
    for (int i = 0; i < n; i++) a[i] = a[(i + mxi)];
    a[n] = a[0];
    n++;
    for (int i = 0; i < n; i++) occ[a[i]].pb(i);

    calc_rge();
    calc_lge();

    long long ans = 0;
    for (int i = 0; i < n - 1; i++)
    {   
        int l = lge[i];
        if (lge[i] != -1)   ans++;
        ans += count(a[i], lge[i] + 1, i);
        if (rge[i] != -1 && !(lge[i] == 0 && rge[i] == n - 1))   ans++;
        // debug(i, a[i], lge[i], rge[i], ans, count(a[i], lge[i] + 1, i - 1));
    }
    cout << ans << endl;

    return 0;
}
