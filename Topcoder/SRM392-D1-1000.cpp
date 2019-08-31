/*
    Author : manu_sy
    
    Idea : We are give an n-digit no. num and need to find smallest no. greater than num that is equidigit
    
    	- Let d be the frequency of each digit in our answer
		- Notice d is a divisor of n and digits used : dcnt = n/d
		- Since the values of d for a particular n are very limited we can find answer for each particular d
	  
	   		To find answer for d : we have to select dcnt digits from 0..9. Here also brute force over all search space
			So do it to get all the possible digits in our no.
			and then try to create our answer using these digits.
			Take min of all possible answers.
		
		Time Complexity : O( div(n) * ncr(10,dnct) * n * n )
		n : no. of digits in our no.
		div(n) : no. of divisors of n
		dcnt : No. of distinct digits to calculate answer
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
#define FOR(i,a,b)   for(int i=a;i<=b;i++)
#define LP(i,a)      for(int i=0;i< a;i++)
#define cerr 		 cout

/* Debug */
template<class L, class R> ostream &operator<<(ostream &os, pair<L,R> P) {
  return os << "(" << P.F << "," << P.S << ")";
} 
template<class T> ostream &operator<<(ostream& os, vector<T> V) {
  os << "["; for (auto vv : V) os << vv << ","; return os << "]";
}
template<class TH> void _dbg(const char *sdbg, TH h){ cerr<<sdbg<<'='<<h<<endl; }
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
  while(*sdbg!=',')cerr<<*sdbg++;
  cerr<<'='<<h<<','; _dbg(sdbg+1, a...);
}

#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)

/* Debug Ends */

ll stolll(string s) {
	
	ll ret = -1;
	try {
		ret = stoll(s);
	} catch (...) {
		ret = LLONG_MAX;
	}
	assert(ret != -1);
	return ret;
}


class EquiDigitNumbers {
public:
	int n;
	string num;
	vector<int> temp;
	int a[10];
	bool taken[20], valid;
	string str, retstr;
	
	void get(int idx, int taken, int dcnt, vector<vi>& digs) {
		if (taken == dcnt) {
			digs.pb(temp);	return;
		}
		if (idx >= 10)	return;
		
		temp.pb(a[idx]);
		get(idx+1, taken+1, dcnt, digs);
		temp.pop_back();
		
		get(idx+1, taken, dcnt, digs);
	}
	void create(int idx, bool greater, vi& dig) {
		if (idx == n) {
			if (stolll(retstr) > stolll(str))
				retstr = str;
            return;
		}
		if (!greater) {
			int pos = -1;
			for (int i = 0; i < dig.size(); i++) 
				if (!taken[i] && dig[i] == num[idx]-'0') {
					taken[i] = true;
					str.pb((char)(dig[i]+'0'));
					create(idx+1, 0, dig);
					str.pop_back();
					taken[i] = false;
					break;
				}
			for (int i = 0; i < dig.size(); i++) {
				if (!taken[i] && dig[i] > num[idx]-'0') {
					taken[i] = true;
					str.pb((char)(dig[i]+'0'));
					create(idx+1, 1, dig);
					str.pop_back();
					taken[i] = false;
					break;	
				}
			}
			return;
		} else {
			for (int i = 0; i < dig.size(); i++)
				if (!taken[i]) {
					taken[i] = true;
					str.pb((char)(dig[i]+'0'));
					create(idx+1, 1, dig);
					return;
				}
		}
	}
	ll solve(int dcnt) {
		vector<vector<int> > digs;
		get(0, 0, dcnt, digs);
		
		ll ret = LLONG_MAX;
		for (auto& v : digs)	sort(all(v)); 
		digs.resize(unique(all(digs))-digs.begin());
		
		for (auto& v : digs) {
			memset(taken, false, sizeof taken);
			valid = true;
			str = "";
			vector<int> temp;
			for (auto i : v)	LP(j,n/dcnt)	temp.pb(i);
			assert(temp.size() == n);
			retstr = to_string(LLONG_MAX);
	
			create(0, 0, temp);		
			ret = min(ret, stolll(retstr));
		}
		return ret;
	}
	
	long long findNext(string nn) {
		
		n = nn.size();
		num = nn;
		vector<int> poss;
		for (int i = 0; i < 10; i++) a[i] = i;
		
		for (int d = 1; d*d <= n; d++) {
			if (n%d == 0) {
				if (d <= 10)	poss.pb(d);
				if (n/d != d && n/d <= 10)	poss.pb(n/d);
			}
		}
		
		ll ans = LLONG_MAX;
		for (auto d : poss) {
			ans = min(ans, solve(d));
		}
		assert(ans != LLONG_MAX);
		return ans;
	}
};

<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
