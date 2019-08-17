/*
    Author : manu_sy
    Idea :
      - Same as editorial
      https://codeforces.com/blog/entry/45912
*/
#include <bits/stdc++.h>
using namespace std;

#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'
#define F first
#define S second
#define mp make_pair
const int N = 2e5+7;

int n, a[N], b[N];
pair<int, int> tree[4*N];

pair<int, int> combine(pair<int, int> a, pair<int,int> b) {
    return pair<int, int>(max(a.F, b.F), min(a.S, b.S));
}

void build(int s, int e, int nd) {
    if (s == e) {
        tree[nd].F = a[s];
        tree[nd].S = b[s];
        return;
    }
    build(s, (s+e)/2, 2*nd);
    build((s+e)/2+1, e, 2*nd+1);
    tree[nd] = combine(tree[2*nd], tree[2*nd+1]);
}
pair<int, int> query(int s, int e, int nd, int l, int r) {
    if (r < s || e < l) return mp(INT_MIN, INT_MAX);
    if (l <= s && e <= r)   return tree[nd];
    return combine(query(s, (s+e)/2, 2*nd, l, r), query((s+e)/2+1, e, 2*nd+1, l, r));
}
int query(int l, int r) {
    auto p = query(0, n-1, 1, l, r);
    return p.F - p.S;
}

signed main() {

    IOS;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    build(0, n-1, 1);

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int left, right;

        int lo = i, hi = n-1;
        if (a[i] > b[i])    continue;

        while(hi-lo>1) {
            int mid = (hi+lo)/2;
            int p = query(i,mid);
            if (p >= 0) hi = mid;
            else lo = mid;    
        }
        if (query(i,lo) == 0)   left = lo;
        else if (query(i,hi) == 0)  left = hi;
        else continue;

        lo = i, hi = n-1;
        while(hi-lo>1) {
            int mid = (hi+lo)/2;
            int p = query(i,mid);
            if (p <= 0) lo = mid;
            else hi = mid;
        }
        if (query(i,hi) == 0)   right = hi;
        else if (query(i,lo) == 0)  right = lo;
        else continue;

        ans += right-left+1;
    }
    cout << ans << endl;

    return 0;
}
