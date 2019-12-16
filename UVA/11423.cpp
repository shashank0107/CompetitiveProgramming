/*
    Author : manu_sy

    Idea : Maintain a time of previous visit prv[i] for each query item.
          - If the number of distinct elements between time prv[i] + 1 till now is
            greater than or equal to the cache size then there will be a cache miss
          - Use a bit to find no. of distinct items b/w two intervals
*/
#include <bits/stdc++.h>
using namespace std;

/** Template Begins **/

typedef long long        ll;
typedef pair<int,int>    PII;

#define IOS         ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl        '\n'

const int N = 30+2;
const int MXN = (1 << 24) + 5;

/** Template Ends **/

int n, sz[N], miss[N], now, prv[MXN];
string q;
int bit[MXN];

struct BIT{
    int n;
    BIT(int sz):n(sz + 1) {} 
    void add(int idx, int val) {
        for (++idx; idx < n; idx += idx & -idx)
            bit[idx] += val;
    }
    int query(int idx) {
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
} bt(MXN-3);

void query(int x)
{
    if (prv[x])
    {
        int distinct = bt.query(prv[x] + 1, now);
        for (int i = 0; i < n; i++)
        {
            if (sz[i] > distinct)   break;
            miss[i]++;
        }
        bt.add(prv[x], -1);
    }
    else
    {
        for (int i = 0; i < n; i++) miss[i]++;
    }
    bt.add(prv[x] = ++now, 1);
}

signed main() {

    IOS;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> sz[i];

    while (cin >> q)
    {
        if (q == "RANGE")
        {
            int b, y, k;    cin >> b >> y >> k;
            for (int j = 0; j < k; j++) query(b + j * y);
        }
        else if (q == "ADDR")
        {
            int x;  cin >> x;
            query(x);
        }
        else if (q == "STAT")
        {
            for (int i = 0; i < n; i++) {
                if (i)  cout << " ";    cout << miss[i];
                miss[i] = 0;
            } cout << endl;
        }
        else if (q == "END")
        {
            break;
        }
    }
    return 0;
}
