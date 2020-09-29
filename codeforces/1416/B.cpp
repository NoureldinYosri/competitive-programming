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

const int MAXN = 10*1000 + 10;
int A[MAXN];
int n;


void tc(){
	int sum = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", A + i);
		sum += A[i];
	}
	if(sum%n){
		puts("-1");
		return;
	}
	int x0 = sum / n;

	vector<tuple<int, int, int>> ans;

	for(int i = 2; i <= n; i++) {
		if(A[i]%i){
			int need = i - A[i]%i;
			ans.emplace_back(1, i, need);
			A[i] += need;
			A[1] -= need;
		}
		int x = A[i]/i;
		ans.emplace_back(i, 1, x);
		A[1] += A[i];
		A[i] = 0;
	}

	for(int i = 2; i <= n; i++) {
		ans.emplace_back(1, i, x0);
		A[1] -= x0;
		A[i] = x0;
	}
	printf("%d\n", sz(ans));
	for(auto [i, j, x] : ans){
		printf("%d %d %d\n", i, j, x);
	}
	assert(A[1] == x0);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif

	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
