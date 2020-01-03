/*
    Author : manu_sy
    Idea : We will create a bit for every char, for every len, for every start_idx%len.
           For each char we have BITS like this :
           LEN  START_IDX       INDICES
            1     0           0, 1, 2, 3, ...
            2     0           0, 2, 4, 6, ..
                  1           1, 3, 5, 7, ..
            3     0           0, 3, 6, ...
                  1           1, 4, 7, ...
                  2           2, 5, 8, ...
            4
            .
            .
            .
            10    0
                  1
                  2
                  3
                  .
                  .
           
           So no. of BITs - 4 * 10 * 10
           - Now we can answer queries easily by queries on the specific BIT
             Eg : We need to compare with string e of size 3 and l = 4, r = 9
                  Then we'll look at BIT[3] and then make appropriate queries
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

const int N = 1e5+7;

/** Template Ends **/
int n, q;
string s;
int bit[4][11][10][N];

int mp(char c) {
    if (c == 'A')   return 0;
    else if (c == 'T')  return 1;
    else if (c == 'G')  return 2;
    else return 3;
}

struct BIT {
    int n;
    
    BIT(int n): n(n+1) {}
    void add(int cc, int ln, int ii, int idx, int val) {
        for (++idx; idx < n; idx += idx & -idx)
            bit[cc][ln][ii][idx] += val;
    }
    int sum(int cc, int ln, int ii, int idx) {
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret += bit[cc][ln][ii][idx];
        return ret;
    }
    int sum(int cc, int ln, int ii, int l, int r) {
        return sum(cc, ln, ii, r) - sum(cc, ln, ii, l - 1);
    }
};

signed main() {

    IOS;
    cin >> s >> q;
    n = s.size();
    BIT bt(n + 2);

    for (int i = 0; i < n; i++)
    {
        for (int len = 1; len <= 10; len++)
        {
            int p = i % len;
            bt.add(mp(s[i]), len, p, i, 1);
        }
    }

    while (q--)
    {
        int t;  cin >> t;
        if (t == 1)
        {
            int x;  char c; cin >> x >> c;
            x--;
            for (int len = 1; len <= 10; len++)
            {
                int p = x % len;
                bt.add(mp(s[x]), len, p, x, -1);
            }
            s[x] = c;
            for (int len = 1; len <= 10; len++)
            {
                int p = x % len;
                bt.add(mp(s[x]), len, p, x, 1);
            }
        }
        else 
        {
            int l, r;   string e;   cin >> l >> r >> e;
            int len = e.size(), ans = 0;
            l--, r--;
            
            for (int i = 0; i < e.size(); i++)
            {
                ans += bt.sum(mp(e[i]), len, (i + l)%len, l, r);
            }
            cout << ans << endl;
        }
    }

    return 0;
}
