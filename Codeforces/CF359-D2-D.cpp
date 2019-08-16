/* 
    Author : Shashank Yadav

    Idea : 
        - Goal is to find subarrays l...r such that there exists some a[j] in subarray
          which divides all elements of subarray

        - So each subarray has one a[j]. We'll try to find all such a[j]'s and call them candidates.
        - Notice that a candidate is one which is not divisible by the previous element
          and the next element (handle duplicates here)
        - After getting a list of candidates ( Ci's ) the array would look like this :
          ..C1.....C2......C3....C4..
        - Notice that any element would belong to atmost 2 subarrays
        - So just find the subarray for each candidate and consequently the answer.

        - Time Complexity : O(n)
        
     Also can check out solution using Sparse Tables :
        - https://github.com/osamahatem/CompetitiveProgramming/blob/master/Codeforces/359D.%20Pair%20of%20Numbers.cpp 
*/
    
#include <bits/stdc++.h>
using namespace std;

#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'

const int N = 3e5+7;

int n, a[N];
vector<int> g[N];

signed main() {

    IOS;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> candidates;
    for (int i = 0; i < n; ) {

        int j = i+1;
        while(j < n && a[j] == a[i])    j++;

        bool valid = true;
        if (i-1 >= 0 && a[i]%a[i-1] == 0)   valid = false;
        if (j < n && a[i]%a[j] == 0)        valid = false;

        if (valid) {
            candidates.push_back(i);
            while(j < n && a[j]%a[i] == 0)  j++;
        } 
        i = j;
    }

    int ml = -1;
    for (auto i : candidates) {
        int l = i, r = i;
        while(l >= 0 && a[l]%a[i] == 0) l--;
        while(r < n && a[r]%a[i] == 0)  r++;
        r--, l++;

        g[r-l].push_back(l+1);
        ml = max(ml, r-l);
    }
    cout << g[ml].size() << " " << ml << endl;
    //sort(g[ml].begin(), g[ml].end());
    for (auto i : g[ml]) cout << i << " ";  cout << endl;

    return 0;
}
