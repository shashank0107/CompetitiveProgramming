/*
    Author : manu_sy
    Idea : First divide array into two equal parts : 
          - make all permutations of first part and store the ending point
          - make all permuations of second part from back and add to answer the number of endings before position reached currently
          Complexiy : ncr(14, 7) * 2 * 7! * log(n)
          
*/
#include "bits/stdc++.h"
using namespace std;
#pragma GCC optimize ("unroll-loops")

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
#define FOR(i,a,b)  for(register int i=a;i<=b;i++)
#define LP(i,n)     for(register int i=0;i< n;i++)

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

const int N = 2e5+5, M = 14+3;

/** Template Ends **/
int n, m, mid;
ll ans;
string s, p[M];
vector<int> v1, v2, v, occ[M];
int near[M][N], stt[M][N];

inline void make1(int idx, int pos) {
    if (idx == mid) {
        v.pb(pos - 1);
        return;
    }
    if (pos >= n)   return;
    for (register int i = idx; i < mid; i++) {
        swap(v1[idx], v1[i]);
        // find the first occ after pos - 1
        int id = v1[idx];
        int pp = near[id][pos];
        if (pp != -1)   make1(idx + 1, pp + p[id].size());
        swap(v1[idx], v1[i]);
    }
}
inline void make2(int idx, int pos) {
    if (idx == m - mid) {
         // find no. of positions in v <= pos
        int p = upper_bound(all(v), pos) - v.begin();
        ans += p;
        return;
    }
    if (pos < 0)    return;   
    for (register int i = idx; i < m - mid; i++) {
        swap(v2[idx], v2[i]);
        // find the last occurence <= pos
        int id = v2[idx];
        int st = pos - p[id].size() + 1;
        int pp = st >= 0 ? stt[id][st] : -1;
        if (pp != -1)   make2(idx + 1, pp - 1);
        swap(v2[idx], v2[i]);
    }
}

inline void calc() {
    v.clear();
    make1(0, 0);
    sort(all(v));
    // debug(v);
    make2(0, n - 1);
}

inline void divide(int idx) {
    if (idx == m) {
        // debug(v1, v2);
        calc();
        return;
    }
    if (v1.size() < mid) {
        v1.push_back(idx);
        divide(idx + 1);
        v1.pop_back();
    }
    if (v2.size() < m - mid) {
        v2.push_back(idx);
        divide(idx + 1);
        v2.pop_back();
    }
}

/* KMP Begins*/
inline vector<int> getLPS(string& pat) {
    int n = pat.size();
    vector<int> lps(n, 0);
    for (register int i = 1, k = 0; i < n; i++) {
        while (k > 0 && pat[i] != pat[k])
            k = lps[k - 1];
        if (pat[i] == pat[k])   k++;
        lps[i] = k;
    }
    return lps;
}
inline vector<int> kmp(string& word, string& pat) {
    int n = word.size(), m = pat.size();
    vector<int> lps = getLPS(pat), occ;
    for (register int i = 0, k = 0; i < n; i++) {
        while (k > 0 && word[i] != pat[k])
            k = lps[k - 1];
        if (word[i] == pat[k])  k++;
        if (k == m) {
            occ.pb(i - m + 1);
            k = lps[k - 1];
        }
    }
    return occ;
}
/* KMP Ends*/

signed main() {

    IOS;
    cin >> n >> m >> s;
    memset(near, -1, sizeof near);
    memset(stt, -1, sizeof stt);
    LP(i,m) 
    {
        cin >> p[i];
        occ[i] = kmp(s, p[i]);
        // debug(i, occ[i]);
        for (auto j : occ[i])   near[i][j] = j, stt[i][j] = j;
        for (int j = n - 1; j >= 0; j--) 
        {
            if (near[i][j] == -1)   near[i][j] = near[i][j + 1];
        }
        FOR(j,1,n-1) if (stt[i][j] == -1)   stt[i][j] = stt[i][j - 1];
    }

    mid = (m + 1) / 2;
    divide(0);

    cout << ans << endl;

    return 0;
}
