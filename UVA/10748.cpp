/*
    Author : manu_sy
    Idea : just do brute force
*/
#include "bits/stdc++.h"
using namespace std;
 
/** Template Begins **/
 
typedef long long        ll;
typedef pair<int,int>    PII;
typedef pair<PII,int>    PIII;

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
 
const int N = 5e6+7;
int dx[] = {1, 1, -1, -1, 2, 2, -2, -2};
int dy[] = {2, -2, 2, -2, 1, -1, 1, -1};
/** Template Ends **/
int n;
 
signed main() {
 
    IOS;
    while (cin >> n)
    {
    	if (!n)	break;
    	vector<PII> ans;
    	LP(i,n)
    	{
    		int x, y, k;	cin >> x >> y >> k;

    		queue<PIII> q;
    		set<PII> s;

    		q.push({{x, y}, 0});
    		s.insert({x, y});
    		while (!q.empty())
    		{
    			auto p = q.front();	q.pop();
    			ans.pb(p.F);
    			s.insert(p.F);

    			if (p.S != k)
    			{
    				LP(j,8)
    				{
    					int nx = p.F.F + dx[j];
    					int ny = p.F.S + dy[j];
    					if (!s.count({nx, ny}))
    					{
    						q.push({{nx, ny}, p.S + 1});
    						s.insert({nx, ny});
    					}
    				}
    			}
    		}
    	}
    	sort(all(ans));
    	ans.resize(unique(all(ans)) - ans.begin());
    	cout << ans.size() << endl;
    }
 
    return 0;
}
