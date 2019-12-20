/*
    Author : manu_sy
    Idea : Just use bit and coordinate compression and Binary Search to find kth.
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
int n, q;
pair<char, int> query[N];
vector<int> v;
map<int, int> mx;

struct BIT {
    vector<int> bit;
    int n;
    BIT (int n): n(n + 1) {
        bit.assign(n + 1, 0);
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
        return sum(r) - sum(l - 1);
    }
};

int find_kth(BIT& bt, int k) {
    int lo = 0, hi = n - 1;
    if (bt.sum(n) < k)  return -1;
    while (hi - lo > 1)
    {
        int mid = (hi + lo) / 2;
        if (bt.sum(mid) < k)    lo = mid;
        else hi = mid;
    }
    if (bt.sum(lo) == k)        return lo;
    else if (bt.sum(hi) == k)   return hi;
    else return -1;
}
signed main() {

    IOS;
    cin >> q;
    for (int i = 0; i < q; i++) 
    {
        cin >> query[i].F >> query[i].S;
        v.pb(query[i].S);
    }
    sort(all(v));
    v.resize(unique(all(v)) - v.begin());
    n = v.size();
    for (int i = 0; i < n; i++) mx[v[i]] = i;

    BIT bt(n + 5);
    for (auto q : query)
    {
        if (q.F == 'I')
        {
            if (bt.sum(mx[q.S], mx[q.S]) == 0)
                bt.add(mx[q.S], 1);
        }
        else if (q.F == 'D')
        {
            if (bt.sum(mx[q.S], mx[q.S]) == 1)
                bt.add(mx[q.S], -1);
        }
        else if (q.F == 'K')
        {
            int p = find_kth(bt, q.S);
            if (p == -1)    cout << "invalid" << endl;
            else            cout << v[p] << endl;
        }
        else if (q.F == 'C')
        {
            cout << bt.sum(mx[q.S] - 1) << endl;
        }
    }

    return 0;
}
