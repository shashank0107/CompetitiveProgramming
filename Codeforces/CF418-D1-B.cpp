/*
    Author : manu_sy

    Idea - Similar to editorial (Div1B)
    https://codeforces.com/blog/entry/11730
*/
#include <bits/stdc++.h>
using namespace std;

//#define int long long
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'

typedef long long ll;

const int N = 1e2+2;
const int MM = (1<<20)+1;

/* Template Ends */
struct item {
    int c, k, mask;
};
ll n, m, b, cost[MM], ans[MM], ncost[MM];
item frnd[N];

bool comp(const item& a, const item& b) {
    return a.k < b.k;
}
ll minn(ll a, ll b) {
    //assert(a != -1 || b != -1);
    if (a == -1)    return b;
    if (b == -1)   return a;
    return min(a, b);
}
signed main() {

    IOS;
    cin >> n >> m >> b;
    for (int i = 1; i <= n; i++) {
        cin >> frnd[i].c >> frnd[i].k;
        frnd[i].mask = 0;
        int m;  cin >> m;
        while(m--) {
            int x;  cin >> x;
            frnd[i].mask |= (1<<(x-1));
        }
    }
    sort(frnd+1, frnd+n+1, comp);

    memset(ans, -1, sizeof ans);
    memset(cost, -1, sizeof cost);
    cost[0] = 0;
    ncost[0] = 0;

    ll ret = -1;
    bool found = false;

    for (int i = 1; i <= n; i++) {
        
        for (int mask = 0; mask < (1<<m); mask++) ncost[mask] = cost[mask];
        
        for (int mask = 0; mask < (1<<m); mask++) {
            if (cost[mask] != -1) {
                int new_mask = (mask | frnd[i].mask);
                ncost[new_mask] = minn(ncost[new_mask], cost[mask] + frnd[i].c);
                ans[new_mask] = minn(ans[new_mask], cost[mask] + frnd[i].c + frnd[i].k*b);
            }   
        }
        if (ans[(1<<m)-1] != -1) {
            found = true;
            ret = minn(ret, ans[(1<<m)-1]);
        }

        for (int mask = 0; mask < (1<<m); mask++) cost[mask] = ncost[mask];
    }
    if (!found) cout << -1 << endl;
    else cout << ret << endl;

    return 0;
}
