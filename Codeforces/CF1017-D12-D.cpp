/*
    Author : manu_sy

    Idea : Possible no. of strings 2^n 
        precalculate f(s1,s2) for every string pair of string : 2^n * 2^n * n
        then for every query just search through the precalculated array for all values <= k.
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

const int N = 13;
const int M = 1<<N;
const int INF = 1e9;

/* Template Ends */
int n, m, q, w[N], cnt[M], k, tot;
vector<pair<int, int> > g[M];
string t;

signed main() {

    IOS;
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) cin >> w[i], tot += w[i];
    for (int i = 0; i < m; i++) {
        cin >> t;   int num = 0;    
        for (int i = 0; i < n; i++) if (t[i] == '1')    num |= (1<<i);
        cnt[num]++;
    }
    for (int i = 0; i < (1<<n); i++)
        for (int j = i+1; j < (1<<n); j++) {
            int val = 0;
            for (int bit = 0; bit < n; bit++) if (((i>>bit)&1) == ((j>>bit)&1)) val += w[bit];
            
            if (val > 100)  continue;
            if (cnt[i] > 0) g[j].push_back(make_pair(val, cnt[i]));
            if (cnt[j] > 0) g[i].push_back(make_pair(val, cnt[j]));
        }

    for (int i = 0; i < (1<<n); i++) sort(g[i].begin(), g[i].end());

    for (int i = 0; i < (1<<n); i++) {
        for (int j = 1; j < g[i].size(); j++) {
            g[i][j].second += g[i][j-1].second;
        }
    }

    while (q--) {
        cin >> t >> k;   int num = 0;
        for (int i = 0; i < n; i++) if (t[i] == '1') num |= (1<<i);

        int pos = upper_bound(g[num].begin(), g[num].end(), make_pair(k, INF)) - g[num].begin() - 1;
        int ans = 0;
        if (pos != -1)  ans += g[num][pos].second;

        if (tot <= k)   ans += cnt[num];
        cout << ans << endl;
    }

    return 0;
}
