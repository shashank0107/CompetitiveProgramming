/*
    Author : manu_sy
    Idea : Same as editorial - https://www.topcoder.com/tc?module=Static&d1=match_editorials&d2=srm424
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long    ll;
typedef pair<ll, ll> PII;

#define pb           push_back
#define F            first
#define S            second
#define mp           make_pair
#define all(a)       (a).begin(),(a).end()
#define fr(i,a,b)    for(int i=a;i<=b;i++)
#define lp(i,a)      for(int i=0;i< a;i++)

#define trace(x)                 cout << #x << ": " << x << endl;
#define trace2(x, y)             cout << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)          cout << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl;

const ll hell = 1e9 + 7;
const int N = 2e5 + 7;

ll a[N];

struct BIT {
	vector<ll> bit1, bit2;
	int n;
	BIT (int n): n(n + 1) {
		bit1.assign(n + 1, 0);
		bit2.assign(n + 1, 0);
	}
	void add(int idx, ll val) {
		for (++idx; idx < n; idx += idx & -idx)
			bit1[idx] = (val + bit1[idx]) % hell, bit2[idx]++;
	}
	PII sum(ll idx) {
		PII ret = mp(0, 0);
		for (++idx; idx > 0; idx -= idx & -idx)
			ret.F = (ret.F + bit1[idx]) % hell, ret.S += bit2[idx];
		return ret;
	}
	PII sum(ll l, ll r) {
		PII R = sum(r);
		PII L = sum(l - 1);
		return mp((R.F - L.F + hell)%hell, R.S - L.S);
	}
};

class ProductOfPrices {
public:
	int product(ll n, ll L, ll X0, ll A, ll B) {
		
		BIT bt(n + 5);
		a[0] = X0 % L;
		vector<ll> v(1, a[0]);
		for (ll i = 1; i < n; i++)
		{	
			a[i] = (((a[i - 1]%L) * (A%L))%L + B%L)%L;
			v.pb(a[i]);
		}
		sort(all(v));
		v.resize(unique(all(v)) - v.begin());
		map<ll, ll> mx;
		for (ll i = 0; i < n; i++) mx[v[i]] = i;
		
		ll ans = 1;
		for (ll i = 0; i < n; i++)
		{
			PII lo = bt.sum(0, mx[a[i]]);
			PII hi = bt.sum(mx[a[i]] + 1, n);
			
			ll cp = (((lo.S * a[i]) % hell) - lo.F + hi.F - ((hi.S * a[i]) % hell) + 3LL * hell) % hell;
			if (i) ans = (ans * cp) % hell;
		
			bt.add(mx[a[i]], a[i]);
		}
		return ans;
	}
};

<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
