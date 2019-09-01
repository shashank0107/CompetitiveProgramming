/*
    Author : manu_sy
    
    Idea : Similar to editorial 
      https://codeforces.com/blog/entry/6545?locale=en&_ga=2.86474139.249832320.1567055721-1570299893.1551264393
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
 
const int N = 1e5+7;
 
/** Template Ends **/
int n;
pair<double, double> p[N];
 
bool comp(const pair<double, double>& a, const pair<double, double>& b) {
    return a.F*a.S*(1-b.S) > b.F*b.S*(1-a.S) || (a.F*a.S*(1-b.S) == b.F*b.S*(1-a.S) && (a.S > b.S) );
}
 
signed main() {
 
    IOS;
    cin >> n;
    LP(i,n) {
        cin >> p[i].F >> p[i].S;
        p[i].S/=100;
    }
    sort(p,p+n, comp);
 
    double ans = 0, liked = 0;
    LP(i,n) {
        ans += 1.0*p[i].S*p[i].F + 1.0*(1-p[i].S)*(liked + p[i].F);
        debug(i, liked, ans, p[i].F, p[i].S);
        liked += 1.0*p[i].S*p[i].F;
    }
    cout << fixed << setprecision(13) << ans << endl;
 
    return 0;
}
