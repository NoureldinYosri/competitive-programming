#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

int fail[1 << 20];
int A[1 << 20], n;
int prv[1 << 20];
void tc(){
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i);
	set<int> S{A, A + n};
	loop(i, n) prv[A[i]] = -1, fail[A[i]] = 0;
	loop(i, n) {
		int x = A[i];
		fail[x] = max(fail[x], i - prv[x] - 1);
		prv[x] = i;
	}
	for(int x : S) fail[x] = max(fail[x], n - prv[x] - 1);
	vi B{all(S)};
	sort(all(B), [](const int & a, const int &b){
		return pi(fail[a], a) < pi(fail[b], b);
	});
//	for(int b : B) cerr << pi(b, fail[b]) << endl;
	int i = 0;
	for(int len = 1, ans = -1; len <= n; len++){
		while(i < sz(B) && fail[B[i]] < len) {
			if(ans == -1 || B[i] < ans) ans = B[i];
			i++;
		}
		printf("%d%c", ans, " \n"[len==n]);
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
