/*
	Author : manu_sy

	Idea : Just handle all the dimensions independently.
		- Then handle as explained in :
		https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/SPOJ/SPOJ_IOPC1207.txt
*/
#include <bits/stdc++.h>
using namespace std;

#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'

const int N = 1e5+7;

struct segTree {

	int tree[4*N];
	bool lazy[4*N];
public:
	segTree() {
		memset(tree, 0, sizeof tree);
		memset(lazy, false, sizeof lazy);
	}
	void lazify(int start, int end, int node) {
		if (lazy[node]) {
			tree[node] = end-start+1 - tree[node];
			if (start != end) {
				lazy[2*node] ^= 1;
				lazy[2*node+1] ^= 1;
			}
			lazy[node] = false;
		}
	}
	void update(int start, int end, int node, int l, int r) {
		lazify(start, end, node);
		if (start > r || end < l)	return;
		if (l <= start && end <= r) {
			lazy[node] = 1;
			lazify(start, end, node);
			return;
		}
		int mid = (start+end)/2;
		update(start, mid, 2*node, l, r);
		update(mid+1, end, 2*node+1, l, r);
		tree[node] = tree[2*node] + tree[2*node+1];
	}
	int query(int start, int end, int node, int l, int r) {
		lazify(start, end, node);
		if (start > r || end < l)	return 0;
		if (l <= start && end <= r)	return tree[node];
		int mid = (start+end)/2;
		int p1 = query(start, mid, 2*node, l, r);
		int p2 = query(mid+1, end, 2*node+1, l, r);
		return p1 + p2;
	}
};

int n[3], q, x[3], y[3];

void solve() {
	cin >> n[0] >> n[1] >> n[2] >> q;
	segTree seg[3];

	while(q--) {
		int id, l, r;
		cin >> id;
		if (id != 3) {
			cin >> l >> r;
			seg[id].update(0, n[id]-1, 1, l, r);
		}
		else {
			cin >> x[0] >> x[1] >> x[2] >> y[0] >> y[1] >> y[2];
			int T[3], X[3], NT[3];
			for (int i = 0; i < 3; i++)	
				T[i] = seg[i].query(0, n[i]-1, 1, x[i], y[i]),
				X[i] = y[i]-x[i]+1;
			for (int i = 0; i < 3; i++)	NT[i] = X[i]-T[i];

			long long ans = 1LL*T[0]*T[1]*T[2] + 1LL*T[0]*NT[1]*NT[2] + 
							1LL*NT[0]*T[1]*NT[2] + 1LL*NT[0]*NT[1]*T[2];
			cout << ans << endl;
		}
	}
}

signed main() {

    IOS;
    int t;	cin >> t;
    while(t--)
    	solve();

    return 0;
}
