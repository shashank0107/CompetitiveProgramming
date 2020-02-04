/*
    Author : manu_sy
    Idea : meet-in-middle
          - Just do 4 step bfs from the start state and 4 step bfs from the end state and check if they meet anywhere
*/
#include "bits/stdc++.h"
using namespace std;
 
/** Template Begins **/
 
typedef long long        ll;
typedef pair<int,int>    PII;
typedef vector<int>      vi;
 
#define IOS         ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl        '\n'
#define pb          push_back
#define F           first
#define S           second
#define mp          make_pair
#define all(a)      (a).begin(), (a).end()
#define FOR(i,a,b)  for(int i=a;i<=b;i++)
#define LP(i,n)     for(int i=0;i< n;i++)
#define x1          x123
#define x2          x323
#define y1          y123
#define y2          y234
 
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
 
const int N = 8;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int ddx[] = {0, 0, 2, -2};
int ddy[] = {2, -2, 0, 0};
 
/** Template Ends **/
bool vis[2][N][N][N][N][N][N][N][N];
 
bool valid(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}
bool vss(vector<PII> xy, int i) {
    return vis[i][xy[0].F][xy[0].S][xy[1].F][xy[1].S][xy[2].F][xy[2].S][xy[3].F][xy[3].S];
}
void mark(vector<PII> xy, int i) {
    vis[i][xy[0].F][xy[0].S][xy[1].F][xy[1].S][xy[2].F][xy[2].S][xy[3].F][xy[3].S] = true;
}
 
bool move(vector<PII> xy, int id) {
    queue<pair<vector<PII>, int> > q;
    sort(all(xy));
    mark(xy, id);
    if (id == 1) {
        if (vss(xy, 0)) return true;
    }
    q.push(mp(xy, 0));
 
    while (!q.empty())
    {
        auto p = q.front(); q.pop();
        xy = p.F;
        int step = p.S;
 
        if (step < 4)
        {
            LP(i,4)
            {
                LP(j,4)
                {
                    int nx = xy[i].F + dx[j];
                    int ny = xy[i].S + dy[j];
                    if (valid(nx, ny))
                    {
                        bool nbr = false;
                        LP(k,4) if (mp(nx, ny) == xy[k]) nbr = true;
 
                        if (!nbr)
                        {
                            auto txy = xy;
                            txy[i].F = nx, txy[i].S = ny;
                            sort(all(txy));
                            if (!vss(txy, id)) 
                            {
                                mark(txy, id);
                                if (id == 1 && vss(txy, 0)) return true;
                                if (step + 1 < 4) q.push(mp(txy, step + 1));
                            }
                        }   
                        else
                        {
                            int nnx = xy[i].F + ddx[j];
                            int nny = xy[i].S + ddy[j];
                            if (valid(nnx, nny))
                            {
                                bool nbr = false;
                                LP(k,4) if (mp(nnx, nny) == xy[k]) nbr = true;
                                
                                if (!nbr)
                                {
                                    auto txy = xy;
                                    txy[i].F = nnx, txy[i].S = nny;
                                    sort(all(txy)); 
                                    if (!vss(txy, id)) 
                                    {
                                        mark(txy, id);
                                        if (id == 1 && vss(txy, 0)) return true;
                                        if (step + 1 < 4) q.push(mp(txy, step + 1));
                                    }
                                }
                            }
 
                        } 
                    }
                }
            }
        }
    }
    return false;
}

signed main() {
 
    IOS;
    int t;  cin >> t;
    while (t--)
    {
        vector<PII> xy1(4), xy2(4);
        LP(i,4) cin >> xy1[i].F >> xy1[i].S, xy1[i].F--, xy1[i].S--;
        LP(i,4) cin >> xy2[i].F >> xy2[i].S, xy2[i].F--, xy2[i].S--;
        
        memset(vis, false, sizeof vis);
 
        move(xy1, 0);
        bool found = move(xy2, 1);

        if (found)  cout << "YES" << endl;
        else cout << "NO" << endl;
    }
 
    return 0;
}
