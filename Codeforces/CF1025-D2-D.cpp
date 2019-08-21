/*
    Author : manu_sy
    Idea : Same as editorial
        https://codeforces.com/blog/entry/61323
*/
#include <bits/stdc++.h>
using namespace std;

/* Template Begins */

#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'

const int N = 7e2+7;

/* Template Ends */
int n, a[N], dp[N][N][2];
bool gcd[N][N];

int poss(int l, int r, int side) {
    if (l > r)  return 1;

    int &ret = dp[l][r][side];
    if (ret != -1)  return ret;
    ret = 0;

    int id = (side ? r+1 : l-1);
    for (int rt = l; rt <= r; rt++) {
        if (gcd[id][rt]) {
            if (poss(l, rt-1,1) && poss(rt+1,r,0)) {
                ret = 1;
                break;
            }
        }
    }
    return ret;
}

signed main() {

    IOS;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) 
            gcd[i][j] = gcd[j][i] = (__gcd(a[i], a[j]) != 1);

    memset(dp, -1, sizeof dp);
    for (int rt = 0; rt < n; rt++) {
        if (poss(0,rt-1,1) && poss(rt+1,n-1,0)) {
            cout << "Yes" << endl;
            return 0;
        }
    }
    cout << "No" << endl;

    return 0;
}
