/*
    Author : manu_sy
    
    I have used 1 in place of 'a' and 2 in place of 'z' for explanation and coding
    Idea : - Just find calc(pos, cntOnes, cur) : count of no.s of length pos with cntOnes '1' and char at pos = cur
           - Now go from m+n till 1 filling making the ans.
               if (calc(pos,cntOnes,1) >= rnk)  insert 'a' in ans
               else insert 'z' in ans, rnk -= calc(pos,cntOnes,1);
               
    Another Sol :
    https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/TopCoder/SRM428-D2-1000.txt
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


class TheDictionary {
public:
    ll hell;
    
    ll dp[203][203][3];
    string ans;
    bool error;
    
    ll calc(int tot, int cntOne, int p) {
        
        ll &ret = dp[tot][cntOne][p];
        if (ret != -1)  return ret;
        
        if ( (cntOne == tot && p == 1) || (cntOne == 0 && p == 2) ) { 
        	ret = 1;
        	return ret;
        }
        if ( (cntOne == tot && p == 2) || cntOne > tot || cntOne < 0 || (cntOne == 0 && p == 1) ){
        	ret = 0;
        	return ret;
        }
        if (p == 1) cntOne--;
        ret = calc(tot-1, cntOne, 1) + calc(tot-1, cntOne, 2);
        if (ret > hell) ret = hell;
        return ret;
    } 
    void go(int pos, int cntOne, int rnk) {
        
        if (pos == 1) {
            if (cntOne == 1)	ans += "a";
            else ans += "z";
            return;
        }
        if (calc(pos, cntOne, 1) >= rnk) {
            ans += "a";
            go(pos-1, cntOne-1, rnk);
        } else {
            ans += "z";
            rnk -= calc(pos, cntOne, 1);
            go(pos-1, cntOne, rnk);
        }
    }
    string find(int n, int m, int k) {
        memset(dp, -1, sizeof dp);
        ans = "";
        error = false;
        hell = 1e15;
        
        //trace2(calc(m+n,n,1), calc(m+n,n,2));
        if (calc(m+n, n, 1) + calc(m+n, n, 2) < k)  return "";
        go(m+n, n, k);
        if (error)  return "";
        return ans;
    }
};
