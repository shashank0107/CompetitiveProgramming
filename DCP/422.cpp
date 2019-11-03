/*
    Author : manu_sy
    
    Idea : Just do coordinate compression and use BIT.
          - When adding a[i] for coordinate compression, add a[i] / 2 also. Then we can correctly answer queries using BIT
*/
#include <bits/stdc++.h>
using namespace std;

/** Template Begins **/
#define IOS         ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl        '\n'
#define pb          push_back
/** Template Ends **/

const int N = 1e5+7;

int n;
long long a[N];

struct BIT {
    vector<int> bit;
    int n;

    BIT (int n): n(n+1) {
        bit.assign(n+1, 0);
    }
    void add (int idx, int val) {
        for (++idx; idx < n; idx += idx & -idx)
            bit[idx] += val;
    }
    int sum (int idx) {
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }
    int sum (int l, int r) {
        return sum(r) - sum(l-1);
    }
};

signed main() {

    IOS;
    int t;  cin >> t;
    while (t--)
    {
        cin >> n;
        vector<long long> v;
        for (int i = 0; i < n; i++) cin >> a[i], v.pb(a[i]), v.pb(a[i]/2);

        sort(v.begin(), v.end());
        v.resize(unique(v.begin(), v.end()) - v.begin());

        map<long long, int> mp;
        for (int i = 0; i < v.size(); i++)  mp[v[i]] = i;

        int nn = v.size();
        BIT bt(nn+1);

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            int idx = mp[a[i]/2];
            int cnt = bt.sum(0, idx);
            ans += cnt;

            bt.add(mp[a[i]], 1);
        }

        cout << ans << endl;
    }


    return 0;
}
