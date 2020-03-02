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


# :warning: bbst/avl_tree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d342894e126a2cdd0812cd3a6c903bbd">bbst</a>
* <a href="{{ site.github.repository_url }}/blob/master/bbst/avl_tree.cpp">View this file on GitHub</a>
    - Last commit date: 2019-11-12 13:37:07+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <functional>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
using namespace std;
template<class T, class Compare = less<T> >
using MaxHeap = priority_queue<T, vector<T>, Compare>;
template<class T, class Compare = greater<T> >
using MinHeap = priority_queue<T, vector<T>, Compare>;
using llong = long long;

//===
template<typename T, typename Compare = less<T> >
struct AVLTree {
    enum direction {L = 0, R = 1};
    direction inv_dir(direction d) {return 1 - d;};
    
    struct Node {
        T data;
        size_t height;
        size_t sz;
        Node *ch[2]; //0:left, 1:right

        Node(T data):data(data), height(0), sz(1), ch{nullptr, nullptr} {};
    };

    Node *root;
    Compare cmp;

    AVLTree(Compare cmp = Compare()):root(nullptr), cmp(cmp) {}

    size_t size(Node *p) {
        if (p == nullptr) return 0;
        else return p->sz;
    };
    size_t size() {
        return size(root);
    };
    
    size_t height(Node *p) {
        if (p == nullptr) return 0;
        else return p->height;
    };
    size_t height() {
        return height(root);
    };

    Node *find(const T &x) {
        Node *w = root;
        while (w != nullptr) {
            if (cmp(w->data, x)) w = w->ch[R];
            else if (cmp(x, w->data)) w = w->ch[L];
            else return w;
        }
        return w;
    };
    bool contains(const T &x) {
        return find(x) != nullptr;
    };
    bool has_element(const T &x) {
        return find(x) != nullptr;
    };
    
    size_t order_of(T x) {};
    T find_Kth_element(size_t k) {};

    void insert(T data) {
        insert(root, new Node(data));
    };
    Node *insert(Node *r, Node *p) {
        if (r == nullptr) return p;
        if (cmp(p->data, r->data)) r->ch[L] = insert(r->ch[L], p);
        else r->ch[R] = insert(r->ch[R], p);

        return balance(r);
    };

    void erase(T x) {
        
    };

    // d=L:left-rotate; u move to left
    // d=R:right-rotate;
    template<int d>
    Node *rotate(Node *u) {
        Node w = u->ch[inv_dir(d)];
        u->ch[inv_dir(d)] = w->ch[d];
        w->ch[d] = u;
        // update(u); update(w);
        return w;
    };

    Node *balance() {
    };

    #ifndef NODEBUG
    void dump(void){};
    void dump(Node *u, int h){};
    #else
    void dump(void){};
    void dump(Node *u, int h){};
    #endif
};
//===

int main() {
    return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "bbst/avl_tree.cpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <functional>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
using namespace std;
template<class T, class Compare = less<T> >
using MaxHeap = priority_queue<T, vector<T>, Compare>;
template<class T, class Compare = greater<T> >
using MinHeap = priority_queue<T, vector<T>, Compare>;
using llong = long long;

//===
template<typename T, typename Compare = less<T> >
struct AVLTree {
    enum direction {L = 0, R = 1};
    direction inv_dir(direction d) {return 1 - d;};
    
    struct Node {
        T data;
        size_t height;
        size_t sz;
        Node *ch[2]; //0:left, 1:right

        Node(T data):data(data), height(0), sz(1), ch{nullptr, nullptr} {};
    };

    Node *root;
    Compare cmp;

    AVLTree(Compare cmp = Compare()):root(nullptr), cmp(cmp) {}

    size_t size(Node *p) {
        if (p == nullptr) return 0;
        else return p->sz;
    };
    size_t size() {
        return size(root);
    };
    
    size_t height(Node *p) {
        if (p == nullptr) return 0;
        else return p->height;
    };
    size_t height() {
        return height(root);
    };

    Node *find(const T &x) {
        Node *w = root;
        while (w != nullptr) {
            if (cmp(w->data, x)) w = w->ch[R];
            else if (cmp(x, w->data)) w = w->ch[L];
            else return w;
        }
        return w;
    };
    bool contains(const T &x) {
        return find(x) != nullptr;
    };
    bool has_element(const T &x) {
        return find(x) != nullptr;
    };
    
    size_t order_of(T x) {};
    T find_Kth_element(size_t k) {};

    void insert(T data) {
        insert(root, new Node(data));
    };
    Node *insert(Node *r, Node *p) {
        if (r == nullptr) return p;
        if (cmp(p->data, r->data)) r->ch[L] = insert(r->ch[L], p);
        else r->ch[R] = insert(r->ch[R], p);

        return balance(r);
    };

    void erase(T x) {
        
    };

    // d=L:left-rotate; u move to left
    // d=R:right-rotate;
    template<int d>
    Node *rotate(Node *u) {
        Node w = u->ch[inv_dir(d)];
        u->ch[inv_dir(d)] = w->ch[d];
        w->ch[d] = u;
        // update(u); update(w);
        return w;
    };

    Node *balance() {
    };

    #ifndef NODEBUG
    void dump(void){};
    void dump(Node *u, int h){};
    #else
    void dump(void){};
    void dump(Node *u, int h){};
    #endif
};
//===

int main() {
    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

