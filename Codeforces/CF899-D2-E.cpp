/*
    Author : manu_sy

    Idea : Just make a priority queue where you insert the segments with 
        their length and start and end.
        - Remove top. Adjust its neighbours if need be
*/
#include <bits/stdc++.h>
using namespace std;

#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'
#define mp make_pair
#define F first
#define S second

typedef pair<int, int> PII;
typedef pair<int, PII> PIII; 

const int N = 2e5+7;

// Debug //
#define trace(x)                 cerr << #x << ": " << x << endl;
#define trace2(x, y)             cerr << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)          cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl;
#define trace4(a, b, c, d)       cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << endl;

set<PIII> s; 
int n, a[N];

bool valid[N];

signed main() {

    IOS;
    map<int, int> right, left, el, len;
    
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    for (int i = 0; i < n; ) {
        int j = i+1;
        while(j < n && a[j] == a[i])    j++;

        right[i] = j-1;
        left[j-1] = i;
        el[i] = a[i], el[j-1] = a[i];
        len[i] = len[j-1] = j-i;
        s.insert(mp(-(j-i), mp(i,j-1)));
        valid[i] = valid[j-1] = true;
        i = j;
    }

    int ans = 0;
    while(!s.empty()) {

        ans++;
        auto p = *s.begin();    s.erase(p);
        int l = p.S.F-1, r = p.S.S+1;
        //trace3(l+1, r-1, -p.F);
        valid[l+1] = valid[r-1] = false;

        if (l >= 0 && r < n && el[l] == el[r] && valid[l] && valid[r]) {
            //trace2("here", s.size());
            int ll = left[l], rr = right[r];
            valid[l] = valid[r] = false;

            auto t1 = mp(-len[l], mp(ll, l)); 
            auto t2 = mp(-len[r], mp(r, rr));

            if (s.find(t1) != s.end() && s.find(t2) != s.end()) {
                // trace("ho");
                s.erase(t1), s.erase(t2);

                int n_len = len[l]+len[r];
                len[ll] = len[rr] = n_len;
                s.insert(mp(-n_len, mp(ll, rr)));
                el[ll] = el[rr] = el[l];
                right[ll] = rr;
                left[rr] = ll;
                valid[ll] = valid[rr] = true;
            }
        } 
        else { 
            if (l >= 0 && r < n) {
                //trace("new_bounderies");
                int ll = left[l];
                auto tmp = mp(-len[l], mp(ll, l));

                if (s.find(tmp) != s.end() && valid[l]) {
                    s.erase(tmp);
                    valid[l] = valid[ll] = false;

                    s.insert(mp(-len[l], mp(ll, l+1)));
                    
                    int length = len[l];
                    len[ll] = len[l+1] = length;
                    el[ll] = el[l+1] = el[l];
                    right[ll] = l+1;
                    left[l+1] = ll;
                    valid[l+1] = valid[ll] = true;
                }
            
                int rr = right[r];
                auto tmp2 = mp(-len[r], mp(r, rr));

                if (s.find(tmp2) != s.end() && valid[r]) {
                    s.erase(tmp2);

                    s.insert(mp(-len[r], mp(l+2, rr)));
                    valid[r] = valid[rr] = false;

                    len[l+2] = len[rr] = len[r];
                    el[l+2] = el[rr] = el[r];
                    right[l+2] = rr;
                    left[rr] = l+2;
                    valid[l+2] = valid[rr] = true;
                }
            }
        }
    }
    cout << ans << endl;


    return 0;
}
