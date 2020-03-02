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


# :warning: bbst/implicit_treap.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d342894e126a2cdd0812cd3a6c903bbd">bbst</a>
* <a href="{{ site.github.repository_url }}/blob/master/bbst/implicit_treap.cpp">View this file on GitHub</a>
    - Last commit date: 2019-09-12 22:14:50+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>
#include <random>
#include <cstdint>
#include <functional>
using namespace std;

//===
// merge()
// split()
// random_access (.at(), operator[])
// insert_at(d, k)
// erase_at(k)
// fold(l, r) [l, r)
// update(l, r) [l, r)
// update_at(k)
// reverse(l, r) [l, r)
// RangeMinQuery
struct ImplicitTreap {
    using uint = uint_fast32_t;
    using llong = long long;
    
    struct Node {
        Node *par = nullptr;
        Node *left = nullptr, *right = nullptr;

        uint cnt = 1;
        llong value;
        llong minv;
        uint pri;

        Node (llong value, uint pri): value(value), pri(pri) {};
    };

    mt19937 rnd;
    Node *root = nullptr;
    llong neutral = 1ll << 60ll;

    ImplicitTreap(): rnd((random_device())()) {};

    uint size() { return count(root); };
    uint count(Node *r) { return r == nullptr ? 0 : r->cnt; };
    llong acc(Node *r) { return r == nullptr ? neutral : r->minv; };

    void push_up(Node *r) {
        r -> cnt = count(r->left) + count(r->right) + 1;
        r -> minv = min(acc(r->left), acc(r->right));
    };
    
    Node *merge(Node *l, Node *r) {
        if (l == nullptr) return r;
        else if (r == nullptr) return l;

        if (l->pri > r->pri) {
            l->right = merge(l->right, r);
            push_up(l);
            return l;
        }
        else {
            r->left = merge(l, r->left);
            push_up(r);
            return r;
        }
    };
    pair<Node *, Node *> split(Node *t, uint k) {
        if (t == nullptr) return make_pair(nullptr, nullptr);

        if (k < count(t->left)) {
            pair<Node *, Node *>s = split(t->left, k);
            t->left = s.second;
            push_up(t);
            return make_pair(s.first, t);
        }
        else {
            pair<Node *, Node *> s = split(t->right, k - count(t->left) - 1);
            t->right = s.first;
            push_up(t);
            return make_pair(t, s.second);
        }
    };

    void insert(Node *t, uint k, llong v) {
        Node *u = new Node(v, rnd());

        pair<Node *, Node *>s = split(t, k);
        t = merge(s.first, u);
        t = merge(t, s.second);
    };
    void erase(Node *t, uint k) {
        pair<Node *, Node *>s1 = split(t, k + 1);
        pair<Node *, Node *>s2 = split(s1.first, k);

        delete(s2.second);
        merge(s2.first, s1.second);
    };

    void update_at(uint k, llong v) {
        erase(root, k);
        insert(root, k, v);
    };
    llong fold(uint l, uint r) {
        pair<Node *, Node *>s1 = split(root, r);
        pair<Node *, Node *>s2 = split(s1.first, l);

        llong ret = s2.second->minv;

        root = merge(s2.first, s2.second);
        root = merge(root, s1.second);

        return ret;
    };
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
#line 1 "bbst/implicit_treap.cpp"
#include <iostream>
#include <random>
#include <cstdint>
#include <functional>
using namespace std;

//===
// merge()
// split()
// random_access (.at(), operator[])
// insert_at(d, k)
// erase_at(k)
// fold(l, r) [l, r)
// update(l, r) [l, r)
// update_at(k)
// reverse(l, r) [l, r)
// RangeMinQuery
struct ImplicitTreap {
    using uint = uint_fast32_t;
    using llong = long long;
    
    struct Node {
        Node *par = nullptr;
        Node *left = nullptr, *right = nullptr;

        uint cnt = 1;
        llong value;
        llong minv;
        uint pri;

        Node (llong value, uint pri): value(value), pri(pri) {};
    };

    mt19937 rnd;
    Node *root = nullptr;
    llong neutral = 1ll << 60ll;

    ImplicitTreap(): rnd((random_device())()) {};

    uint size() { return count(root); };
    uint count(Node *r) { return r == nullptr ? 0 : r->cnt; };
    llong acc(Node *r) { return r == nullptr ? neutral : r->minv; };

    void push_up(Node *r) {
        r -> cnt = count(r->left) + count(r->right) + 1;
        r -> minv = min(acc(r->left), acc(r->right));
    };
    
    Node *merge(Node *l, Node *r) {
        if (l == nullptr) return r;
        else if (r == nullptr) return l;

        if (l->pri > r->pri) {
            l->right = merge(l->right, r);
            push_up(l);
            return l;
        }
        else {
            r->left = merge(l, r->left);
            push_up(r);
            return r;
        }
    };
    pair<Node *, Node *> split(Node *t, uint k) {
        if (t == nullptr) return make_pair(nullptr, nullptr);

        if (k < count(t->left)) {
            pair<Node *, Node *>s = split(t->left, k);
            t->left = s.second;
            push_up(t);
            return make_pair(s.first, t);
        }
        else {
            pair<Node *, Node *> s = split(t->right, k - count(t->left) - 1);
            t->right = s.first;
            push_up(t);
            return make_pair(t, s.second);
        }
    };

    void insert(Node *t, uint k, llong v) {
        Node *u = new Node(v, rnd());

        pair<Node *, Node *>s = split(t, k);
        t = merge(s.first, u);
        t = merge(t, s.second);
    };
    void erase(Node *t, uint k) {
        pair<Node *, Node *>s1 = split(t, k + 1);
        pair<Node *, Node *>s2 = split(s1.first, k);

        delete(s2.second);
        merge(s2.first, s1.second);
    };

    void update_at(uint k, llong v) {
        erase(root, k);
        insert(root, k, v);
    };
    llong fold(uint l, uint r) {
        pair<Node *, Node *>s1 = split(root, r);
        pair<Node *, Node *>s2 = split(s1.first, l);

        llong ret = s2.second->minv;

        root = merge(s2.first, s2.second);
        root = merge(root, s1.second);

        return ret;
    };
};
//===

int main() {

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

