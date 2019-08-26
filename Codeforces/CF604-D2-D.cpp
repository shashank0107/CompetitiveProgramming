/*
    Author : manu_sy
    
    Idea : Just union_set all x and k*x % p since they depend on each other. Now each set can take p values except set of 0
          since f(0) = k*f(0) for k != 0.
          Handle base cases k = 0, k = 1
*/
#include <bits/stdc++.h>
using namespace std;

/* Template Begins */
#define int long long
#define ll long long
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'

const int N = 1e6+7;
const int hell = 1e9+7;

/* Template Ends */
int p, k;
bool done[N];

int parent[N], size[N];
void make_set(int v) {
    parent[v] = v;
    size[v] = 1;
}
int find_set(int u) {
    if (u == parent[u]) return u;
    return parent[u] = find_set(parent[u]);
}
void union_sets(int u, int v) {
    u = find_set(u);
    v = find_set(v);
    if (u != v) {
        if (size[u] < size[v])  swap(u,v);
        parent[v] = u;
        size[u] += size[v];
    }
}
ll power(ll x, ll y, ll p){ ll res = 1;x = x % p;while (y > 0){ if (y & 1) res = (res*x) % p;y = y>>1;x = (x*x) % p;} return res; } 

signed main() {

    IOS;
    cin >> p >> k;
    for (int i = 0; i < p; i++) make_set(i);

    if (k == 0) {
        cout << power(p, p-1, hell);
        return 0;
    } else if (k == 1) {
        cout << power(p, p, hell);
        return 0;
    }

    for (int i = 0; i < p; i++) {
        union_sets(i, (i*k*1LL)%p);
    }

    long long ans = 1;
    for (int i = 0; i < p; i++) {
        int v = find_set(i);
        if (!done[v]) {
            done[v] = true;
            if (i != 0) {
                ans = (ans*p)%hell;
            }
        }
    }
    cout << ans << endl;

    return 0;
}
