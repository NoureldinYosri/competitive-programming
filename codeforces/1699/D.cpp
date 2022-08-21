#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < (n); i++)
#define all(A) A.begin(), A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int, int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A, t)                             \
  cerr << #A << ": ";                           \
  copy(all(A), ostream_iterator<t>(cerr, " ")); \
  cerr << endl
#define prArr(A, n, t)                            \
  cerr << #A << ": ";                             \
  copy(A, A + n, ostream_iterator<t>(cerr, " ")); \
  cerr << endl
#define PRESTDIO() cin.tie(0), cerr.tie(0), ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0), __builtin_ffsll(x) - 1)
const double PI = acos(-1);
template <class A, class B>
std::ostream& operator<<(std::ostream& st, const std::pair<A, B> p) {
  st << "(" << p.first << ", " << p.second << ")";
  return st;
}
using namespace std;

const int MAX = 5 << 10;
int A[MAX], n;
bool canDelete[MAX][MAX];

void init() {
  static int cnt[MAX];
  loop(i, n) loop(j, n) canDelete[i][j] = false;
  loop(i, n) {
    for (int j = i; j < n; j++) cnt[A[j]] = 0;
    int mx = 0;
    for (int j = i; j < n; j++) {
      cnt[A[j]]++;
      mx = max(mx, cnt[A[j]]);
      int len = j - i + 1;
      if (2 * mx <= len && len%2 == 0) {
        canDelete[i][j] = true;
      }
    }
  }
}

int dp[MAX];

int f(int i, int v) {
  if(i == n) return 0;
  if(A[i] == v) return dp[i];
  return -n;
}

int solve() {
  dp[n] = 0;
  for(int i = n-1; i >= 0; i--) {
    int v = A[i];
    dp[i] = f(i + 1, A[i]);
    for(int j = i + 1; j < n; j++)
      if(canDelete[i + 1][j]) {
        dp[i] = max(dp[i], f(j + 1, v));
      }
    dp[i]++;
  }
  int ans = max(0, dp[0]);
  for(int i = 1; i < n; i++)
    if(canDelete[0][i - 1]) {
      ans = max(ans, dp[i]);
    }
  return ans;
}


void tc() {
  scanf("%d", &n);
  loop(i, n) {
		scanf("%d", A + i);
		A[i]--;
	}
  init();

  printf("%d\n", solve());
}

int main() {
#ifdef HOME
  freopen("in.in", "r", stdin);
#endif
  int T;
  scanf("%d", &T);
  while (T--) tc();
  return 0;
}
