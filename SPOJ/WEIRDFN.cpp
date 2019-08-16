/*
	Author : manu_sy

	Idea : Similar to 
		https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/SPOJ/SPOJ_WEIRDFN.txt
*/

#include <bits/stdc++.h>
using namespace std;

#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'

const int N = 2e5+7;
const int hell = 1e9+7;

struct mySet {
	priority_queue<int> q1;
	priority_queue<int, vector<int>, greater<int> > q2;
public:
	void insert(int x) {
		if (q1.empty()) {	q1.push(x);	return;	}
		if (q2.empty()) {	
			if (q1.top() <= x)	q2.push(x);
			else {
				q2.push(q1.top());	q1.pop();
				q1.push(x);
			}
			return;
		}
		if (x > q1.top()) q2.push(x);
		else q1.push(x);

		if (q1.size() < q2.size()) {
			q1.push(q2.top());	q2.pop();
		}
		if (q1.size() > q2.size()+1) {
			q2.push(q1.top());	q1.pop();
		}
		//assert(q1.size()-q2.size() >= 0 && q1.size()-q2.size() <= 1);
	}
	int get_median() {
		return q1.top();
	}
};

int n, a, b, c, f[N];

void solve() {
	cin >> a >> b >> c >> n;

	mySet s;
	s.insert(1);

	long long ans = 1;
	f[1] = 1;
	for (int i = 2; i <= n; i++) {
		f[i] = ( 1LL*a*s.get_median() + 1LL*b*i + c )%hell;
		ans += f[i];

		//cerr << s.get_median() << " " << f[i] << endl;
		s.insert(f[i]);
	}
	cout << ans << endl;
}

signed main() {

    IOS;
	int t;	cin >> t;
	while(t--)
		solve();    

    return 0;
}
