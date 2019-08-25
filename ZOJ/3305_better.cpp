/*
    Author : manu_sy
    
    Idea : Similar to 
        https://github.com/magdy-hasan/competitive-programming/blob/master/Other/ZOJ%20Get%20Sauce.cpp
*/
#include <bits/stdc++.h>
using namespace std;

/* Template Begins */

#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'

// Debug //
#define trace(x)                 cerr << #x << ": " << x << endl;
#define trace2(x, y)             cerr << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)          cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl;
#define trace4(a, b, c, d)       cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << endl;

const int N = 17;
const int MM = (1<<N)+5;
const int M = 5e4+7;

/* Template Ends */
int n, m, cnt[MM], a[MM];

int calc(int mask) {

    int &ret = cnt[mask];
    if (ret != -1)  return ret;
    
    ret = 0;
    for (int submask = mask; submask != 0; submask = (submask-1)&mask) if (a[submask]) {
        ret = max(ret, 1 + calc(mask & (~submask)));
    }
    return ret;
}

signed main() {

    IOS;
    while(cin >> n >> m) {

        int ans = 0;
        for (int i = 0; i < (1<<n); i++) cnt[i] = -1, a[i] = 0;

        while (m--) {
            int k;  cin >> k;
            int cur = 0;
            while (k--) {
                int x;  cin >> x;
                cur |= (1<<(x-1));
            }
            a[cur] = 1;
        }   

        cout << calc((1<<n)-1) << endl;
    }

    return 0;
}
