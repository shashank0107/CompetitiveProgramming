/*
    Author : manu_sy
    Idea : Similar to 
        - https://github.com/abdullaAshraf/Problem-Solving/blob/master/SPOJ/GSS4.cpp
*/
#include <bits/stdc++.h>
using namespace std;

/* Template Begins */
#define int ll
typedef long long ll;

#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'

// Debug //
#define trace(x)                 cerr << #x << ": " << x << endl;
#define trace2(x, y)             cerr << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)          cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl;
#define trace4(a, b, c, d)       cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << endl;

const int N = 1e5+7;

/* Template Ends */
int n, m;
ll a[N];
int tree[4*N], sum[4*N];

void calc(int nd) {
    tree[nd] = tree[2*nd] + tree[2*nd+1];
    sum[nd] = sum[2*nd] + sum[2*nd+1]; 
}

void build(int st, int en, int node) {
    if (st == en) {
        tree[node] = 64;
        sum[node] = a[st];
        return;
    }
    build(st, (st+en)/2, 2*node);
    build((st+en)/2+1, en, 2*node+1);
    calc(node);
}
void update(int st, int en, int nd, int l, int r) {
    if (st > r || en < l)   return;
    if (tree[nd] == 0)  return;
    if (st == en) {
        a[st] = sqrt(a[st]);
        sum[nd] = a[st];
        if (a[st] == 1) tree[nd] = 0;  
        else tree[nd]--;
        assert(tree[nd] >= 0);
        return;
    }
    int mid = (st+en)/2;
    update(st, mid, 2*nd, l, r);
    update(mid+1, en, 2*nd+1, l, r);
    //trace3(st, en, sum[nd]);
    calc(nd);
}
ll query(int st, int en, int nd, int l, int r) {
    if (st > r || en < l)   return 0;
    if (l <= st && en <= r) return sum[nd];
    ll p1 = query(st, (st+en)/2, 2*nd, l, r);
    ll p2 = query((st+en)/2+1, en, 2*nd+1, l, r);
    return p1+p2;
}

signed main() {

    IOS;
    
    int tc = 1;
    while (cin >> n) {
        assert(n > 0);
        for (int i = 0; i < n; i++) cin >> a[i];

        build(0, n-1, 1);
        
        cin >> m;
        cout << "Case #" << tc++ << ":" << endl;
        while (m--) {
            int t, l, r;    cin >> t >> l >> r;
            l--, r--;

            if (l > r)  swap(l,r);
            if (t == 0) {
                update(0, n-1, 1, l, r);
            } else {
                cout << query(0, n-1, 1, l, r) << endl;
            }
        }
        cout << endl;
    }

    return 0;
}
