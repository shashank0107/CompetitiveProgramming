/*
    Author : manu_sy
    Idea : Just loop through both arrays simulatanously, i is counter for s1 and j for s2 :
          -  if s1[i] == s2[j]:  no swap needed
          -  else we need to find the first occurence of s2[j] that comes after ith position and then we have to bring it
             till current position by swapping with everyone in between
             - Use BIT for find the next position of s2[j] = p (BIT for each character)
             - Use bitmasking to check whether we can swap with everyone
               - Just keep kth bit set if 'a' + k comes b/w i to p
               
    Complexity : O(n*logn*26)
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

const int C = 27;
const int N = 1e5+7;
const ll hell = (1LL << 32);
/** Template Ends **/
int m, sw[C], n;
int bit[C][N];
bool taken[N];

struct BIT {
    int n;
    
    BIT(int n): n(n+1) {
        LP(i,C) LP(j,n+10) bit[i][j] = 0;
    }
    void add(int ii, int idx, int val) {
        for (++idx; idx < n; idx += idx & -idx)
            bit[ii][idx] += val,
            bit[26][idx] += val;
    }
    int sum(int ii, int idx) {
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret += bit[ii][idx];
        return ret;
    }
    int sum(int ii, int l, int r) {
        return sum(ii, r) - sum(ii, l-1);
    }
    int find_next(int ii, int l) {
        int lo = l, hi = n - 1;
        while (hi - lo > 1)
        {
            int mid = (hi + lo) / 2;
            if (sum(ii, l, mid) >= 1)   hi = mid;
            else lo = mid;
        }
        if (sum(ii, l, lo) == 1)    return lo;
        else if (sum(ii, l, hi) == 1)   return hi;
        else {
            assert(sum(ii,l,hi) == 0);
            return -1;
        }
    }
    int present(int l, int r) {
        int ret = 0;
        for (int i = 0; i < 26; i++)
            if (sum(i, l, r))
                ret |= (1 << i);
        return ret;
    }
};

signed main() {

    IOS;
    int t;  cin >> t;
    while (t--)
    {
        string s1, s2; cin >> s1 >> s2;
        if (s1.size() != s2.size()) 
        {
            cout << -1 << endl;
            continue;
        }

        memset(sw, 0, sizeof sw);
        cin >> m;
        for (int i = 0; i < m; i++)
        {
            char c1, c2;    cin >> c1 >> c2;
            sw[c1-'a'] |= (1 << (c2 - 'a'));
            sw[c2-'a'] |= (1 << (c1 - 'a'));
        }

        n = s1.size();
        BIT bt(n + 1);
        LP(i,n) taken[i] = false;

        for (int i = 0; i < n; i++) 
        {
            bt.add(s1[i]-'a', i, 1);
        }

        ll ans = 0;
        bool valid = true;
        for (int i = 0, j = 0; i < n && j < n; )
        {
            if (taken[i]) 
            {
                i++;
                continue;
            }
            if (s1[i] == s2[j])
            {
                i++, j++;
            }
            else
            {
                int p = bt.find_next(s2[j]-'a', i);
                if (p == -1)
                {
                    valid = false;
                    break;
                }
                else
                {
                    int nums = bt.present(i, p - 1);
                    if ( nums & ( ~sw[s2[j] - 'a'] ) )
                    {
                        valid = false;
                        break;
                    }
                    else
                    {
                        bt.add(s2[j] - 'a', p, -1);
                        taken[p] = true;
                        ans = (ans + bt.sum(26, i, p - 1)) % hell;
                    }
                    j++;
                }
            }
        }
        if (valid)  cout << ans << endl;
        else cout << -1 << endl;
    }

    return 0;
}
