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


const int MAX = 1 << 10;
int A[MAX],n;

int ctr[MAX];

char name[2][10] = {"lowie","imitater"};
int X[2];
int dp[MAX][MAX];
int H;

int getXor(int hi,int low){
	int ret = X[1^(hi&1)];
	int a = 0,b = 0;
	if(low == H) a = ctr[H];
	else a = ctr[H] - 1,b = 1;
	if((H - hi)%2 == 0) a = 0;
	if((low - hi)%2 == 0) b = 0;
	ret ^= a ^ b;
	cerr << hi << " " << low << ": " << ret << " " << X[1^(hi&1)]<< endl;
	return ret;
}

int solve(int hi,int low) {
	if(hi+1 == low) return getXor(hi,low) > 0;
	int & ret = dp[hi][low];
	if( ret != -1) return ret;
	ret = solve(hi + 1,low) || solve(hi,low - 1);
	return 0;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d",A + i);
		ctr[A[i]]++;
	}
	int s = 0;
	s = accumulate(A,A + n,0);
	int h = *min_element(A,A + n);
	bool win = n%2 ? s%2 : (s%2 || h%2);
	cout << name[1-win] << endl;
	return 0;
}
#endif
