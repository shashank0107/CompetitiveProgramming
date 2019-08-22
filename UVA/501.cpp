/*
    Author : manu_sy
    Idea : Just use a red black tree (C++ Policy Based DS) to perform ADD and GET in O(logn)
        - To handle duplicates insert {a[i], cnt++} where presence of cnt makes all elements unique
*/
#include <bits/stdc++.h>
using namespace std;

/* Template Begins */

#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'

const int N = 3e4+7;

/* Policy based DS */

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<
pair<int,int>,
null_type,
less<pair<int,int> >,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

/* PBDS ends */

/* Template Ends */

int n, m, a[N], u[N];

signed main() {

    IOS;
    int t;  cin >> t;

    while(t--) {

        cin >> m >> n;
        for (int i = 0; i < m; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> u[i];

        ordered_set s;
        int c = 0;
        for (int i = 0, j = 0; i < n; i++) {

            while(j < u[i]) {
                s.insert({a[j++],c++});
            }
            cout << (*s.find_by_order(i)).first << endl;
        }
        if (t != 0) cout << endl;
    }    
    
    return 0;
}
