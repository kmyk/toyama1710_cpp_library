#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;

//===
template<class SemiLattice,
         class Merge = function<SemiLattice(SemiLattice, SemiLattice)> >
struct SparseTable {

    bool builded = false;
    const int n;
    const Merge merge;
    vector<vector<SemiLattice>> table;
    vector<size_t> log2;

    SparseTable():n(0){}
    SparseTable(int n, SemiLattice v, const Merge &f):
        n(n), merge(f)
    {
        log2.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) log2[i] = log2[i / 2] + 1;
        
        table.assign(log2[n] + 1, vector<SemiLattice>(n, v));
    };

    template<class InputIterator>
    SparseTable(InputIterator first, InputIterator last, const Merge &f):
        n(distance(first, last)), merge(f)
    {
        log2.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) log2[i] = log2[i / 2] + 1;
        
        table.assign(log2[n] + 1, vector<SemiLattice>(first, last));
        build();
    };

    void build(void) {
        for (int i = 0; i < log2[n]; i++) {
            int w = 1 << i;
            for (int j = 0; j + (w * 2) <= n; j++) {
                table[i + 1][j] = merge(table[i][j], table[i][j + w]);
            }
        }

        builded = true;
    };

    void set(int k, SemiLattice dat) {
        table[0][k] = dat;
        builded = false;
    };

    //[l, r)
    SemiLattice fold(int l, int r) {
        if (!builded) build();

        int k = log2[r - l];

        return merge(table[k][l], table[k][r - (1 << k)]);
    };

    int size() {
        return n;
    };

    SemiLattice operator[] (const int k) {
        return table[0][k];
    };
};
//===

int RMQ(void) {
    using ll = long long;

    ll n, q;
    ll com, x, y;
    vector<ll> arr;

    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> x;
        arr.push_back(x);
    }

    cout << "building..." << endl;
    SparseTable<ll> st(arr.begin(), arr.end(), [](ll l, ll r){return max(l, r);});
    cout << "done." << endl;
    while (q--) {
        cin >> x >> y;
        cout << st.fold(x, y) << endl;
    }

    return 0;
}

int PCK2014_pre_8(void) {
    using ll = long long;
    struct Star{ ll x, y, b; };
    auto scmp = [](const Star &x, const Star &y) {
                    if (x.b < y.b) return true;
                    else return false;
                };

    ll ans = 0;
    ll n, d;
    vector<Star> s;
    
    cin >> n >> d;
    s = vector<Star>(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i].x >> s[i].y >> s[i].b;
    }

    sort(s.begin(), s.end(), scmp);
    
    SparseTable<ll> minX(n, 0, [](ll l, ll r){return min(l, r);});
    SparseTable<ll> maxX(n, 0, [](ll l, ll r){return max(l, r);});
    SparseTable<ll> minY(n, 0, [](ll l, ll r){return min(l, r);});
    SparseTable<ll> maxY(n, 0, [](ll l, ll r){return max(l, r);});

    for (int i = 0; i < n; i++) {
        minX.set(i, s[i].x);
        maxX.set(i, s[i].x);

        minY.set(i, s[i].y);
        maxY.set(i, s[i].y);
    }

    for (int i = 0; i < n; i++) {
        ll l = i;
        ll r = upper_bound(s.begin(), s.end(), (Star){0, 0, s[i].b + d}, scmp)
            - s.begin();

        ll x = maxX.fold(l, r) - minX.fold(l, r);
        ll y = maxY.fold(l, r) - minY.fold(l, r);

        ans = max(ans, x * y);
    }

    cout << ans << endl;

    return 0;
}

int main() {
    return RMQ();
    //return PCK2014_pre_8();
}
