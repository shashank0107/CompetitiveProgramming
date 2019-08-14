/*
	Author : manu_sy

	Idea :
		- Noitce we can alter formula as h[i] = 2(h[i-1]+1) - h[i-2] 
		- So given h[1] and h[2] we can get all others easily
		- The minimization of h[n] correlates with the minimization of h[2] or infact any other h[i] 
		  such that all the correspoing h[i] are >= 0
		- So we binary search over the possible values for h[2] and find the minimum that is valid
		- And so obtain the corresponding h[n]
*/

#include <bits/stdc++.h>
using namespace std;

#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'

const int N = 1e3+7;
const double EPS = 1e-7;
int n;
double a, h[N];

bool f(double x) {
	fill(h, h+n+1, 0);
	h[1] = a, h[2] = x;
	for (int i = 3; i <= n; i++) {	
		h[i] = 2*(h[i-1]+1) - h[i-2];
		if (h[i] < 0)	return false;
	}
	return true;
}

signed main() {

    IOS;
    cout << fixed << setprecision(2);

    while(cin >> n >> a) {

    	double lo = 0, hi = 1e18, h2 = -1;
    	while(hi-lo > EPS) {
    		double mid = (hi+lo)/2;
    		if (f(mid))	hi = mid;
    		else lo = mid;
    	}
    	if (f(lo))	h2 = lo;
    	else if (f(hi))	h2 = hi;
    	else assert(false);

    	f(h2);
    	cout << h[n] << endl;
    }

    return 0;
}
