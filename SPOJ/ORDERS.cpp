/*
    Author : manu_sy
    
    Idea : 
      - The position of each element only depends on the values to its right. So iterate from right to left
      - insert 1 to n in RBT.
      - FOR(i,n-1,0):
        current elements position is (RBT.size()-a[i]-1)th in the RBT. 
        Remove this from RBT.
        
     Other Solutions :
     https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/SPOJ/SPOJ_ORDERS.txt
*/
#include <bits/stdc++.h>
using namespace std;

/* Template Begins */

#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'

/* Policy based DS */
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;
/* PBDS ends */

const int N = 2e5+7;

/* Template Ends */
int n, a[N], rnk[N];


signed main() {

    IOS;
    int cases;  cin >> cases;
    while(cases--) {
        
        cin >> n;
        for (int i = 0; i < n; i++) cin >> a[i];
        
        ordered_set s;
        for (int i = 1; i <= n; i++) s.insert(i);
        
        for (int i = n-1; i >= 0; i--) {
            
            int pos = s.size()-a[i]-1;
            
            int val = *s.find_by_order(pos);
            s.erase(val);
            
            rnk[i] = val;
        }
        for (int i = 0; i < n; i++) cout << rnk[i] << " ";  cout << endl;
    }
    
    return 0;
}
