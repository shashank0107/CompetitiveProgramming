/* 
    - Note : This currently has been checked only on prestests since not being able to submit on topcoder currently
    Author : manu_sy
    
    Idea : 
        - Similar to 
        https://github.com/MohamedAhmed04/Competitive-programming/blob/master/Topcoder/Topcoder%20SRM525-D1-525%20Rumor.cpp
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long    ll;

#define pb           push_back
#define F            first
#define S            second
#define mp           make_pair
#define all(a)       (a).begin(),(a).end()
#define fr(i,a,b)    for(int i=a;i<=b;i++)
#define lp(i,a)      for(int i=0;i< a;i++)

#define trace(x)                 cout << #x << ": " << x << endl;
#define trace2(x, y)             cout << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)          cout << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl;

const int INF = 1e9;

class Rumor {
public:
    void upd(string& state, int idx, char c) {
        if (c == 'A') {
            if (state[idx] == 'Y' || state[idx] == 'B') state[idx] = 'Y';
            else state[idx] = 'A';
        }
        else {
            if (state[idx] == 'Y' || state[idx] == 'A') state[idx] = 'Y';
            else state[idx] = 'B';
        }
    }
    void set(int& mask, int bit) {
        mask |= (1<<bit);
    }
    void unset(int& mask, int bit) {
        mask &= ~(1<<bit);
    }
    int getMinimum(string know, vector<string> graph) {
        
        int ans = INF;
        int n = know.size();
        string final(n, 'Y');
        if (know == final)  return 0;

        for (int tr = 0; tr < (1<<n); tr++) 
        {
            int mask = tr;          // if ith bit is set in mask then transfer rumor A else B (valid only if we can transfer both)
            string cur = know;      // else transfer the one we can and complement the bit

            bool valid = true;
            int day;
            for (day = 1; valid; day++)
            {
                string new_state = cur;
                for (int i = 0; i < n; i++)
                {
                    if (cur[i] == 'A') {
                        for (int j = 0; j < n; j++) if (graph[i][j] == 'Y') {
                            upd(new_state, j, 'A');
                        }
                        unset(mask, i);
                    }
                    else if (cur[i] == 'B') {
                        for (int j = 0; j < n; j++) if (graph[i][j] == 'Y') {
                            upd(new_state, j, 'B');
                        }
                        set(mask, i);
                    }
                    else if (cur[i] == 'Y') {
                        if ((mask>>i)&1) {
                            for (int j = 0; j < n; j++) if (graph[i][j] == 'Y') {
                                upd(new_state, j, 'A');
                            }
                        }
                        else {
                            for (int j = 0; j < n; j++) if (graph[i][j] == 'Y') {
                                upd(new_state, j, 'B');
                            }
                        }
                        mask ^= (1<<i);     
                    }
                }
                if (new_state == cur) valid = false;
                if (new_state == final) break;
                cur = new_state;
            }
            if (valid)  ans = min(ans, day);
        }
    
        if (ans != INF) return ans;
        else return -1;
    }
};

<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
