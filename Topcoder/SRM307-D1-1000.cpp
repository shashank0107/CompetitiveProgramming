/*
    Author : manu_sy
    Idea : We will solve using meet in middle - Do Parallel BFS from start and end state
          - Note that you only need to simulate merge operation as every total transformation can be modelled as a 
            sequence of merges followed by a sequence of splits
          - So merge operations while moving from the end state would actually simulate split operation
          - Store time of visit of each state reachable from start in map vis[0][state] and reachable from end in vis[1][state]
            Keep on doing parallel moves from both direction and break when a common point is found 
          - Answer is -1 if their sum is not same
*/
#include "bits/stdc++.h"
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

/** Template Ends **/
map<vector<int>, int> vis[2];
int ans;

void move(queue<pair<vector<int>, int> >& q, int id) {

    queue<pair<vector<int>, int> > tempq;
    while (!q.empty())
    {
        auto p = q.front(); q.pop();

        vector<int> v = p.F;
        if (v.size() == 1)  continue;

        LP(i,v.size()) FOR(j,i+1,(int)v.size() - 1) 
        {
            vector<int> tempv(1, v[i] + v[j]);
            LP(k,v.size()) if (k != i && k != j) tempv.pb(v[k]);
            sort(all(tempv));
            if (vis[id].count(tempv))   continue;
            vis[id][tempv] = p.S + 1;
            tempq.push(mp(tempv, p.S + 1));
            if (vis[1 - id].count(tempv))
            {
                ans = p.S + 1 + vis[1 - id][tempv];
                return;
            }
        }
    }
    q = tempq;
}

class SplitAndMergeGame {
public:
    int minMoves(vector <int> st, vector <int> en) {
        sort(all(st)); sort(all(en));
        int s1 = 0, s2 = 0; for (auto i : st) s1 += i; for (auto i : en) s2 += i;
        if (s1 != s2)   return -1;

        vis[0].clear(), vis[1].clear();
        ans = -1;
        if (st == en)   return 0;

        queue<pair<vector<int>, int> > q1, q2;
        vis[0][st] = 0, vis[1][en] = 0;
        q1.push(mp(st, 0));
        q2.push(mp(en, 0));

        while (1)
        {
            move(q1, 0);
            if (ans != -1)  return ans;
            move(q2, 1);
            if (ans != -1)  return ans;
        }
        return -1;
    }   
};

signed main() {

    IOS;
    SplitAndMergeGame s;
    cout << s.minMoves({4, 2}, {2, 2, 2}) << endl;
    cout << s.minMoves({1, 2}, {3}) << endl;
    cout << s.minMoves({1, 2, 3, 4, 5, 6}, {7, 7, 7}) << endl;
    cout << s.minMoves({3, 4}, {1, 6}) << endl;
    cout << s.minMoves({31, 2}, {1}) << endl;

    return 0;
}
