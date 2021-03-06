#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <functional>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <random>
using namespace std;
template<class T, class Compare = less<T> >
using MaxHeap = priority_queue<T, vector<T>, Compare>;
template<class T, class Compare = greater<T> >
using MinHeap = priority_queue<T, vector<T>, Compare>;
using llong = long long;

//===
//#include <cstdint>
template <typename T, T mod>
struct RollingHash {
    const string s;
    const int len;
    const T base;
    vector<T> hashed, power;

    RollingHash (const string &s, T base):s(s), len(s.size()), base(base) {
        hashed.assign(len + 1, 0);
        power.assign(len + 1, 1);

        for (int i = 0; i < len; i++) {
            hashed[i + 1] = (hashed[i] * base + s[i]) % mod;
            power[i + 1] = power[i] * base % mod;
        }
    };

    // s[l, r)
    T get_hash(int l, int r) {
        T res = hashed[r] + mod - hashed[l] * power[r - l] % mod;
        if (res >= mod) res -= mod;
        return res;
    };
};

template<>
struct RollingHash<uint64_t, (1ull << 61ull) - 1ull> {
    const string s;
    const int len;
    const uint64_t mask30 = (1ull << 30ull) - 1ull;
    const uint64_t mask31 = (1ull << 31ull) - 1ull;
    const uint64_t mod = (1ull << 61ull) - 1ull;
    const uint64_t base;
    vector<uint64_t> hashed, power;

    RollingHash (const string &s, uint64_t base):s(s), len(s.size()), base(base) {
        hashed.assign(len + 1, 0);
        power.assign(len + 1, 1);

        for (int i = 0; i < len; i++) {
            hashed[i + 1] = calc_mod(mul(hashed[i], base) + s[i]);
            power[i + 1] = calc_mod(mul(power[i], base));
        }
    };

    // s[l, r)
    uint64_t get_hash(int l, int r) {
        uint64_t res = hashed[r] + mod - calc_mod(mul(hashed[l], power[r - l]));
        if (res >= mod) res -= mod;
        return res;
    };

    inline uint64_t mul(uint64_t l, uint64_t r) {
        uint64_t lu = l >> 31;
        uint64_t ld = l & mask31;
        uint64_t ru = r >> 31;
        uint64_t rd = r & mask31;
        uint64_t mid = ld * ru + lu * rd;

        return ((lu * ru) << 1) +
            (mid >> 30) + ((mid & mask30) << 31)
            + ld * rd;
    };

    inline uint64_t calc_mod(uint64_t v) {
        v = (v & mod) + (v >> 61);
        if (v >= mod) v -= mod;
        return v;
    };
};

using MRollingHash = RollingHash<uint64_t, (1ull << 61ull) - 1ull>;
//===

int ABC141D() {
    llong n;
    string s;

    cin >> n;
    cin >> s;
    //MRollingHash rh(s, (random_device())());
    //RollingHash<uint64_t, (uint64_t)(1e9) + 9> rh(s, (random_device())());
    RollingHash<uint64_t, (uint64_t)(1e9) + 7> rh1(s, (random_device())());
    RollingHash<uint64_t, (uint64_t)(1e9) + 9> rh2(s, (random_device())());

    llong valid = 0;
    llong invalid = n;
    while (invalid - valid > 1) {
        llong len = (valid + invalid) / 2;
        llong cnt = 0;
        llong m = 0;

        for (int i = 0; i + len <= n; i++) {
            uint64_t h1 = rh1.get_hash(i, i + len);
            uint64_t h2 = rh2.get_hash(i, i + len);

            cnt = 0;
            for (int j = i; j + len <= n; j++) {
                if (rh1.get_hash(j, j + len) == h1 &&
                    rh2.get_hash(j, j + len) == h2) {
                    //cout << rh.get_hash(j, j + len) << endl;
                    //cout << j << ' ' << j + len << endl;
                    //cout << s.substr(j, len) << endl;
                    
                    cnt++;
                    j += len - 1;
                }
            }
            //cout << "=====" << endl;
            m = max(cnt, m);
        }

        if (m >= 2) valid = len;
        else invalid = len;
    }

    cout << valid << endl;
    
    return 0;
}

int main() {
    return ABC141D();
}
