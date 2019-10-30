/*
    Author : manu_sy
    
    Idea : 2d BIT implementation inspired from article -
          https://cp-algorithms.com/data_structures/fenwick.html
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

const int N = 1024+7;

/** Template Ends **/

struct BIT2d {
    vector<vector<int> > bit, mat;
    int n, m;

    BIT2d (int n, int m) {
        this->n = n + 1, this->m = m+1;
        bit.assign(this->n, vector<int>(this->m, 0));
        mat = bit;
    }
    void add (int x, int y, int val) {

        for (int i = x+1; i < n; i += (i & -i))
            for (int j = y+1; j < n; j += (j & -j))
                bit[i][j] += val - mat[x][y];

        mat[x][y] = val; 
    }
    int sum (int x, int y) {
        int ret = 0;
        
        for (int i = x+1; i > 0; i -= (i & -i))
            for (int j = y+1; j > 0; j -= (j & -j))
                ret += bit[i][j];

        return ret;
    }
    int sum (int x1, int y1, int x2, int y2) {
        return sum(x2, y2) - sum(x1-1, y2) - sum(x2, y1-1) + sum(x1-1, y1-1);
    }
};

signed main() {

    IOS;
    int t;  cin >> t;
    while (t--)
    {
        int n;  cin >> n;
        string s;

        BIT2d bt(n, n);

        while (cin >> s)
        {
            if (s == "END") break;
            else if (s == "SET")
            {
                int x, y, num;    cin >> x >> y >> num;
                bt.add(x, y, num);
            }
            else if (s == "SUM")
            {
                int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
                cout << bt.sum(x1, y1, x2, y2) << endl; 
            }
        }
        cout << endl;
    }

    return 0;
}
