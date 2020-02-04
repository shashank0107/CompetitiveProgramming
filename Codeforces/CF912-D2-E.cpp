/*
    Author : manu_sy
    Idea : All the candidate numbers will be of form a1^p1 * a2^p2 * a3^p3 * .... an^pn
           So just divide a[] into two parts and find all such candidate numbers and store in vectors v1 and v2.
           - Now the question reduces to finding the kth smallest element when all elements of v1 are multiplied with all 
             elements of v2. 
           - This can easily be solved using binary search in O(nlognlogn) where n is the size of v1/v2
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

#ifdef LOCALI
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif

/* Debug Ends */

const int N = 1e5+7;
const int INF = 1e18+7000;
/** Template Ends **/
int n, a[N], k;
vector<int> v1, v2;

bool dv(int x) {
    LP(i,n) {
        while (x % a[i] == 0) x /= a[i];
    }
    return x == 1;
}
void make(int idx, int prd, int end, vector<int>& v) {
    if (idx == end) {
        v.pb(prd);
        return;
    }

    for (int i = 0; i < 100; i++) {
        make(idx + 1, prd, end, v);
        if ((double)prd * (double)a[idx] < INF)   
            prd *= a[idx];
        else break;
    } 
} 

int f(int val) {

    int cnt = 0;
    for (auto x : v2)
    {
        int up = val / x;
        cnt += upper_bound(all(v1), up) - v1.begin();
    }
    return cnt;
}

signed main() {

    IOS;
    cin >> n;
    LP(i,n) cin >> a[i];
    cin >> k;
    int mid = n/ 2;

    make(0, 1, mid, v1);
    make(mid, 1, n, v2);
    sort(all(v1));     
    sort(all(v2));  

    int lo = 1, hi = INF, ans = -1;
    while (hi - lo > 1)
    {
        int mid = (hi + lo) / 2;
        if (f(mid) > k) hi = mid;
        else if (f(mid) < k) lo = mid;
        else 
        {
            if (dv(mid)) lo = mid;
            else hi = mid;
        }
    }
    if (f(lo) == k && dv(lo))    ans = lo;
    else if (f(hi) == k && dv(hi)) ans = hi;
    assert(ans != -1);
    
    cout << ans << endl;
    return 0;
}
