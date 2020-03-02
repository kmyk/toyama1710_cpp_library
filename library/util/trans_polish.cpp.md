---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: util/trans_polish.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#05c7e24700502a079cdd88012b5a76d3">util</a>
* <a href="{{ site.github.repository_url }}/blob/master/util/trans_polish.cpp">View this file on GitHub</a>
    - Last commit date: 2019-09-27 22:25:24+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;

ll mod;
bool valid;

ll pow_mod(ll n, ll m) {
    ll ret = 1;
    while (m) {
        if (m & 1) {
            ret = ret * n % mod;
        }
        n = n * n % mod;
        m = m >> 1;
    }
    return ret;
}

//===
struct token {
    int pre;
    ll num;
    char op;

    token(char op):op(op) {
        if (op == '(' || op == ')') pre = 0;
        if (op == '+' || op == '-') pre = 1;
        if (op == '*' || op == '/') pre = 2;
    }

    token(ll num):num(num) {
        pre = -1;
    }
};

ll split_num(const string &str, int &pos) {
    ll s = 0;
    while (isdigit(str[pos])) {
        s = s * 10 + (str[pos] - '0');
        pos++;
    }
    return s;
}

vector<token> trans_polish(const string &expr) {
    stack<token> op;

    vector<token> ret;

    for (int pos = 0; pos < expr.size(); pos++) {
        if (isdigit(expr[pos])) {
            token n(split_num(expr, pos));
            pos--;
            ret.push_back(n);
        }
        else {
            token x(expr[pos]);

            if (x.op == ')') {
                while(op.top().op != '(') {
                    ret.push_back(op.top());
                    op.pop();
                }
                op.pop();
            }
            else if (x.op == '(') {
                op.push(x);
            }
            else if (x.op != ' ') {
                while(!op.empty()) {
                    if (op.top().pre >= x.pre) {
                        ret.push_back(op.top());
                        op.pop();
                        
                        continue;
                    }
                    else {
                        break;
                    }
                }
                op.push(x);
            }
        }
    }

    while (!op.empty()) {
        ret.push_back(op.top()); op.pop();
    }

    return ret;
}
//===

ll eval(const vector<token> &expr) {
    stack<ll> st;

    for (int i = 0; i < expr.size(); i++) {
        if (expr[i].pre == -1) {
            st.push(expr[i].num);
        }
        else {
            char op = expr[i].op;
            ll b = st.top(); st.pop();
            ll a = st.top(); st.pop();

            switch(op) {
            case '+':
                st.push((a + b) % mod);
                break;
            case '-':
                st.push((a - b + mod) % mod);
                break;
            case '*':
                st.push(a * b % mod);
                break;
            case '/':
                if (b == 0) valid = false;
                b = pow_mod(b, mod - 2);
                st.push(a * b % mod);
                break;
            }
        }
    }

    return st.top();
}

// verify
// https://onlinejudge.u-aizu.ac.jp/solutions/problem/0264/review/3763192/ei1710/C++14
int PCK_pre2012_9(void)
{
    auto print_polish = [](vector<token> expr) {
        cout << "polish: ";
        for (auto t : expr) {
            if (t.pre == -1) {
                cout << ' ' << t.num << ' ';
            }
            else {
                cout << ' ' << t.op << ' ';
            }
        }
        cout << endl;
    };
    
    string expr;
    char ch;
    
    while (scanf("%lld", &mod), mod != 0) {
        expr.clear();
        
        while ((ch = getchar()) != '\n') {
            if (ch != ' ' && ch != ':') {
                expr += ch;
            }
        }

        vector<token> polish = trans_polish(expr);

        //print_polish(polish);

        valid = true;
        ll ans = eval(polish);

            if (valid) {
            cout << expr << " = ";
            cout << ans;
            cout << ' ' << "(mod " << mod << ')' << endl;
        }
        else {
            cout << "NG" << endl;
        }
    }

    return 0;
}

int main()
{
    return PCK_pre2012_9();
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "util/trans_polish.cpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;

ll mod;
bool valid;

ll pow_mod(ll n, ll m) {
    ll ret = 1;
    while (m) {
        if (m & 1) {
            ret = ret * n % mod;
        }
        n = n * n % mod;
        m = m >> 1;
    }
    return ret;
}

//===
struct token {
    int pre;
    ll num;
    char op;

    token(char op):op(op) {
        if (op == '(' || op == ')') pre = 0;
        if (op == '+' || op == '-') pre = 1;
        if (op == '*' || op == '/') pre = 2;
    }

    token(ll num):num(num) {
        pre = -1;
    }
};

ll split_num(const string &str, int &pos) {
    ll s = 0;
    while (isdigit(str[pos])) {
        s = s * 10 + (str[pos] - '0');
        pos++;
    }
    return s;
}

vector<token> trans_polish(const string &expr) {
    stack<token> op;

    vector<token> ret;

    for (int pos = 0; pos < expr.size(); pos++) {
        if (isdigit(expr[pos])) {
            token n(split_num(expr, pos));
            pos--;
            ret.push_back(n);
        }
        else {
            token x(expr[pos]);

            if (x.op == ')') {
                while(op.top().op != '(') {
                    ret.push_back(op.top());
                    op.pop();
                }
                op.pop();
            }
            else if (x.op == '(') {
                op.push(x);
            }
            else if (x.op != ' ') {
                while(!op.empty()) {
                    if (op.top().pre >= x.pre) {
                        ret.push_back(op.top());
                        op.pop();
                        
                        continue;
                    }
                    else {
                        break;
                    }
                }
                op.push(x);
            }
        }
    }

    while (!op.empty()) {
        ret.push_back(op.top()); op.pop();
    }

    return ret;
}
//===

ll eval(const vector<token> &expr) {
    stack<ll> st;

    for (int i = 0; i < expr.size(); i++) {
        if (expr[i].pre == -1) {
            st.push(expr[i].num);
        }
        else {
            char op = expr[i].op;
            ll b = st.top(); st.pop();
            ll a = st.top(); st.pop();

            switch(op) {
            case '+':
                st.push((a + b) % mod);
                break;
            case '-':
                st.push((a - b + mod) % mod);
                break;
            case '*':
                st.push(a * b % mod);
                break;
            case '/':
                if (b == 0) valid = false;
                b = pow_mod(b, mod - 2);
                st.push(a * b % mod);
                break;
            }
        }
    }

    return st.top();
}

// verify
// https://onlinejudge.u-aizu.ac.jp/solutions/problem/0264/review/3763192/ei1710/C++14
int PCK_pre2012_9(void)
{
    auto print_polish = [](vector<token> expr) {
        cout << "polish: ";
        for (auto t : expr) {
            if (t.pre == -1) {
                cout << ' ' << t.num << ' ';
            }
            else {
                cout << ' ' << t.op << ' ';
            }
        }
        cout << endl;
    };
    
    string expr;
    char ch;
    
    while (scanf("%lld", &mod), mod != 0) {
        expr.clear();
        
        while ((ch = getchar()) != '\n') {
            if (ch != ' ' && ch != ':') {
                expr += ch;
            }
        }

        vector<token> polish = trans_polish(expr);

        //print_polish(polish);

        valid = true;
        ll ans = eval(polish);

            if (valid) {
            cout << expr << " = ";
            cout << ans;
            cout << ' ' << "(mod " << mod << ')' << endl;
        }
        else {
            cout << "NG" << endl;
        }
    }

    return 0;
}

int main()
{
    return PCK_pre2012_9();
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

