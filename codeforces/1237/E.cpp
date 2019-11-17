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


int getMax(int k) {
	int N = (1 << (k+1)) - 1;
	return N;
}

int getK(int n) {
	int k = 0;
	while(getMax(k) < n) {
//		cout << getMax(k) << " " << n << endl;
		k++;
	}
	return k;
}

int dp[1 << 20][20][2][2];

const int mod = 998244353;
int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a,int b) {
	return (a*(ll)b)%mod;
}

int bf(int s,int e,int k,int target) {
	if(s == e) return (s&1) == target;
	if(s > e) return 1;
	if(k == 0) return 0;
	int len = e-s+1;
	if(getMax(k) < len) return 0;
	if(k > getK(len)) return 0;
	int sp = s & 1;
	int & ret = dp[len][k][sp][target];
	if(ret != -1) return ret;
	ret = 0;


	s = 1;
	e = len;
	if(sp%2 == 0) s = 2,e = len+1;

	int l = e - getMax(k-1);
	int r = s + getMax(k-1);
	for(int m = l;m <= r;m++){
		if((m&1) != target) continue;
		if(abs(getK(m-l) - getK(e-m)) > 1) continue;
		int tmp = mul(bf(s,m-1,k-1,target^1),bf(m+1,e,k-1,target));
		ret = add(ret,tmp);
	}
//	cerr << s << " " << e << " " << k << " " << target << ": " << ret << endl;
	return ret;
}

int bf(int n) {
	int k = getK(n);
	memset(dp,-1,sizeof dp);
	int ret = 0;
	loop(i,2) ret = add(ret,bf(1,n,k,i));
//	cout << bf(1,n,k,1) << endl;
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n; cin >> n;
	int itr[2] = {1,2};
	int k = 0;
	bool y = (n == 1) || (n == 2);
	for(;k < 20 && !y;k++) {
		int x = itr[1-(k&1)];
		itr[0] = 2*x + (k&1);
		itr[1] = itr[0] + 1;
		y = itr[0] == n || itr[1] == n;
	}
	cout << y << endl;
	return 0;
}
