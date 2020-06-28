/*
  Author : manu
  Idea : Same as editorial. Dp on no. of partitions at node v subject to its inclusion / exclusion.
*/
#include "bits/stdc++.h"
using namespace std;
 
/** Template Begins **/
#define int long long
#define ll          long long 
#define IOS         ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl        '\n'
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

const int N = 2e5+7;
const int hell = 998244353;
/** Template Ends **/
int sum(int a, int b) {
    return (a + b) % hell;
}
int mul(int a, int b) {
    return ((a % hell) * (b % hell)) % hell;
}
int n, dp[N][3];
vector<int> g[N];

int out(int v)
{
    return sum(dp[v][0], dp[v][2]);
}
int in(int v)
{
    return sum(dp[v][0], dp[v][1]);
}

void dfs(int i)
{
    if (g[i].size() == 0)
    {
        dp[i][0] = 1;
        return;
    }

    dp[i][2] = 1;
    for (auto v : g[i]) 
    {
        dfs(v);
        dp[i][0] = sum(mul(in(i), in(v)), mul(dp[i][0], out(v)));
        dp[i][1] = sum(mul(dp[i][2], in(v)), mul(dp[i][1], out(v)));
        dp[i][2] = mul(dp[i][2], out(v));
    }
}

signed main() 
{ 
    IOS;
    cin >> n;
    for (int i = 2; i <= n; i++)
    {
        int x;  cin >> x;
        g[x].push_back(i);
    }
    dfs(1);
    cout << out(1) << endl;

    return 0;
}
