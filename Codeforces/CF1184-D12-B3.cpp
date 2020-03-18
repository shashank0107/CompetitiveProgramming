/*
    Author : manu_sy
    Idea : same as editorial
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
 
const int NN = 1e2+7, N = 1e5+7, NNN = 2e3+7;
const int INF1 = 1e17+100;

/** Template Ends **/

int n, m, dist[NN][NN], s, b, k;
bool mark[N];
int sx[N], sa[N], sf[N], sp[N];
vector<PII> base[NN];
int profit[N];
vector<int> posp, negp;
int d1[N], d2[N], aa, bb;
ll ans;

void fill_graph() 
{
    FOR(i,1,n) FOR(j,1,n) dist[i][j] = (i == j ? 0 : INF1);
    LP(i,m) 
    {
        int u, v; cin >> u >> v;
        dist[u][v] = dist[v][u] = min(dist[u][v], 1LL);
    }
    FOR(k,1,n) FOR(i,1,n) FOR(j,1,n) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}
void simplify_bases()
{
    FOR(i,1,n) sort(all(base[i]));
    FOR(i,1,n)
    {
        int mg = 0;
        for (auto &bs: base[i]) bs.S = max(bs.S, mg), mg = bs.S;
        debug(i, base[i]);
    }
}
void calc_profit()
{
    FOR(i,1,s)
    {
        profit[i] = -INF1;
        FOR(j,1,n) if (dist[sx[i]][j] <= sf[i])
        {
            int pos = upper_bound(all(base[j]), mp(sa[i], INF1)) - base[j].begin() - 1;
            if (pos == -1)  continue;
            profit[i] = max(profit[i], base[j][pos].S - sp[i]);
        }
        debug(i, profit[i]);
    }
}
void get_dep() 
{
    LP(i,k)
    {
        debug(d1[i], d2[i]);
        cin >> d1[i] >> d2[i];
        mark[d1[i]] = mark[d2[i]] = true;
    }
    FOR(i,1,s)
    {
        ans += max(0LL, profit[i]);
        if (!mark[i]) continue;
        if (profit[i] >= 0) posp.pb(i);
        else                negp.pb(i);
    }
    sort(all(posp));   sort(all(negp));
    debug(posp); debug(negp);
}
namespace Maxflow{
    const int maxn=2022;
    const int maxm=66666;
    const int inf=INF1;
 
    int g[maxn],to[maxm],np[maxm],cp;
    int n,u,v,now,source,sink;
    int sum,cap[maxm],a[maxn];
    int d[maxn],p[maxn],cur[maxn],cnt[maxn];
 
    void add_edge(int x,int y,int z){
        // printf("%d - %d: %d\n",x,y,z);
        cap[cp]=z;to[cp]=y;np[cp]=g[x];g[x]=cp++;cap[cp]=0;to[cp]=x;np[cp]=g[y];g[y]=cp++;
    }
 
    void init(){
        cp=2; memset(g,0,sizeof(g));
    }
    int maxflow(){
        sum=0;
        for(u=1;u<=n;u++)cur[u]=g[u]; a[u=source]=inf; memset(d,0,sizeof(int)*(n+1)); memset(cnt,0,sizeof(int)*(n+1)); cnt[0]=n;
        while(d[source]<n)
        {
            for(now=cur[u];now;now=np[now])if(cap[now]&&d[v=to[now]]+1==d[u])break; cur[u]=now;
            if(now)
            {
                p[v]=now; a[v]=cap[now]; if(a[v]>a[u])a[v]=a[u];
                if((u=v)==sink)
                {
                    do{cap[p[u]]-=a[sink]; cap[p[u]^1]+=a[sink]; u=to[p[u]^1];}while(u!=source);
                    sum+=a[sink]; a[source]=inf;
                }
            }
            else
            {
                if(--cnt[d[u]]==0)break; d[u]=n; cur[u]=g[u];
                for(now=g[u];now;now=np[now]) if(cap[now] && d[u]>d[to[now]]+1) d[u]=d[to[now]]+1;
                cnt[d[u]]++;
                if(u!=source)u=to[p[u]^1];
            }
        }
    //    printf("maxflow\n");
        return sum;
    }
}
int findp(int s1) {
    if (profit[s1] >= 0)    return lower_bound(all(posp), s1) - posp.begin() + 1;
    else                    return lower_bound(all(negp), s1) - negp.begin() + aa + 1;
}
signed main() {
 
    IOS;
    cin >> n >> m;
    fill_graph();
    cin >> s >> b >> k;
    FOR(i,1,s) cin >> sx[i] >> sa[i] >> sf[i] >> sp[i];
    LP(i,b)
    {
        int x, d, g;    cin >> x >> d >> g;
        base[x].pb(mp(d, g));
    }
    simplify_bases();
    calc_profit();
    get_dep();
    aa = posp.size(), bb = negp.size();

    Maxflow::init();
    Maxflow::n = aa + bb + 2;
    Maxflow::source = 0, Maxflow::sink = aa + bb + 1;
    LP(i,aa) Maxflow::add_edge(0, i + 1, profit[posp[i]]);
    LP(i,bb) Maxflow::add_edge(aa + i + 1, Maxflow::sink, -profit[negp[i]]);

    LP(i,k)
    {
        int s1 = d1[i], s2 = d2[i];
        int x1 = findp(s1), x2 = findp(s2);  
        debug(s1, s2, x1, x2);
        Maxflow::add_edge(x1, x2, INF1);
    }
    int ff = Maxflow::maxflow();
    debug(ff);
    cout << ans - ff << endl;
 
    return 0;
}
