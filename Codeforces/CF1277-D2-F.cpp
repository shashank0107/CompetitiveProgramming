/*
  Author : manu
  Idea : Given a set of number - have to make the largest rectangle where different no.s in each col and row
        - Check for area of rectangle (ar) from 1 to n if we can make this rectangle:
          - so take ar elements greedily from our set such that the highest freq taken is min (can be done using priority_queue)
        - Now once the size of rectangle is found. Just make the rectangle in circular fashion. (Explained in editorial)
        Editorial : https://codeforces.com/blog/entry/72239
*/
#include "bits/stdc++.h"
using namespace std;
 
/** Template Begins **/
typedef pair<int, int> pii;
typedef pair<int, pair<int, int> > piii;

#define ll          long long 
#define IOS         ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl        '\n'
 
const int N = 4e5+7;
template<class L, class R> ostream &operator<<(ostream &os, pair<L,R> P) {
  return os << "(" << P.first << "," << P.second << ")";
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
/** Template Ends **/
int n, sq[N], hlb[N];
map<int, int> m;
vector<int> d[N];

void sv()
{
    for (ll i = 1, s = 1; i < N; i++)
    {
        if ((s + 1) * (s + 1) <= i) s++;
        sq[i] = s;
    }

    for (ll i = 1; i < N; i++) {
        for (ll j = i; j < N; j+=i)    d[j].push_back(i);
    }
}

pair<bool, int> check(int k, int mnd)
{
    int pos = lower_bound(d[k].begin(), d[k].end(), mnd) - d[k].begin();
    if (pos < d[k].size() && d[k][pos] <= sq[k])    return {1, d[k][pos]};
    else    return {0, 0};
}

signed main() 
{ 
    IOS;
    sv();
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;  cin >> x;   hlb[i] = x;
        m[x]++;
    }

    priority_queue<piii, vector<piii>, greater<piii> > q;
    for (auto i : m)    q.push({0, {-i.second, i.first}});

    int mxn = 0, afq = -1;
    for (int i = 1, mfq = 0; i <= n; i++)
    {
        auto p = q.top();   q.pop();
        debug(p);
        int fq = p.first, left = -p.second.first, x = p.second.second;

        fq++, left--;
        mfq = max(fq, mfq);
        
        // check if any prime divisor of i lies between mfq and sqrt(i)
        // if yes then mxn = i
        auto haha = check(i, mfq);
        if (haha.first)  mxn = i, afq = haha.second;

        if (left)   q.push({fq, {-left, x}});
    }    
    int col = mxn / afq;
    vector<vector<int> > ans(afq, vector<int>(col, 0));

    vector<int> z;
    vector<pii> zt;
    for (auto i : m)    zt.push_back({i.second, i.first});
    sort(zt.begin(), zt.end(), greater<pii>());

    for (auto i : zt)
    {
        int tfill = min(i.first, min(mxn - (int)z.size(), afq));
        for (int h = 0; h < tfill; h++) z.push_back(i.second);
        if (z.size() == mxn)    break;
        assert(z.size() < mxn);
    }

    int ci = 0, cj = 0;
    for (auto i : z)
    {
        if (ans[ci][cj] != 0)   ci = (ci + 1) % afq;
        assert(ans[ci][cj] == 0);
        if (ans[ci][cj] == 0)   ans[ci][cj] = i;

        ci = (ci + 1) % afq;
        cj = (cj + 1) % col;
    }

    cout << mxn << endl;
    cout << afq << " " << mxn / afq << endl;
    for (auto v : ans) 
    {
        for (auto x : v)    cout << x << " "; cout << endl;
    }

    return 0;
}
