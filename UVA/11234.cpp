/*
    Author : manu_sy

    Idea : Any expression E can be viewed as :
        E -> E op E | number

        - So parse the expression using a stack to calculate resulting E in the above form
            let E = E1 opx E2
        
        Insert this E in queue
        Now we'll just simulate the queue operations backwards :
          
          E is at the back of the queue (since all insertions happen at back and the last E inserted would now be at the back)
          E = E1 opx E2
          
        1) Now to get this E from queue E2 must have been at the top of queue and then E1 second
            and we would be on operator opx. 
        2) Therefor opx would have been the last term of the expression and at that moment the
            queue would look like above.
        3) So add opx to answer string (in front) and add E1 to front of queue and then E2.

        - And now get E from the back of queue and continue step 1,2,3.
        - If you encounter number then just insert in front of answer
        
    Another Sol :
    https://github.com/AbdelrahmanRamadan/competitive-programming/blob/master/UVA/11234%20-%20Expressions.cpp
*/
#include <bits/stdc++.h>
using namespace std;

/* Template Begins */

#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'

/* Template Ends */
struct ex {
    ex *left, *right;
    char op, c;
    int type; 
    ex(ex* left = NULL, ex* right = NULL, char op = '1', char c = '1', int type = 1): 
        left(left), right(right), op(op), c(c), type(type) {}
};
string s;

signed main() {

    IOS; 
    int cases;  cin >> cases;
    while(cases--) {

        cin >> s;

        stack<ex*> st;

        for (auto i : s) {
            if (islower(i)) {
                st.push(new ex(NULL, NULL, '1', i, 0));
            } else {
                auto p2 = st.top(); st.pop();
                auto p1 = st.top(); st.pop();
                st.push(new ex(p1, p2, i));
            }
        }
        assert(st.size() == 1);

        stack<char> ans;
        deque<ex*> q;
        q.push_back(st.top());

        while (!q.empty()) {
            auto e = q.back();  q.pop_back();
            if (e->type) {
                q.push_front(e->left);
                q.push_front(e->right);
                ans.push(e->op);
            } else {
                ans.push(e->c);
            }
            delete e;
        }

        string res;
        while(!ans.empty()) res += ans.top(), ans.pop();
        cout << res << endl;
    }

    return 0;
}
