/*
	Author : manu_sy

	Idea :
		- Any RBS (Regular Bracket Sequence) can be represented as :
			( RBS RBS RBS ..)

		- So we'll use stack (containing two types of elements : '(' or RBS block ) to process our answer :
			- if a '(' just push it in stack
			- if a ')' comes then we'll find the length and height of the current RBS :
				keep popping the RBS blocks from the stack until you encounter a '('
				and keep updating the length and height of current block as well as the area 
				of children RBS
			- finally calculate the answer for current RBS and push this block onto stack
		- Area for RBS blocks at odd depth is added to the answer
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'

struct item {
	int type;
	int area, len, ht;
	item(int type = 0, int area = 0, int len = 0, int ht = 0): type(type), area(area), len(len), ht(ht) {}
};

void solve() {

	string s;
	cin >> s;

	stack<item> st;
	long long ans = 0;
	
	int dep = 0;
	for (auto i : s) {
		if (i == '(')	st.push(item(0)), dep++;
		else {

			int length = 1;
			int height = 1;
			int cha = 0;

			while(st.top().type) {
				auto p = st.top();	st.pop();
				length += p.len;
				height = max(p.ht+1, height);
				cha += p.area;
			}

			long long cur_area = length*height - cha;
			// cerr << "area : " << cur_area << " len : " << length << " height : " << height << endl;

			if (dep&1) {
				ans += cur_area;
			}
			assert(st.top().type == 0);
			st.pop();

			st.push(item(true, length*height, length+1, height));
			dep--;
		}
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
