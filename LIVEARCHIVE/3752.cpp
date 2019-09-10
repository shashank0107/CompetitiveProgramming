/*
    Author : manu_sy
    
    Idea : Just process each char greedily onto a stack.
      - Find the first stack on which it can be put ( st.top() >= c ) and put it
      - Ans is the total no. of stacks
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
string s;


signed main() {

    IOS;
    int tc = 1;
    while (cin >> s) {
        if (s == "end") break;

        vector<stack<char> > v;

        for (auto c : s) {
        
            bool found = false;
            for (auto& st : v) {
                if (st.top() >= c) {
                    found = true;
                    st.push(c);
                    break;
                }
            }

            if (!found) {
                v.pb(stack<char>());
                v.back().push(c);
            }
        }
        cout << "Case " << tc++ << ": " << v.size() << endl;
    }

    return 0;
}
