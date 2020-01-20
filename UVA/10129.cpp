/*
    Author : manu_sy
    Idea : Consider a graph with each char representing a node (n = 26). N
           Now every word w can be considered as an edge between char w[0] and w[w.size() - 1]
           We just have to check if a euler path exists in this graph.
           Credits : http://jhe169auckland.blogspot.com/2014/07/uva-10129-play-on-words.html
*/
#include <bits/stdc++.h>
using namespace std;

/** Template Begins **/

typedef long long        ll;
typedef pair<int,int>    PII;

#define IOS         ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl        '\n'
#define pb          push_back
#define F           first
#define S           second
#define mp          make_pair
#define all(a)      (a).begin(), (a).end()
#define FOR(i,a,b)  for(int i=a;i<=b;i++)
#define LP(i,n)     for(int i=0;i< n;i++)

/* Debug */

template<class L, class R> ostream &operator<<(ostream &os, pair<L,R> P) {
  return os << "(" << P.F << "," << P.S << ")";
} 

template<class T> ostream &operator<<(ostream& os, vector<T> V) {
  os << "["; for (auto vv : V) os << vv << ","; return os << "]";
}

template<class TH> void _dbg(const char *sdbg, TH h){ cerr << sdbg << '=' << h << endl; }

template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
  while(*sdbg!=',') cerr << *sdbg++;
  cerr<<'='<<h<<','; _dbg(sdbg+1, a...);
}

#ifdef LOCAL
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#define cerr if(0)cout
#endif

/* Debug Ends */

const int N = 1e5+7;
const int C = 26;

/** Template Ends **/
int n;

struct UNF {
    vector<int> par, sz;
    UNF(int n) {
        par.resize(n); sz.resize(n);
        for (int i = 0; i < n; i++) make_set(i);
    }
    void make_set(int v) {
        par[v] = v, sz[v] = 1;
    }
    int find_set(int v) {
        if (v == par[v])    return v;
        return par[v] = find_set(par[v]);
    }
    void union_sets(int u, int v) {
        u = find_set(u);
        v = find_set(v);
        if (u != v) {
            if (sz[u] < sz[v])  swap(u, v);
            par[v] = u;
            sz[u] += sz[v];
        }
    }
};
void Yes() {
    cout << "Ordering is possible." << endl;
}
void No() {
    cout << "The door cannot be opened." << endl;
}

signed main() {

    IOS;
    int t; cin >> t;
    while (t--)
    {
        cin >> n;
        map<char, int> in, out;
        set<char> nodes;
        UNF uf(C+3);

        for (int i = 0; i < n; i++)
        {
            string s; cin >> s;
            in[s.back()]++;
            out[s[0]]++;
            nodes.insert(s[0]), nodes.insert(s.back());
            uf.union_sets(s[0]-'a', s.back()-'a');
        }
        if (uf.sz[uf.find_set(*nodes.begin() - 'a')] != nodes.size()) No();
        else 
        {
            bool valid = true;
            vector<int> diff;
            for (char c : nodes) {
                if (in[c] != out[c])    diff.pb(in[c] - out[c]);
            }
            if (diff.size() != 2 && diff.size() != 0)   
                valid = false;
            if (diff.size() == 2 && !((diff[0] == 1 && diff[1] == -1) || (diff[0] == -1 && diff[1] == 1)))
                valid = false;
            
            if (valid) Yes();
            else No();    
        }
    }

    return 0;
}
