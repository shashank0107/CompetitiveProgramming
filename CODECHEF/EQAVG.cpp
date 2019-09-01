/*
    Author : manu_sy
    
    Idea : Since all subarray of length K have equal mean - they have equal sum. Hence all elements at distance k are equal.
        - So we just need to find a[0..K] and the rest of the array is decided.
        
        - a[0..k] would be like this - d11 d12 d13 ... d21 d22 d23
          where d1i are the no.s that would have frequency n/k + 1 and d2i would have frequency n/k.
          This happens bcz n might not be a multiple of k
          
        - Now get all the no.s and there frequencies. Now process these no.s to fill a[0..k] incrementally as follows : 
          - if the freq of no. is divisible by (n/k) then process it only after all the freq which aren't divisible by (n/k)
            have been processed.
          
          Above can be implemented easily using a priority queue.
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
#ifdef LOCA
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif
/* Debug Ends */

const int N = 1e6+7;

/** Template Ends **/
ll n, a[N], k, v[N], pre[N];

signed main() {

    IOS;
    int t;  cin >> t;
    while (t--) {

        cin >> n >> k;
        map<int, int> m;
        LP(i,n) {
            int x;  cin >> x;
            m[x]++;
        }
        int d = n/k;
        int cnt = n%k;              // cnt of digits whose freq needs to be d+1
        priority_queue<PII> q1, q2;

        for (auto i : m) {
            if (i.S%d == 0)  q2.push(mp(i.S, i.F));
            else q1.push(mp(i.S, i.F));
        }

        bool valid = true;
        for (int i = 0; i < k; i++) {
            int need = (i < cnt ? d+1 : d);

            PII p;
            if (!q1.empty()) {
                p = q1.top();  q1.pop();
            } else if (!q2.empty()) {
                p = q2.top();   q2.pop();
            } else {
                valid = false;  break;
            }
        
            if (p.F < need){ valid = false;  break;  }
            else {
                a[i] = p.S;
                p.F -= need;
                if (p.F > 0) {
                    if (p.F%d == 0) q2.push(p);
                    else q1.push(p);
                }
            }
        }
        
        if (valid) {
            cout << "YES" << endl;
            LP(i,n) {
                cout << a[i%k];
                if (i+1 < n)    cout << " ";
            } cout << endl;
        } else cout << "NO" << endl;
    }

    return 0;
}
