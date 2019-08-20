/*
    Author : manu_sy

    Idea : Just convert the expression to postfix and then evaluate.
        - Keep checking errors in between
*/
#include <bits/stdc++.h>
using namespace std;

#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'

struct item {
    int type;
    double val;
    char op;
    item(int type = 0, double val = 0, char op = 'c'): type(type), val(val), op(op) {}
};
int pr(char c) {
    if (c == '+')   return 1;
    else if (c == '*')  return 2;
    else if (c == '(')  return 0;
    else if (c == ')')  return 3;
    else assert(false);
}
bool isop(char c) {
    return c == '+' || c == '*' || c == ')';
}

string s;
int n;

pair<double, int> getDig(int idx) {
    double res = 0;
    while(idx < n && isdigit(s[idx])) {
        res *= 10;  res += s[idx]-'0';
        idx++;
    }
    if (idx < n && s[idx] == '.') {
        idx++;
        double mul = 1;
        while(idx < n && isdigit(s[idx])) {
            res += (s[idx]-'0')*pow(0.1, mul++);
            idx++;
        }
    }
    return make_pair(res, idx);
}

signed main() {

    IOS;
    int t;  cin >> t;
    while(t--) {

        cin >> s;   n = s.size();

        bool need_op = false;

        stack<item> st;
        stack<char> opst;

        bool valid = true;
        for (int i = 0; i < n; i++) {

            if (need_op) {
                if (!isop(s[i])) {
                    valid = false;  break;
                } else {
                    if (s[i] != ')') {
                        while(!opst.empty() && pr(opst.top()) >= pr(s[i])) {
                            st.push(item(1, 0, opst.top()));    opst.pop();
                        }
                        opst.push(s[i]);
                        need_op = false;
                    } else {
                        while(!opst.empty() && opst.top() != '(') {
                            st.push(item(1, 0, opst.top()));    opst.pop();
                        }
                        if (opst.empty()) {
                            valid = false;  break;
                        }
                        opst.pop();
                        need_op = true;
                    }
                }
            }
            else {
                if (isdigit(s[i])) {
                    auto p = getDig(i);
                    double val = p.first;
                    st.push(item(0, val));
                    i = p.second-1;
                    need_op = true;
                } else if (s[i] == '(') {
                    opst.push('(');                    
                } else {
                    valid = false;
                    break;
                }   
            }
        }

        if (valid) {
            while(!opst.empty()) {
                if (opst.top() == '(') {
                    valid = false;  break;
                } else {
                    st.push(item(1, 0, opst.top()));    opst.pop();
                }
            }
        }
        if (!valid) {
            cout << "ERROR" << endl;
            continue;
        }
        else {
            double ans = 0;
            vector<item> postfix;
            while(!st.empty()) {
                postfix.push_back(st.top());   st.pop();
            }
            reverse(postfix.begin(), postfix.end());

            // cout << "posfix : ";
            // for (auto i : postfix) if (i.type) cout << i.op << " "; else cout << i.val << " ";
            // cout << endl;

            stack<double> temp;
            for (auto i : postfix) {
                if (i.type) {
                    if (temp.size() < 2) {
                        valid = false;  break;
                    } else {
                        double val1 = temp.top();  temp.pop();
                        double val2 = temp.top();  temp.pop();
                        if (i.op == '+')    temp.push(val1+val2);
                        else if (i.op == '*') temp.push(val1*val2);
                        else assert(false);
                    }
                } else {
                    temp.push(i.val);
                }
            }
            if (temp.size() != 1) valid = false;

            if (valid) {
                double ans = temp.top();    
                if (floor(ans) == ceil(ans))    cout << (long long)ans << endl;
                else cout << ans << endl;
            } else {
                cout << "ERROR" << endl;
            }
        }
    }

    return 0;
}
