/*
    Author : manu_sy
    
    Idea : Just iterate over 1 till m and maintain a list of possible submasks found till i-1 and cnt of sauce in them.
        - Now we can add all those masks (combinations of sauce) to current i s.t mask & cur = 0
        - So find those and update if need

    Complexity of this solution is O(m*(2^n)) but optimized so it passes since all masks arent reached for all i

    Better Solution :
        https://github.com/magdy-hasan/competitive-programming/blob/master/Other/ZOJ%20Get%20Sauce.cpp
*/
#include <bits/stdc++.h>
using namespace std;

/* Template Begins */

#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'

// Debug //
#define trace(x)                 cerr << #x << ": " << x << endl;
#define trace2(x, y)             cerr << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)          cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl;
#define trace4(a, b, c, d)       cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << endl;

const int N = 17;
const int MM = (1<<N)+5;

/* Template Ends */
int n, m, cnt[MM];


signed main() {

    IOS;
    while(cin >> n >> m) {

        int ans = 0;
        //memset(cnt, 0, sizeof cnt);
        for (int i = 0; i < (1<<n); i++) cnt[i] = 0;

        vector<int> poss;
        poss.push_back(0);

        while (m--) {
            int k;  cin >> k;
            int cur = 0;
            while (k--) {
                int x;  cin >> x;
                cur |= (1<<(x-1));
            }
            vector<int> temp;
            for (auto mask : poss) {

                if ((mask&cur) == 0 && cnt[mask|cur] < cnt[mask]+1) {
                    if (cnt[mask|cur] == 0) temp.push_back((mask|cur));
                    cnt[mask|cur] = cnt[mask]+1;
                    ans = max(ans, cnt[mask|cur]);
                    //trace4(cur, mask, (mask|cur), cnt[mask|cur]);
                }   
            }
            poss.insert(poss.end(), temp.begin(), temp.end());
        }   
        cout << ans << endl;
    }

    return 0;
}
