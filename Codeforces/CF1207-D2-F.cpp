/*
    Author : manu_sy
    
    Idea : Same as editorial 
      https://codeforces.com/blog/entry/69314
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long    ll;
typedef vector<int>  vi;

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


class BerryPacker {
public:
	double bestPacking(vector <int> first, vector <int> period, int b) {
		
		int m = first.size();
		int bs = 1<<m;
		vi seen(m, 0), cnt(bs, 0);
		vector<double> val(bs,0), profit(m,0);
		
		double ret = 0;
		for (int n = 0; n < b; n++) {
			
			//trace(n);
			int mask = 0;
			for (int bx = 0; bx < m; bx++) {
				if (n >= first[bx] && (n-first[bx])%period[bx] == 0) 
					seen[bx]++, mask |= (1<<bx);
				//trace2(bx, seen[bx]);
			}
		 	cnt[mask]++;
		  	
		  	if (n+1 >= (b+8)/9) {
		  		double ans = 0;
		  		for (int i = 0; i < m; i++) {	
		  			if (seen[i] > 0)	profit[i] = (((n+1)*1.0)/seen[i])/m;
		  			else profit[i] = 0;
		  			//trace2(i, profit[i]);
		  		}
		  		vector<pair<double, int> > v;		// contains profit of each type of box and the respective cnt
		  		for (int i = 0; i < bs; i++) {
		  			val[i] = 0;
		  			for (int bit = 0; bit < m; bit++) if ((i>>bit)&1) {
		  				val[i] += profit[bit];
		  			}
		  			v.pb(mp(val[i], cnt[i]));
		  			//trace3(i, val[i], cnt[i]);
		  			ans += cnt[i]*val[i];			// each box contains 1 berry now.
		  		}
		  		sort(v.begin(), v.end());	reverse(all(v));
		  		
		  		int remain = b-(n+1);
		  		for (auto b : v) if (remain > 0) {
		  			int have = b.S*8;
		  			int take = min(remain, have);
		  			ans += take*b.F;
		  			remain -= take;
		  		}
		  		assert(remain == 0);
		  		//trace(ans);
		  		ret = max(ans, ret);	
		  	}
		}    
		return ret;
	}
};

<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
