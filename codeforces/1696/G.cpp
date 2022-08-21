#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
using vi = std::vector<int>;
using pi = std::pair<int,int>;
using vp = std::vector<pi>;
using ll = long long;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
void tc();
auto test_cases = [](){
	int T; scanf("%d", &T);
	while(T--) tc();
};
using namespace std;

int n, m, x, y;

int B[1 << 20];


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
  scanf("%d %d %d %d", &n, &m, &x, &y);
  if(x < y) swap(x, y);
  loop(i, n) scanf("%d", B + i);
  while(m--) {
    int t; scanf("%d", &t);
    if(t == 1) {
      int k, v; scanf("%d %d", &k, &v);
      k--;
      B[k] = v;
    } else {
      int l, r; scanf("%d %d", &l, &r);
      l--, r--;
      double ans = 0, d = 0;
      for(int i = l; i < r; i++) {
        double a = max(0.0, B[i] - d), b = B[i + 1];
        if(a < b) {
          double t = a/y;
          d = t * x;
          ans += t;
        } else {
          double t = a/x;
          d = t * y;
          ans += t;
        }
      }
      ans += max(0.0, B[r] - d) / x;
      printf("%.10f\n", ans);
    }
  }
	return 0;
}
