/*
    Author : manu_sy
    Idea : - Observe that we can always reach the end
           - the path will in terms of loops, each time we encounter a loop we reach the initial position and the loop is removed
           - if we are at position i :
             U D U ... U U   D   U   D D
             0 1 2 ... i i+1 i+2 i+3
             
             - all the D's in front of i will make the path go back(loop) and then they would convert to U
               and all the U's in back of i will loop and get changed to D
             - So path would be like i -> next D -> previous U -> next_next D -> previous_previous D .. until we reach one end
           - The length of path can be calculated by keeping a prefix sum array and storing count of D's in front and U's in back of i
*/
#include "bits/stdc++.h"
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
 
const int N = 1e6+7;
 
/** Template Ends **/
int n, n1, n2, ans[N];
char s[N];
vector<int> pre1, pre2;

void add(vector<int>& v) {
    FOR(i,1,(int)v.size()-1) v[i] += v[i - 1];
} 

int sum1(int k)
{
    assert(k <= n1);
    if (k == 0) return 0;
    // left : n1 - k;
    // right : n1 - 1;
    return pre1[n1 - 1] - (n1 - k - 1 >= 0 ? pre1[n1 - k - 1] : 0);
}
int sum2(int k)
{
    assert(k <= n2);
    if (k == 0) return 0;
    int d = pre2.size();
    // left : pre2.size() - n2;
    // right : pre2.size() - n2 + k - 1;
    return pre2[d - n2 + k - 1] - (d - n2 - 1 >= 0 ? pre2[d - n2  - 1] : 0);
}
int sum1(int k, int i)
{
    return sum1(k) - k * (n - i + 1);
}
int sum2(int k, int i)
{
    return sum2(k) - k * i;
}
signed main() {
 
    IOS;
    cin >> n;
    FOR(i,1,n) cin >> s[i];
    FOR(i,1,n) 
    {
        if (s[i] == 'U') pre1.pb(n - i + 1); 
        else pre2.pb(i);
    }
    add(pre1); add(pre2);

    n2 = pre2.size(), n1 = 0;
    FOR(i,1,n)
    {
        if (s[i] == 'D')    n2--;

        if (s[i] == 'U')
        {
            if (n1 >= n2)
            {
                ans[i] = 2 * sum1(n2, i) + 2 * sum2(n2, i) + (n - i + 1);
            }
            else
            {
                ans[i] = 2 * sum1(n1, i) + 2 * sum2(n1 + 1, i) + i;  
            }
        }
        else
        {
            if (n1 <= n2)
            {
                ans[i] = 2 * sum1(n1, i) + 2 * sum2(n1, i) + i;
            }
            else
            {
                ans[i] = 2 * sum1(n2 + 1, i) + 2 * sum2(n2, i) + n - i + 1;
            }
        }

        if (s[i] == 'U')    n1++;
    }
    
    FOR(i,1,n) cout << ans[i] << " ";

    return 0;
}
