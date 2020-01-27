/*
    Author : manu_sy
    Idea : - First make count of 3s in a1*b1 & a2*b2 same
           - Then make count of 2s same
           Obsevation - You can always do the above
           Check if a1*b1 == a2*b2
*/
#include "bits/stdc++.h"
using namespace std;

/** Template Begins **/
#define int              ll
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
int a1, b1, a2, b2, ans;

struct rect {
    int a, b, c2, c3;
    rect(int a, int b, int c2, int c3):a(a),b(b),c2(c2),c3(c3){}
    void print() {
        debug(a, b, c2, c3);
    }
};

int count(int x, int y) {
    int cnt = 0;
    while (x % y == 0)  x /= y, cnt++;
    return cnt;
}
void red_3(rect& r, int need3) {
    assert(r.c3 >= need3);
    while (r.c3 > need3) 
    {
        if (r.a % 3 == 0)       r.a = (2 * r.a) / 3;
        else if (r.b % 3 == 0)  r.b = (2 * r.b) / 3;
        else assert(false);
        r.c3--;
        r.c2++;
        ans++;
    }
}
void red_2(rect& r, int need2) {
    assert(r.c2 >= need2);
    while (r.c2 > need2) 
    {
        if (r.a % 2 == 0)       r.a = (r.a) / 2;
        else if (r.b % 2 == 0)  r.b = (r.b) / 2;
        else assert(false);
        r.c2--;
        ans++;
    }
}

signed main() {

    IOS;
    cin >> a1 >> b1 >> a2 >> b2;

    rect r1 = rect(a1, b1, count(a1, 2) + count(b1, 2), count(a1, 3) + count(b1, 3));
    rect r2 = rect(a2, b2, count(a2, 2) + count(b2, 2), count(a2, 3) + count(b2, 3));

    if (r1.c3 > r2.c3)  red_3(r1, r2.c3);
    else                red_3(r2, r1.c3);

    if (r1.c2 > r2.c2)  red_2(r1, r2.c2);
    else                red_2(r2, r1.c2);

    if (r1.a * r1.b != r2.a * r2.b) cout << -1 << endl;
    else 
    {
        cout << ans << endl;
        cout << r1.a << " " << r1.b << endl;
        cout << r2.a << " " << r2.b << endl;
    }

    return 0;
}
