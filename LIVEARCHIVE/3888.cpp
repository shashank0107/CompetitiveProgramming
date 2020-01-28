/*
    Author : manu_sy
    Idea : Do two bfs simultaneously from the starting state and the ending state to arrive at solution
    Note : This solution works only works on sample i/o but RE on judge.
*/
#include "bits/stdc++.h"
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

#ifdef LOCALI
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif

/* Debug Ends */

const int N = 16+5;
const int M = 1e8;
const int K = 17;
int dx[] = {0, 0, 1, -1, 0};
int dy[] = {1, -1, 0, 0, 0};

/** Template Ends **/
int w, h, n;
char m[N][N];
int vis[2][M], tme[2][M], ct;
bool noerror;

struct pos 
{
    int ax, ay, bx, by, cx, cy;
    pos(int ax=0, int ay=0, int bx=0, int by=0, int cx=0, int cy=0):
        ax(ax), ay(ay), bx(bx), by(by), cx(cx), cy(cy) {}
    void print() {
        debug(ax, ay, bx, by, cx, cy);
    }
    bool operator==(pos& oth) {
        return ax==oth.ax && ay==oth.ay && bx==oth.bx && by==oth.by && cx==oth.cx && cy==oth.cy;
    }
} ini, fnl;
int gen(int a, int b, int c, int d, int e, int f) 
{
    return a + b * (K) + c * (K * K) + d * (K * K * K) + e * (K * K * K * K) + f * (K * K * K * K * K);
}
int gen(pos& p) {   
    return gen(p.ax, p.ay, p.bx, p.by, p.cx, p.cy);
}
pos get(int num)
{
    int x = num;
    pos p;
    p.ax = x % (K), x /= (K);
    p.ay = x % (K), x /= (K);
    p.bx = x % (K), x /= (K);
    p.by = x % (K), x /= (K);
    p.cx = x % (K), x /= (K);
    p.cy = x % (K);

    assert(gen(p) == num);
    return p;
}
void mark(pos& p, int t, int i)
{
    int x = gen(p.ax, p.ay, p.bx, p.by, p.cx, p.cy);
    vis[i][x] = ct;
    tme[i][x] = t;
}
void input() 
{
    ini = pos(), fnl = pos();
    map<char, pair<int, int> > sm, lg;
    string temp;
    getline(cin, temp);
    LP(i,h) 
    {
        getline(cin, temp);
        debug(i, temp);
        LP(j,w) 
        {
            m[i][j] = temp[j];
            if (m[i][j] >= 'a' && m[i][j] <= 'z')   sm[m[i][j]] = mp(i, j);
            else if (m[i][j] >= 'A' && m[i][j] <= 'Z') lg[m[i][j]] = mp(i, j);
        }
    }
    for (auto c : sm)
    {
        char l = 'A' + (c.F - 'a');
        //assert(lg.count(l));
        if (ini.ax == 0)
        {
            ini.ax = c.S.F, ini.ay = c.S.S;
            fnl.ax = lg[l].F, fnl.ay = lg[l].S;
        }
        else if (ini.bx == 0)
        {
            ini.bx = c.S.F, ini.by = c.S.S;
            fnl.bx = lg[l].F, fnl.by = lg[l].S;
        }
        else if (ini.cx == 0)
        {
            ini.cx = c.S.F, ini.cy = c.S.S;
            fnl.cx = lg[l].F, fnl.cy = lg[l].S;
        }
        //else assert(false);
    }
}
bool valid(int x, int y) {
    return x > 0 && x < h && y > 0 && y < w && m[x][y] != '#'; 
}
signed main() {

    IOS;
    vector<int> v(10);
    while (cin >> w >> h >> n)
    {
        if (w == 0 && h == 0 && n == 0) break;
        ct++;
        input();
        ini.print(); fnl.print();
        if (ini == fnl) 
        {
            cout << 0 << endl;
            continue;
        }

        queue<pair<pos,int> > q1, q2;
        q1.push(mp(ini, 0)), q2.push(mp(fnl, 0));
        mark(ini, 0, 0);    
        mark(fnl, 0, 1);    

        int cur = 0, ans = -1;
        debug("q1");
        while (!q1.empty() || !q2.empty())
        {
            while (q1.front().S == cur)
            {
                auto ff = q1.front();   q1.pop();
                pos p = ff.F;
                int vv = gen(p);

                // move a
                LP(i,5) 
                {
                    int nax = p.ax + dx[i];
                    int nay = p.ay + dy[i];
                    if (valid(nax, nay) && mp(nax, nay) != mp(p.bx, p.by) && mp(nax, nay) != mp(p.cx, p.cy))
                    {
                        if (p.bx)
                        {
                            LP(k,5) 
                            {
                                int nbx = p.bx + dx[k];
                                int nby = p.by + dy[k];
                                if (valid(nbx, nby) && mp(nbx, nby) != mp(nax, nay) && mp(nbx, nby) != mp(p.cx, p.cy))
                                {
                                    if (p.cx)
                                    {
                                        LP(y,5)
                                        {
                                            int ncx = p.cx + dx[y];
                                            int ncy = p.cy + dy[y];
                                            if (valid(ncx, ncy) && mp(ncx, ncy) != mp(nax, nay) && mp(ncx, ncy) != mp(nbx, nby))
                                            {
                                                if (mp(nax, nay) == mp(p.bx, p.by) && mp(nbx, nby) == mp(p.ax, p.ay))   continue;
                                                if (mp(nax, nay) == mp(p.cx, p.cy) && mp(ncx, ncy) == mp(p.ax, p.ay))   continue;
                                                if (mp(ncx, ncy) == mp(p.bx, p.by) && mp(nbx, nby) == mp(p.cx, p.cy))   continue;
                                                int pval = gen(nax, nay, nbx, nby, ncx, ncy);
                                                pos cpos = get(pval);
                                                if (pval != gen(cpos))  continue;
                                                // debug("cpos");  cpos.print();
                                                if (vis[0][pval] < ct)
                                                {
                                                    mark(cpos, cur + 1, 0);
                                                    q1.push(mp(cpos, cur + 1));
                                                    if (vis[1][pval] == ct)
                                                    {
                                                        ans = tme[0][pval] + tme[1][pval];
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if (mp(nax, nay) == mp(p.bx, p.by) && mp(nbx, nby) == mp(p.ax, p.ay))   continue;
                                        //assert(p.cx == 0 && p.cy == 0);
                                        int pval = gen(nax, nay, nbx, nby, 0, 0);
                                        pos cpos = get(pval);
                                        if (pval != gen(cpos))  continue;
                                        // debug("cpos", i);  cpos.print();
                                        if (vis[0][pval] < ct)
                                        {
                                            debug("marked");
                                            mark(cpos, cur + 1, 0);
                                            q1.push(mp(cpos, cur + 1));
                                            if (vis[1][pval] == ct)
                                            {
                                                ans = tme[0][pval] + tme[1][pval];
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            //assert(p.bx == p.by && p.by == p.cx && p.cx == p.cy && p.cy == 0);
                            int pval = gen(nax, nay, 0, 0, 0, 0);
                            pos cpos = get(pval);
                            if (pval != gen(cpos))  continue;
                            // debug("cpos");  cpos.print();
                            if (vis[0][pval] < ct)
                            {
                                mark(cpos, cur + 1, 0);
                                q1.push(mp(cpos, cur + 1));
                                if (vis[1][pval] == ct)
                                {
                                    ans = tme[0][pval] + tme[1][pval];
                                }
                            }
                        }
                    }
                }
            }
            if (ans != -1)  break;

            while (q2.front().S == cur)
            {
                auto ff = q2.front();   q2.pop();
                pos p = ff.F;
                int vv = gen(p);

                // move a
                LP(i,5)
                {
                    int nax = p.ax + dx[i];
                    int nay = p.ay + dy[i];
                    if (valid(nax, nay))
                    {
                        if (p.bx)
                        {
                            LP(k,5) 
                            {
                                int nbx = p.bx + dx[k];
                                int nby = p.by + dy[k];
                                if (valid(nbx, nby) && mp(nbx, nby) != mp(nax, nay))
                                {
                                    if (p.cx)
                                    {
                                        LP(y,5) 
                                        {
                                            int ncx = p.cx + dx[y];
                                            int ncy = p.cy + dy[y];
                                            if (valid(ncx, ncy) && mp(ncx, ncy) != mp(nax, nay) && mp(ncx, ncy) != mp(nbx, nby))
                                            {
                                                if (mp(nax, nay) == mp(p.bx, p.by) && mp(nbx, nby) == mp(p.ax, p.ay))   continue;
                                                if (mp(nax, nay) == mp(p.cx, p.cy) && mp(ncx, ncy) == mp(p.ax, p.ay))   continue;
                                                if (mp(ncx, ncy) == mp(p.bx, p.by) && mp(nbx, nby) == mp(p.cx, p.cy))   continue;

                                                int pval = gen(nax, nay, nbx, nby, ncx, ncy);
                                                pos cpos = get(pval);
                                                if (pval != gen(cpos))  continue;
                                                // debug("cpos");  cpos.print();
                                                if (vis[1][pval] < ct)
                                                {
                                                    mark(cpos, cur + 1, 1);
                                                    q2.push(mp(cpos, cur + 1));
                                                    if (vis[0][pval] == ct)
                                                    {
                                                        ans = tme[0][pval] + tme[1][pval];
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        //assert(p.cx == 0 && p.cy == 0);
                                        int pval = gen(nax, nay, nbx, nby, 0, 0);
                                        if (mp(nax, nay) == mp(p.bx, p.by) && mp(nbx, nby) == mp(p.ax, p.ay))   continue;
                                        
                                        pos cpos = get(pval);
                                        if (pval != gen(cpos))  continue;
                                        // debug("cpos");  cpos.print();
                                        if (vis[1][pval] < ct)
                                        {
                                            mark(cpos, cur + 1, 1);
                                            q2.push(mp(cpos, cur + 1));
                                            if (vis[0][pval] == ct)
                                            {
                                                ans = tme[0][pval] + tme[1][pval];
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            //assert(p.bx == p.by && p.by == p.cx && p.cx == p.cy && p.cy == 0);
                            int pval = gen(nax, nay, 0, 0, 0, 0);
                            pos cpos = get(pval);
                            if (pval != gen(cpos))  continue;
                            // debug("cpos");  cpos.print();
                            if (vis[1][pval] < ct)
                            {
                                mark(cpos, cur + 1, 1);
                                q2.push(mp(cpos, cur + 1));
                                if (vis[0][pval] == ct)
                                {
                                    ans = tme[0][pval] + tme[1][pval];
                                }
                            }
                        }
                    }
                }
            }
            if (ans != -1)  break;
            cur++;
        }
        //assert(ans != -1);
        cout << ans << endl;
    }


    return 0;
}
