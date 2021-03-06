#include <iostream>
#include <vector>
using namespace std;

//===
struct UnionFind {
    int n;
    vector<int> parent;

    UnionFind() {}
    UnionFind(int nmemb) {
        init(nmemb);
    };

    void init(int nmemb) {
        parent.clear();
        parent.assign(nmemb, -1);
    };

    int root(int x) {
        if (parent[x] < 0) {
            return x;
        }
        return parent[x] = root(parent[x]);
    };

    void unite(int x, int y) {
        x = root(x);
        y = root(y);

        if (x == y) return;

        if (parent[y] < parent[x]) swap(x, y);

        parent[x] += parent[y];
        parent[y] = x;
        
        return;
    };
    
    bool same(int x, int y) {
        return root(x) == root(y);
    };
    int size(int x) {
        return -(parent[root(x)]);
    };
};
//===

// verify AOJ DSL_1_A
int main()
{
    UnionFind uf;
    int n, q;
    int com, x, y;

    cin >> n >> q;
    uf.init(n);
    for (int i = 0; i < q; i++) {
        cin >> com >> x >> y;

        if (com == 0) {
            uf.unite(x, y);
        }
        else {
            if (uf.same(x, y)) {
                cout << 1 << endl;
            }
            else {
                cout << 0 << endl;
            }
        }
    }

    return 0;
}
