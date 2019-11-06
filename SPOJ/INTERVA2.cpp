/*
    Author : manu_sy
    
    Idea : Just sort the points in increasing l and if l is same then decreasing r
          - Now as you traverse the intervals, keep storing r in BIT
          - For current interval just need to count sum(r, INF) in BIT
          - Handle equal intervals
*/
#include <bits/stdc++.h>
using namespace std;
 
/** Template Begins **/
typedef pair<int, int>  PII;
 
#define IOS         ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl        '\n'
#define mp          make_pair
#define F           first
#define S           second
/** Template Ends **/

const int N = 2e5+7;

int n, ans[N];
pair<PII, int> p[N];
 
struct BIT {
    vector<int> bit;
    int n;
 
    BIT(int n) : n(n+1) {
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
bool comp(const pair<PII, int>& a, const pair<PII, int>& b) {
    return a.F.F < b.F.F || (a.F.F == b.F.F && a.F.S > b.F.S);
}
 
signed main() {
 
    IOS;
    while (cin >> n)
    {
        set<int> sy;
        for (int i = 0; i < n; i++) 
        {
            cin >> p[i].F.F >> p[i].F.S, p[i].S = i;
            sy.insert(p[i].F.S);
        }
        sort(p, p + n, comp);
        
        map<int, int> m;
        int id = 0;
        for (auto i : sy)   m[i] = id++;
 
        BIT bt(id+2);
 
        for (int i = 0; i < n; )
        {
            int cur_ans = bt.sum(m[p[i].F.S], id);
            ans[p[i].S] = cur_ans;
 
            int j = i + 1;
            while (j < n && p[j].F == p[i].F)   ans[p[j++].S] = cur_ans;
 
            bt.add(m[p[i].F.S], j-i);
            i = j;
        }
 
        for (int i = 0; i < n; i++) {
            if (i)  cout << " ";    cout << ans[i];
        } cout << endl;
    }
 
    return 0;
}
