/*
    Author : manu_sy

    Idea : Just reduce the equation and transform the matrix and calculate max subrectangle sum o(n^3)
    Similar to 
        - https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/SPOJ/SPOJ_FISHES.txt
*/
#include <bits/stdc++.h>
using namespace std;

/* Template Begins */

typedef long long ll;

#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'

const int N = 1e2+7;
const int K = 5e2+7;

/* Template Ends */
int n, m, h, k, t;
int a[N][N];
ll pre[N][N];
int v[K];
int z[K];

signed main() {

    //IOS;
    int cases;  cin >> cases;
    for (int tc = 1; tc <= cases; tc++) {
        
        cin >> n >> m >> h >> k >> t;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) cin >> a[i][j];

        memset(z, 0, sizeof z);
        for (int i = 0; i < t; i++) {
            int x;  cin >> x;
            for (int i = 1; i <= k; i++) { 
                cin >> v[i];
                z[i] += x*v[i];
            }
        }

        for (int i = 1; i <= n; i++) 
            for (int j = 1; j <= m; j++) a[i][j] = z[a[i][j]];

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                pre[i][j] = pre[i][j-1] + a[i][j];
            }
        }

        ll ans = INT_MIN;
        for (int l = 1; l <= m; l++) {
            for (int r = l; r <= m; r++) {

                ll last = 0;
                for (int k = 1; k <= n; k++) {
                    ll cur = pre[k][r]-pre[k][l-1] + last;
                    last = max(cur, 0LL);
                    ans = max(ans, cur);
                }
            }   
        }
        cout << "Case #" << tc << ":" << endl;
        cout << ans+h << endl;
    }

    return 0;
}
