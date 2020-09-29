#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#define endl "\n"
#define ll long long
#define sz(s) (int)(s.size())
#define INF 0x3f3f3f3f3f3f3f3fLL
#define all(v) v.begin(),v.end()
#define watch(x) cout<<(#x)<<" = "<<x<<endl
const int dr[] { -1, -1, 0, 1, 1, 1, 0, -1 };
const int dc[] { 0, 1, 1, 1, 0, -1, -1, -1 };
#if __cplusplus >= 201402L
template<typename T>
vector<T> create(size_t n) {
    return vector<T>(n);
}
template<typename T, typename ... Args>
auto create(size_t n, Args ... args) {
    return vector<decltype(create<T>(args...))>(n, create<T>(args...));
}
#endif
void run(string f) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
#ifdef EZZAT
    freopen("input.in", "r", stdin);
    //freopen("output.out", "w", stdout);
#else
    freopen((f + ".in").c_str(), "r", stdin);
    freopen((f + ".out").c_str(), "w", stdout);
#endif
}

int main() {
    // run("collider");
    int n, q;
    string tmp;
    cin >> n >> q >> tmp;
    int sqrtN = 1000;
    vector<string> v;
    for (int i = 0; i < n; i += sqrtN)
        v.push_back(tmp.substr(i, sqrtN));
    auto remove = [&](int idx) {
        for (int k = 0; k < sz(v); k++)
            if (idx > sz(v[k]))
                idx -= sz(v[k]);
            else {
                char tmp = v[k][idx - 1];
                v[k].erase(idx - 1, 1);
                return tmp;
            }
        assert(0);
        return '\0';
    };
    auto add = [&](int idx, char ch) {
        for (int k = 0; k < sz(v); k++)
            if (idx > sz(v[k]))
                idx -= sz(v[k]);
            else {
                string s = v[k];
                v[k] = s.substr(0, idx);
                v[k] += ch;
                v[k] += s.substr(idx);
                return;
            }
        assert(0);
    };
    while (q--) {
        if (q % sqrtN == 0) {
            tmp = "";
            for (auto &it : v)
                tmp += it;
            v.clear();
            for (int i = 0; i < n; i += sqrtN)
                v.push_back(tmp.substr(i, sqrtN));
        }
        char type;
        cin >> type;
        if (type == 'a') {
            int i, j;
            cin >> i >> j;
            add(j - 1, remove(i));
        } else {
            int idx;
            cin >> idx;
            for (int k = 0; k < sz(v); k++)
                if (sz(v[k]) < idx)
                    idx -= sz(v[k]);
                else {
                    cout << v[k][idx - 1] << endl;
                    break;
                }
        }
    }
}

                                                                        