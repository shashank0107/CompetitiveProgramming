/*
    Author : manu_sy

    Idea : Final array would be divisible by a prime.
    - These primes can be divisors of v[0] or v[n-1] or (v[0]+-1) or (v[n-1]+-1)
    - Now for each prime calculate the answer using dp
    - dp[i][0/1/2] - segment not start/ segment continue here / segment end here or before 
*/
#include <bits/stdc++.h>
using namespace std;

/* Template Begins */
//#define int ll
typedef long long ll;

#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'

// Debug //
#define trace(x)                 cerr << #x << ": " << x << endl;
#define trace2(x, y)             cerr << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)          cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl;
#define trace4(a, b, c, d)       cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << endl;

const int N = 1e6+7;

/* Template Ends */
int n, v[N];
ll a, b, dp[N][3];

ll add(ll a, ll b) {
    if (a == -1 || b == -1) return -1;
    return a+b;
}
ll minn(ll a, ll b) {
    if (a == -1)    return b;
    if (b == -1)    return a;
    return min(a, b);
}

ll calc() {

    vector<int> pf;
    int aa = v[0];
    for (ll i = 2; i*i <= v[0]; i++)
        if (aa%i == 0) {
            pf.push_back(i);
            while(aa%i == 0)  aa /= i;
        }
    if (aa > 1) pf.push_back(aa);

    //trace(v[0]);
    ll ans = 1e18;
    for (auto p : pf) {

        ll sum = (n-1)*a;
        for (int k = 0; k < 3; k++) dp[0][k] = 0;

        //trace(p);
        for (int i = 1; i < n; i++) {
            if (dp[i-1][0] != -1) {
                if (v[i]%p == 0) {
                    dp[i][0] = add(dp[i-1][0], 0);
                } else if ((v[i]-1)%p == 0 || (v[i]+1)%p == 0) {
                    dp[i][0] = add(dp[i-1][0], b);
                } else {
                    dp[i][0] = -1;
                }
            } else dp[i][0] = -1;

            dp[i][1] = add(a, minn(dp[i-1][1], dp[i-1][0]));
            dp[i][2] = dp[i][1];

            if (v[i]%p == 0) {
                dp[i][2] = minn(dp[i][2], dp[i-1][2]);
            } else if ((v[i]-1)%p == 0 || (v[i]+1)%p == 0) {
                dp[i][2] = minn(dp[i][2], add(b, dp[i-1][2]));
            }
            //trace3(dp[i][0], dp[i][1], dp[i][2]);
        }

        ll cur = minn(dp[n-1][0], minn(dp[n-1][1], dp[n-1][2]));
        //trace(cur);
        ans = min(ans, cur);
    }
    return ans;

    return 0;
}

ll solve() {

    ll ret1 = calc();
    v[0]++;
    ll ret2 = calc() + b;
    v[0] -= 2;
    ll ret3 = calc() + b;
    v[0]++;

    //trace3(ret1, ret2, ret3);
    return min(ret1, min(ret2, ret3));
}

signed main() {

    IOS;
    cin >> n >> a >> b;
    for (int i = 0; i < n; i++) cin >> v[i];

    int g = v[0];
    for (int i = 1; i < n; i++) g = __gcd(g, v[i]);
    if (g > 1) {
        cout << 0 << endl;  return 0;
    }

    ll ans = (n-1)*a;
    ll ans1 = solve();
    reverse(v,v+n);
    ll ans2 = solve();
    //trace2(ans1, ans2);

    ans = min(ans, min(ans1, ans2));
    cout << ans << endl;

    return 0;
}
