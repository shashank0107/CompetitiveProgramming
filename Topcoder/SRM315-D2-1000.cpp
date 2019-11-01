/*
    Author : manu_sy
    
    Idea : - Initially cur position is 1
           - Every time just we have to find the mth position in the array starting from position cur
           - This can be find using binary search in BIT in logn*logn 
           - So keep finding next positions in brute force until k is reached.
           Complexity : O(n*logn*logn)
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long    ll;

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

struct BIT {
	vector<int> bit;
	int n;
	BIT(int n): n(n+1) {
		bit.assign(n+1, 0);
		for (int i = 1; i < n; i++) add(i, 1);
		assert(sum(1,n-1) == n-1);
	}
	void add(int idx, int val) {
		for (++idx; idx < n; idx += idx & -idx)
			bit[idx] += val;
	}
	int sum(int idx) {
		int ret = 0;
		for (++idx;	idx > 0; idx -= idx & -idx)
			ret += bit[idx];
		return ret;
	}
	int sum(int l, int r) {
		return sum(r) - sum(l-1);
	}
};

class KidsGame {
public:
	int left, n;
	
	int find(int idx, int dist, BIT& bt) {
		
		dist = ((dist - 1) % left) + 1;
		if (bt.sum(idx, n) < dist)	
			return find(1, dist - bt.sum(idx, n), bt);
		
		int lo = idx, hi = n;
		while (hi - lo > 1) {
			int mid = (hi + lo) / 2;
			if (bt.sum(idx, mid) < dist)	lo = mid;
			else hi = mid;
		}
		if (bt.sum(idx, lo) == dist)	return lo;
		else if (bt.sum(idx, hi) == dist)	return hi;
		else assert(false);
	}
	
	int kthKid(int nn, int m, int k) {
		
		n = nn;
		BIT bt(n+1);
		left = n;
		int cur = 1;
				
		for (int i = 1; i <= n; i++)
		{
			int x = find(cur, m, bt);
			if (x == k)	return i;
			
			bt.add(x, -1);
			left--;
			
			cur = find(x, 1, bt);
		}
				
		assert(false);
		return 0;
	}
};

<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
