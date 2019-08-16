/*
    Author : Shashank Yadav

    Idea :
        - dp[i][j] = min cost to get j holes till ith index
        - precalculate cost[i][j] as the min cost to i till j (inclusive) holes
        - dp[i][j] = min(dp[i-1][j], dp[i-r][j-r] + cost[i-r+1][i]), 1 <= r <= i, r denotes you are taking r consequtive holes till i
*/
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'
#define FOR(i,a,b) for (int i = a; i <= b; i++)

const int N = 3e2+7;
const int INF = 1e15;

int n, m, k, cost[N][N], dp[N][N], l, r, c;

void pre() {
    FOR(i,0,n) FOR(j,0,n) cost[i][j] = INF, dp[i][j] = INF;
}

signed main() {

    IOS;
    cin >> n >> m >> k;
    pre();

    while(m--) {
        cin >> l >> r >> c;
        FOR(j,l,r) cost[l][j] = min(cost[l][j], c);
    }

    int ans = INF;
    dp[0][0] = 0;
    FOR(i,1,n) FOR(j,0,i) {
        if (j == 0){ dp[i][j] = 0; continue;   }
        
        dp[i][j] = dp[i-1][j];

        FOR(r,1,i) {
            dp[i][j] = min(dp[i][j], dp[i-r][max(j-r,0LL)]+cost[i-r+1][i]);
        }

        if (j >= k) {
            ans = min(ans, dp[i][j]);
        }
    }

    if (ans != INF) cout << ans << endl;
    else cout << -1 << endl;

    return 0;
}
