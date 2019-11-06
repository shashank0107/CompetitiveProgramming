/*
    Author : manu_sy
    
    Idea : Sort points and maintaing a bit for all the y values
           Then points dominated by current can be easily found
*/
#include <bits/stdc++.h>
using namespace std;
 
/** Template Begins **/
#define IOS         ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl        '\n'
#define F           first
#define S           second
#define mp          make_pair
/** Template Ends **/
 
const int N = 1e5+7;
 
int n, k;
pair<int, int> pt[N];
 
struct BIT {
    vector<int> bit;
    int n;
 
    BIT(int n): n(n+1) {
        bit.assign(n+1, 0);
    }
    void add(int idx, int val) {
        for (++idx; idx < n; idx += idx & -idx)
            bit[idx] += val;
    }
    int sum(int idx) {
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }
    int sum(int l, int r) {
        return sum(r) - sum(l-1);
    }
};
 
signed main() {
 
    IOS;
    int t;  cin >> t;
    while (t--)
    {
        cin >> n >> k;
        
        set<int> sx, sy;
 
        for (int i = 0; i < n; i++) 
        {
            cin >> pt[i].F >> pt[i].S;
            sx.insert(pt[i].F);
            sy.insert(pt[i].S);
        }
 
        map<int, int> mx, my;
        int id = 0;
        for (auto i : sx)   mx[i] = id++;
        id = 0;
        for (auto i : sy)   my[i] = id++;
 
        sort(pt, pt + n);
 
        long long ans = 0;
        BIT bt(id+1);
        for (int i = 0; i < n; )
        {
            int j = i + 1;
            while (j < n && pt[i] == pt[j]) j++;
 
            int dom = bt.sum(0, my[pt[i].S]);
            dom += (j - i) - 1;
 
            int n_dom = n - dom - 1;
            if (abs(dom - n_dom) >= k)    ans += (j-i);
 
            bt.add(my[pt[i].S], 1);
            i = j;
        }
        cout << ans << endl;
    }
 
    return 0;
} 
