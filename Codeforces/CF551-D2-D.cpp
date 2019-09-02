/*
    Author : manu_sy
    Idea : Same as editorial 
*/
#include <bits/stdc++.h>
using namespace std;

/** Template Begins **/
#define int ll
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

const int N = 1e5+7;
const int SZ = 3;
int MOD;
/** Template Ends **/

/** Matrix Template Begin **/
int add(int a, int b)
{
    int res = a + b;
    if(res >= MOD)
        return res - MOD;
    return res;
}

int mult(int a, int b)
{
    long long res = a;
    res *= b;
    if(res >= MOD)
        return res % MOD;
    return res;
}

struct matrix
{
    int arr[SZ][SZ];

    void reset()
    {
        memset(arr, 0, sizeof(arr));
    }

    void makeiden()
    {
        reset();
        for(int i=0;i<SZ;i++)
        {
            arr[i][i] = 1;
        }
    }

    matrix operator + (const matrix &o) const 
    {
        matrix res;
        for(int i=0;i<SZ;i++)
        {
            for(int j=0;j<SZ;j++)
            {
                res.arr[i][j] = add(arr[i][j], o.arr[i][j]);
            }
        }
        return res;
    }

    matrix operator * (const matrix &o) const 
    {
        matrix res;
        for(int i=0;i<SZ;i++)
        {
            for(int j=0;j<SZ;j++)
            {
                res.arr[i][j] = 0;
                for(int k=0;k<SZ;k++)
                {
                    res.arr[i][j] = add(res.arr[i][j] , mult(arr[i][k] , o.arr[k][j]));
                }
            }
        }
        return res;
    }
};

matrix power(matrix a, int b)
{
    matrix res;
    res.makeiden();
    while(b)
    {
        if(b & 1)
        {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}
/** Matrix Template Ends **/
ll power(ll x, ll y, ll p){ ll res = 1;x = x % p;while (y > 0){ if (y & 1) res = (res*x) % p;y = y>>1;x = (x*x) % p;} return res; } 

int n, k, l;

int fib(int n) {
    if (n == 1) return 2;
    if (n == 2) return 3;

    matrix mat;
    mat.reset();
    mat.arr[0][0] = mat.arr[0][1] = mat.arr[1][0] = 1;
    mat = power(mat, n-2);
    int ret = (mat.arr[0][0]*fib(2) + mat.arr[0][1]*fib(1) + MOD)%MOD;
    return ret;
}

signed main() {

    IOS;
    cin >> n >> k >> l >> MOD;

    if ((l <= 62 && k >= (1LL<<l)) || MOD == 1) {
        cout << 0 << endl;
        return 0;
    } 
    int ans = 1;
    for (int bit = 0; bit < l; bit++) {
        if (((k>>bit)&1)==0) ans = (ans*fib(n))%MOD;
        else ans = (ans*(power(2,n,MOD) + MOD - fib(n)))%MOD;
    }
    cout << ans << endl;

    return 0;
}
