/*
    Author : Shashank Yadav
    
    Idea : Store range square sum and range sum in a node. So easy lazy updations. Eg:
        - (a+t)^2 + (b+t)^2 + (c+t)^2 = 
                    a^2 + b^2 + c^2 + 3*t^2 + 2*(a+b+c)*t
        - Above is for range updation by t
*/
#include <bits/stdc++.h>
using namespace std;

#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'

typedef long long ll;

const int N = 4e5+7;

struct leaf {
    ll sum, sq, l1, l2;
    bool lazy1, lazy2;
    leaf(ll sum = 0, ll sq = 0, bool lazy1 = false, bool lazy2 = false, ll l1 = 0, ll l2 = 0): sum(sum), sq(sq), lazy1(lazy1), lazy2(lazy2) {}
};
ll sq(ll x) {
    return x*x;
}
int n, q, a[N];
leaf tree[N];

struct segTree {
    vector<int> v;
public:
    segTree(int a[], int n) {
        v = vector<int>(a, a+n);
        build(0, n-1, 1);
    }
    leaf combine(leaf a, leaf b) {
        return leaf(a.sum+b.sum, a.sq+b.sq);
    }
    void build(int start, int end, int node) {
        if (start == end) {
            tree[node].sum = v[start];
            tree[node].sq = sq(v[start]);
            return;
        }
        int mid = (start+end)/2;
        build(start, mid, 2*node);
        build(mid+1, end, 2*node+1);
        tree[node] = combine(tree[2*node], tree[2*node+1]);
    }
    void make_lazy(int id, int node, int val) {
        if (id == 1) {
            tree[node].lazy2 = false, tree[node].lazy1 = true;
            tree[node].l1 += val;
        }
        else {
            tree[node].lazy1 = false, tree[node].lazy2 = true, tree[node].l1 = 0;
            tree[node].l2 = val;
        }
    }
    void lazify(int start, int end, int node) {
        assert(!(tree[node].lazy1 && tree[node].lazy2));

        if (tree[node].lazy1) {
            ll len = end-start+1;
            tree[node].sq += len*sq(tree[node].l1) + 2*tree[node].sum*tree[node].l1;
            tree[node].sum += len*tree[node].l1;
            tree[node].lazy1 = false;
            
            if (start != end) {
                make_lazy(1, 2*node, tree[node].l1);
                make_lazy(1, 2*node+1, tree[node].l1);
            }
            tree[node].l1 = 0;
        }
        else if (tree[node].lazy2) {
            int len = end-start+1;
            tree[node].sq = len*sq(tree[node].l2);
            tree[node].sum = len*tree[node].l2;
            tree[node].lazy2 = false;

            if (start != end) {
                make_lazy(2, 2*node, tree[node].l2);
                make_lazy(2, 2*node+1, tree[node].l2);
            }
            tree[node].l2 = 0;
        }
    }
    void upd1(int start, int end, int node, int l, int r, int x) {
        lazify(start, end, node);
        if (start > r || end < l)   return;
        
        if (l <= start && end <= r) {
            tree[node].lazy1 = true, tree[node].l1 = x;
            lazify(start, end, node);
            return;
        }
        int mid = (start+end)/2;
        upd1(start, mid, 2*node, l, r, x);
        upd1(mid+1, end, 2*node+1, l, r, x);
        tree[node] = combine(tree[2*node], tree[2*node+1]);
    }
    void upd2(int start, int end, int node, int l, int r, int x) {
        lazify(start, end, node);
        if (start > r || end < l)   return;

        if (l <= start && end <= r) {
            tree[node].lazy2 = true, tree[node].l2 = x;
            lazify(start, end, node);
            return;
        }
        int mid = (start+end)/2;
        upd2(start, mid, 2*node, l, r, x);
        upd2(mid+1, end, 2*node+1, l, r, x);
        tree[node] = combine(tree[2*node], tree[2*node+1]);
    }
    int query(int start, int end, int node, int l, int r) {
        lazify(start, end, node);
        if (start > r || end < l)   return 0;
        if (l <= start && end <= r) return tree[node].sq;

        int mid = (start+end)/2;
        int p1 = query(start, mid, 2*node, l, r);
        int p2 = query(mid+1, end, 2*node+1, l, r);
        return p1+p2;
    }
};


void solve() {

    cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> a[i];

    segTree s(a, n);
    int type, l, r, x;
    while(q--) {
        cin >> type;
        if (type == 2) {
            cin >> l >> r;  l--, r--;
            cout << s.query(0, n-1, 1, l, r) << endl;
        }
        else if (type == 1) {
            cin >> l >> r >> x; l--, r--;
            s.upd1(0, n-1, 1, l, r, x);
        }
        else {
            cin >> l >> r >> x; l--, r--;
            s.upd2(0, n-1, 1, l, r, x);
        }
    }
}

signed main() {

    IOS;
    int t;  cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        cout << "Case " << tc << ":" << endl;
        solve();
    }

    return 0;
}
