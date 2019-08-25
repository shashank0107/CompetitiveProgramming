/*
    Author : manu_sy
    
    Idea : Keep a segment tree with max and min values.
      - While updating a range if max[range] <= h : update whole range - no need to go down just update here and add to ans
                               if min[range] > h  : no update          - no need to go down
                          else go down and update and add to ans
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

const int N = 1e5+7;

/* Template Ends */
int n, mx[4*N], mn[4*N], m, lazy[4*N], l[N], r[N], h[N], len;

void upd(int nd) {
    mx[nd] = max(mx[2*nd], mx[2*nd+1]);
    mn[nd] = min(mn[2*nd], mn[2*nd+1]);
}

void update(int st, int en, int nd, int h, int l, int r) {
    if (lazy[nd] != 0) {
        if (mn[nd] < lazy[nd])  mn[nd] = lazy[nd];
        mx[nd] = max(mx[nd], mn[nd]);
        if (st != en) {
            lazy[2*nd] = lazy[nd];
            lazy[2*nd+1] = lazy[nd];
        }
        lazy[nd] = 0;
    }
    if (r < st || en < l)   return;
    
    if (l <= st && en <= r) {
        if (mn[nd] > h) return;
        else if (mn[nd] == h) {
            if (mx[nd] == h) {
                len += en-st+1;
                return;
            } else {
                update(st, (st+en)/2, 2*nd, h, l, r);
                update((st+en)/2+1, en, 2*nd+1, h, l, r);
                upd(nd);
                return;
            }
        }
        else {
            if (mx[nd] <= h) {
                len += en-st+1;
                mn[nd] = h;
                mx[nd] = h;
                if (st != en) { 
                    lazy[2*nd] = h;
                    lazy[2*nd+1] = h;
                }
            } else {
                update(st, (st+en)/2, 2*nd, h, l, r);
                update((st+en)/2+1, en, 2*nd+1, h, l, r);
                upd(nd);
            }
            return;
        }
    }
    update(st, (st+en)/2, 2*nd, h, l, r);
    update((st+en)/2+1, en, 2*nd+1, h, l, r);
    upd(nd);
}

signed main() {

    IOS;
    int cases;  cin >> cases;

    while (cases--) {
        cin >> m;
        for (int i = 0; i < m; i++) {
            cin >> l[i] >> r[i] >> h[i];
            n = max(n, r[i]);
        }
        n = 1e5+1;
        memset(mx, 0, sizeof mx);
        memset(mn, 0, sizeof mn);
        memset(lazy, 0, sizeof lazy);

        int ans = 0;
        for (int i = 0; i < m; i++) {
            len = 0;
            update(0, n-1, 1, h[i], l[i], r[i]-1);
            ans += len;
        }
        cout << ans << endl;
    }

    return 0;
}
