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


# :warning: array/persistent_array.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f1f713c9e000f5d3f280adbd124df4f5">array</a>
* <a href="{{ site.github.repository_url }}/blob/master/array/persistent_array.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-05 20:26:40+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>
#include <functional>
#include <vector>
#include <memory>
using namespace std;
using llong = long long;

//===
template<class T>
struct PersitentArray {
    struct Node {
        using Leaf = T;
        using NodePointer = union {
            Node *u;
            Leaf *dat;
        };
        NodePointer ch[2] = {}; // 0:left, 1:right

        Node (): ch{nullptr, nullptr} {};
    };
    using np = typename Node::NodePointer;
    using Leaf = typename Node::Leaf;
    
    inline int inv(int p) { // p = 0 or 1
        return p ^ 1;
    };
    
    Node *root;
    int arr_sz;
    
    template<class InputIterator>
    PersitentArray(InputIterator first, InputIterator last) {
        arr_sz = distance(first, last);

        root = new Node();
        auto itr = first;
        for (int i = 0; i < arr_sz; i++, itr++) {
            int range[] = {arr_sz, 0}; //[0] = right, [1] = left
            int mid;
            int direction;
            np u_parent = root;
            np u = root;

            while (range[0] - range[1] > 1) {
                mid = (range[0] + range[1]) / 2;
                direction = i < mid ? 0 : 1;

                range[direction] = mid;
                if (u->ch[direction] == nullptr && range[0] - range[1] > 1) {
                    u->ch[direction] = new Node();
                }
                u_parent = u;
                u = u->ch[direction];
            }

            if (i & 1) u_parent->ch[1] = new Leaf(*itr);
            else u_parent->ch[0] = new Leaf(*itr);
        }
    };
    PersitentArray(int size, T d = T()) {
        vector<T> v(size, d);
        PersitentArray(v.begin(), v.end());
    };

    T get(int idx){
        int range[] = {arr_sz, 0};
        int mid;
        int direction;
        np u = root;

        while (range[0] - range[1] > 1) {
            mid = (range[0] + range[1]) >> 1;
            direction = idx < mid ? 0 : 1;

            range[direction] = mid;
            u = u->ch[direction];
        }

        return *(u.dat);
    };
    void set(int idx, T val) {
        int range[] = {arr_sz, 0};
        int mid;
        int direction;
        np next_root = new Node();
        np u = root;
        np w = next_root;

        mid = (range[0] + range[1]) / 2;
        direction = idx < mid ? 0 : 1;

        range[direction] = mid;
        w->ch[inv(direction)] = u->ch[inv(direction)];
        while (range[0] - range[1] > 1) {
            if (range[0] - range[1] > 1) {
                w->ch[direction] = new Node();
                w = w->ch[direction];
                u = u->ch[direction];
            }
        }

        if (idx & 1) w->ch[1] = new Leaf(val);
        else w->ch[0] = new Leaf(val);
        root = next_root;
    };
    
    PersitentArray get_array() {
        return *this;
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
#line 1 "array/persistent_array.cpp"
#include <iostream>
#include <functional>
#include <vector>
#include <memory>
using namespace std;
using llong = long long;

//===
template<class T>
struct PersitentArray {
    struct Node {
        using Leaf = T;
        using NodePointer = union {
            Node *u;
            Leaf *dat;
        };
        NodePointer ch[2] = {}; // 0:left, 1:right

        Node (): ch{nullptr, nullptr} {};
    };
    using np = typename Node::NodePointer;
    using Leaf = typename Node::Leaf;
    
    inline int inv(int p) { // p = 0 or 1
        return p ^ 1;
    };
    
    Node *root;
    int arr_sz;
    
    template<class InputIterator>
    PersitentArray(InputIterator first, InputIterator last) {
        arr_sz = distance(first, last);

        root = new Node();
        auto itr = first;
        for (int i = 0; i < arr_sz; i++, itr++) {
            int range[] = {arr_sz, 0}; //[0] = right, [1] = left
            int mid;
            int direction;
            np u_parent = root;
            np u = root;

            while (range[0] - range[1] > 1) {
                mid = (range[0] + range[1]) / 2;
                direction = i < mid ? 0 : 1;

                range[direction] = mid;
                if (u->ch[direction] == nullptr && range[0] - range[1] > 1) {
                    u->ch[direction] = new Node();
                }
                u_parent = u;
                u = u->ch[direction];
            }

            if (i & 1) u_parent->ch[1] = new Leaf(*itr);
            else u_parent->ch[0] = new Leaf(*itr);
        }
    };
    PersitentArray(int size, T d = T()) {
        vector<T> v(size, d);
        PersitentArray(v.begin(), v.end());
    };

    T get(int idx){
        int range[] = {arr_sz, 0};
        int mid;
        int direction;
        np u = root;

        while (range[0] - range[1] > 1) {
            mid = (range[0] + range[1]) >> 1;
            direction = idx < mid ? 0 : 1;

            range[direction] = mid;
            u = u->ch[direction];
        }

        return *(u.dat);
    };
    void set(int idx, T val) {
        int range[] = {arr_sz, 0};
        int mid;
        int direction;
        np next_root = new Node();
        np u = root;
        np w = next_root;

        mid = (range[0] + range[1]) / 2;
        direction = idx < mid ? 0 : 1;

        range[direction] = mid;
        w->ch[inv(direction)] = u->ch[inv(direction)];
        while (range[0] - range[1] > 1) {
            if (range[0] - range[1] > 1) {
                w->ch[direction] = new Node();
                w = w->ch[direction];
                u = u->ch[direction];
            }
        }

        if (idx & 1) w->ch[1] = new Leaf(val);
        else w->ch[0] = new Leaf(val);
        root = next_root;
    };
    
    PersitentArray get_array() {
        return *this;
    };
};
//===

int main() {

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

