/*
    Author : manu_sy
    
    Idea : Very similar to editorial : https://codeforces.com/blog/entry/15743
          - Just represent permutation in factorial no. system
          - Add and then find ans
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

const int N = 2e5+7;

/** Template Ends **/
int n, p[N], q[N], p1[N], q1[N], a[N], a1[N];

struct BIT {
    vector<int> bit;
    int n;
    
    BIT(int n): n(n+1) {
        bit.assign(n+1, 0);
    }
    void add(int idx, int val) {
        for (++idx; idx < n; idx += idx & -idx)
            bit[idx] += val;
    }
    int sum(int idx) {
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }
    int sum(int l, int r) {
        return sum(r) - sum(l-1);
    }
};

void calc(int a[], int a1[]) {
    BIT bt(n);
    for (int i = n - 1; i >= 0; i--)
    {
        a1[i] = bt.sum(0, a[i] - 1);
        bt.add(a[i], 1);
    }
}

int find_kth(int k, BIT& bt) {
    k++;
    int lo = 0, hi = n - 1;
    while (hi - lo > 1)
    {
        int mid = (hi + lo) / 2;
        if (bt.sum(0, mid) < k)    lo = mid;
        else hi = mid;
    }
    if (bt.sum(0, lo) == k)         return lo;
    else if (bt.sum(0, hi) == k)    return hi;
    else assert(false);
}

signed main() {

    IOS;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> p[i];
    for (int i = 0; i < n; i++) cin >> q[i];

    calc(p, p1);    
    calc(q, q1);
    
    for (int i = n - 1, carry = 0; i >= 0; i--)
    {
        int cur = p1[i] + q1[i] + carry;
        int mxi = n - i;
        a1[i] = cur % mxi;
        carry = cur / mxi;
    }

    BIT bt(n);
    for (int i = 0; i < n; i++) bt.add(i, 1);

    for (int i = 0; i < n; i++)
    {
        a[i] = find_kth(a1[i], bt);
        bt.add(a[i], -1);
    }
    for (int i = 0; i < n; i++) cout << a[i] << " ";    cout << endl;

    return 0;
}
