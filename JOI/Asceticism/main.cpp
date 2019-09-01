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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

const int MAX = 1024;

vi bf(int n) {
	vi cnt(n,0);
	vi P;
	loop(i,n) P.push_back(i);
	do{
		int k = 0;
		loop(i,n-1) k += P[i + 1] < P[i];
		cnt[k]++;
	}while(next_permutation(all(P)));
	return cnt;
}

int dp[MAX][MAX];
int C[MAX][MAX];

int f(int n,int k) {
	if(k > n-1) return 0;
	if(n == 1) return k==0;
	int & ret = dp[n][k];
	if(ret != -1) return ret;
	ret = f(n-1,k)*(k + 1) + f(n-1,k-1)*(n-k);
	return ret;
}

// f(n,k) = f(n,n-k)
// f(n-1,k-1) = f(n-1,n-k)

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	for(int n = 0;n < MAX;n++){
		C[n][0] = C[n][n] = 1;
		for(int k = 1;k < MAX;k++)
			C[n][k] = C[n-1][k-1] + C[n-1][k];
	}
	memset(dp,-1,sizeof dp);
	for(int n = 1;n <= 10;n++) {
//		vi q = bf(n);
//		print(q,int);
		cerr << "g: ";
		for(int k = 0;k < n;k++)
			cerr << f(n,k) << " ";
		cerr << endl;
		cerr << "C: ";
		for(int k = 0;k < n;k++)
			cerr << C[n-1][k] << " ";
		cerr << endl;
	}
	return 0;
}
