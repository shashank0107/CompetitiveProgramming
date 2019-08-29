/*
  Author : manu_sy
  
  Idea : 
    The answer is unbounded if there are atleast two cycles that share a common vertex.
    Reason : - let length of the two cylces be p1 & p2 and their lcm(p1,p2) be L. 
             - So to cover a length of L we have 2 choices atleast,
               now for 2*L length - 2*2 choices, ...
             - For very big length - 2^(L/2) ~ 2^L : Exponential
    
    So just start dfs from all vertices and check if we reach back to it more than once.
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long    ll;

#define pb           push_back
#define F            first
#define S            second
#define mp           make_pair
#define all(a)       (a).begin(),(a).end()
#define FOR(i,a,b)   for(int i=a;i<=b;i++)
#define LP(i,a)      for(int i=0;i< a;i++)

#define trace(x)                 cout << #x << ": " << x << endl;
#define trace2(x, y)             cout << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)          cout << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl;


class BigOEasy {
public:
	vector<string> g;
	bool valid;
	int n, color[55], cnt[55];
	
	void dfs(int v) {
		if (!valid)	return;
		color[v] = 1;	// now in stack
		
		LP(nb,n) if (g[v][nb] == 'Y') {
			if (color[nb] == 0)	dfs(nb);
			else if (color[nb] == 1) {
				cnt[nb]++;
				if (cnt[nb] > 1) {
					valid = false;
					break;
				}
			} 
		}
		color[v] = 2;
	}
	
	string isBounded(vector <string> graph) {
		g = graph;
		valid = true; n = g.size();	memset(color, 0, sizeof color), memset(cnt, 0, sizeof cnt);
		
		bool found = false;
		LP(i,n) {
			if (found)	break;
			memset(color, 0, sizeof color);
			memset(cnt, 0, sizeof cnt);
			dfs(i);
			if (!valid)	found = true;
		}
		if (!found)	return "Bounded";
		else return "Unbounded";
	}
};

<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
