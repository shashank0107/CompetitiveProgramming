/*
    Author : manu_sy
    
    Idea : At each moment keep the diameter length and its ending nodes - a, b 
          - after adding a vertex v.
            - update its up[v][i] array and L[]-depth
            Check if it can be new dia meter
              - if dist(a, v) > dia || dist(b, v) > dia
                then update dia and a,b
            Since we are adding only leaves the up[v][i] once calculated will not be modified later. 
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
 
const int N = 2e6+7;
 
/** Template Ends **/
int n, up[N][22], L[N], l, a, b, dia;
 
void add(int u, int p) 
{
    L[u] = L[p] + 1;
    up[u][0] = p;
    for (int i = 1; i <= l; i++)
    {
        if (up[u][i-1] != -1)
            up[u][i] = up[up[u][i-1]][i-1];
        else break;
    }
}
int lca(int u, int v)
{
    if (L[u] < L[v]) swap(u, v);
    for (int i = l; i >= 0; i--)
        if (((L[u]-L[v])>>i)&1)
            u = up[u][i];
    if (u == v) return u;
 
    for (int i = l; i >= 0; i--)
        if (up[v][i] != up[u][i])
            u = up[u][i], v = up[v][i];
    return up[u][0]; 
}
int dist(int u, int v) {
    return L[u] + L[v] - 2 * L[lca(u, v)];
}
void check(int v)
{   
    int d1 = dist(v, a), d2 = dist(v, b);
    if (d1 >= d2 && d1 > dia)
    {
        dia = d1;
        b = v;
    }
    else if (d2 > d1 && d2 > dia)
    {
        dia = d2;
        a = v;
    }
}
signed main() {
 
    IOS;
    int q;  cin >> q;
    memset(up, -1, sizeof up);
    
    L[1] = 0, L[2] = L[3] = L[4] = 1;
    up[2][0] = up[3][0] = up[4][0] = 1;
    
    a = 2, b = 3, dia = 2;
    l = ceil(log2(2 * q + 6));
 
    n = 4;
    while (q--)
    {
        int v;  cin >> v;
        add(n+1, v);
        add(n+2, v);
 
        check(n+1);
        check(n+2);
        n += 2;
 
        cout << dia << endl;
    }
 
    return 0;
}
