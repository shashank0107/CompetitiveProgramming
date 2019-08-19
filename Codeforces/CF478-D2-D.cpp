/*
    Author : manu_sy

    Idea : Same as editorial 
        https://codeforces.com/blog/entry/14307#comment-192751
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'

const int N = 2e5+7;
const int hell = 1e9+7;

// Debug //
#define trace(x)                 cerr << #x << ": " << x << endl;
#define trace2(x, y)             cerr << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)          cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl;
#define trace4(a, b, c, d)       cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << endl;

/* Template Ends */

int r, g;
ll pre[N], cur[N]; 

ll f(ll x) {
    return (x*(x+1))/2;
}
int calc(int blocks) {
    ll lo = 0, hi = blocks;
    while (hi-lo>1) {
        ll mid = (hi+lo)/2;
        if (f(mid) <= blocks)   lo = mid;
        else hi = mid;
    }
    if (f(hi) <= blocks)  return hi;
    else if (f(lo) <= blocks) return lo;
    else return 0;
}
void add(ll& a, ll b) {
    a = (a+b)%hell;
}
int ans(int a) {
    cout << a << endl;
    exit(0);
}
signed main() {

    IOS;
    cin >> r >> g;

    pre[r] = 1;
    int h = calc(r+g);
    if (h == 1) {
        if (r >= 1 && g >= 1)   ans(2);
        else ans(1);
    }

    for (int i = 1; i <= h; i++) {
        for (int rr = 0; rr <= r; rr++) {

            // cur state is height = i and red blocks remaining = rr
            ll rd_use = r-rr;
            ll gr_use = f(i)-rd_use;

            if (gr_use <= g && rd_use <= r && gr_use >= 0 && rd_use >= 0) {
                add(cur[rr], pre[rr]);
                if (rr+i <= r) { 
                    add(cur[rr], pre[rr+i]);
                }
            }   
            else cur[rr] = 0;
        }
        if (i != h) {
            for (int rr = 0; rr <= r; rr++) {
                pre[rr] = cur[rr];
                cur[rr] = 0;
            }
        }
    }
    ll ans = 0;
    for (int rr = 0; rr <= r; rr++) add(ans, cur[rr]);
    cout << ans << endl;

    return 0;
}
