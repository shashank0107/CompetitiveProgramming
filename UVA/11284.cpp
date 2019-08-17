/*
    Author : manu_sy
    Verdict : Getting WA

    Idea : 
        - First calculate cost[][] matrix : min cost to go b/w any villages
        - Select the subset of all the stores that we are going to visit : call it chosen
        - Apply tsp between them to reach the starting point and calculate the answer
    
    - Something is wrong in this. idk 
    - Passing all the cases on udebug and forum but faling on systests
    
    Correct Solution : (Good implementation)
        https://github.com/SaraElkadi/competitive-programming-/blob/master/UVA/11284.cpp
*/
#include <bits/stdc++.h>
using namespace std;

#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'

// Debug //
#define trace(x)                 cerr << #x << ": " << x << endl;
#define trace2(x, y)             cerr << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)          cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl;
#define trace4(a, b, c, d)       cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << endl;

const int N = 50+7;
const int P = 15;
const double INF = 1e18;
const int MASK = 1<<15;

int n, m, p;
double cost[N][N], price[P];
int st[P];
double dp[MASK][P];

void pre() {
    for (int i = 0; i <= n; i++) for (int j = 0; j <= n; j++) if (i != j) cost[i][j] = INF;
}
void floyd_warshall() {
    for (int k = 0; k <= n; k++) 
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                cost[i][j] = min(cost[i][j], cost[i][k]+cost[k][j]);
}
double calc(int mask, int last, vector<int>& chosen) {

    double& ret = dp[mask][last];
    if (ret != -1)  return ret;

    int new_mask = mask&(~(1<<last));
    if (new_mask == 0) {    
        //trace3(mask, last, cost[0][st[chosen[last]]]);
        return ret = cost[0][st[chosen[last]]];
    }

    ret = INF;
    for (int i = 0; i < chosen.size(); i++) {
        if ((new_mask>>i)&1) {
            ret = min(ret, calc(new_mask, i, chosen) + cost[st[chosen[i]]][st[chosen[last]]]);
        }
    }
    //trace3(mask, last, ret);
    return ret;
}
// chosen contains all the indices of the stores i am going to visit
double solve(vector<int>& chosen) {

    int pp = chosen.size();
    for (int i = 0; i < (1<<pp)+5; i++) for (int j = 0; j <= pp; j++) dp[i][j] = -1;
    
    double ini = 0;
    for (auto i : chosen) ini -= price[i];

    double path_sum = INF;
    for (int i = 0; i < pp; i++) {
        path_sum = min(path_sum, calc((1<<pp)-1, i, chosen) + cost[ st[chosen[i]] ][0]);
        //trace3(i, st[chosen[i]], cost[ st[chosen[i]] ][0]);
    }
    //trace2(ini, path_sum);
    return path_sum + ini;
}

signed main() {

    IOS;
    cout << fixed << setprecision(2);
    int t;  cin >> t;
    while(t--) {

        cin >> n >> m;
        pre();
        for (int i = 0; i < m; i++) {
            int a, b; cin >> a >> b;
            double x;   cin >> x;
            cost[b][a] = cost[a][b] = min(cost[a][b], x);
        }
        floyd_warshall();

        cin >> p;
        for (int i = 0; i < p; i++) {
            cin >> st[i] >> price[i];
        }

        double pay = 0;
        for (int mask = 1; mask < (1<<p); mask++) {

            vector<int> chosen;
            for (int i = 0; i < p; i++) if ((mask>>i)&1)    chosen.push_back(i);

            double cur_ans = solve(chosen);
            pay = min(pay, cur_ans);
        }
        if (pay == 0) cout << "Don't leave the house" << endl;
        else          cout << "Daniel can save $" << -pay << endl;
    }
    return 0;
}
