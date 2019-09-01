#ifdef ACTIVE
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


int A[8],B[8];

int dp[7][1 << 8];
int C[7][1 << 8],n;

int solve(int x,int msk) {
	if(!msk) return 1;
	int &ret = dp[x][msk];
	if(ret != -1) return ret;
	ret = 0;
	loop(i,n) if(msk & (1 << i)){
		if(A[i] == x || B[i] == x) {
			int y = A[i] + B[i]- x;
			int tmp = solve(y,msk ^ (1 << i));
			if(tmp) {
				ret = 1;
				C[x][msk] = i;
			}
		}
	}
	return ret;
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> n;
	loop(i,n) cin >> A[i] >> B[i];
	memset(dp,-1,sizeof dp);
	int s = 0,c = 0;
	bool f = 0;
	int tot = (1 << n) - 1;
	for(s = 0;s < n;s++){
		for(c = 0;c < 2;c++) {
			int x = (c == 0) ? B[s] : A[s];
			f = solve(x,tot ^ (1 << s));
			if(f) break;
		}
		if(f) break;
	}
	assert(f);
	cout << s+1 << " " << "ab"[c] << endl;
	int x = (c == 0) ? B[s] : A[s];
//	cout << x << endl;
	int msk = tot ^ (1 << s);
	loop(t,n-1) {
		int i = C[x][msk];
		cout << i+1 << " " << "ab"[x != A[i]] << endl;
		assert(A[i] == x || B[i] == x);
		x = A[i] + B[i] - x;
		msk ^= 1 << i;
	}
	return 0;
}
#endif
