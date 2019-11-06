/*
    Author : manu_sy
    
    Idea : using bit. 
           Just maintaing 2 pointer for current subarray and the current inversion count and keep updating it.
*/
#include <bits/stdc++.h>
using namespace std;
 
/** Template Begins **/
#define IOS         ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl        '\n'
/** Template Ends **/
 
const int N = 5e5+7;
int n, p, a[N];
vector<int> v;
 
struct BIT {
    vector<int> bit;
    int n;
    BIT (int n) : n(n + 1) {
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
        if (r < l)  return 0;
        return sum(r) - sum(l-1);
    }
};
 
signed main() {
 
    IOS;
    cin >> n >> p;
    v.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i], v[i] = a[i];
    
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
 
    map<int, int> m;
    for (int i = 0; i < v.size(); i++)  m[v[i]] = i;
 
    BIT bt(v.size() + 2);
    
    long long inv = 0, st = 0, ans = -1;
 
    for (int i = 0, j = 0; i + p - 1 < n; i++)
    {
        while (j-i < p && j < n)
        {
            inv += bt.sum(m[a[j]]+1, v.size());
            bt.add(m[a[j]], 1);
            j++;
        }
 
        if (inv > ans)  ans = inv, st = i;
 
        inv -= bt.sum(0, m[a[i]]-1);
        bt.add(m[a[i]], -1);
    }
    cout << st + 1 << " " << ans << endl;
 
    return 0;
} 
