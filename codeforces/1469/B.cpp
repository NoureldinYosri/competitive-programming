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

vi R, B;

void read(vi & A){
	int n; scanf("%d", &n);
	A.resize(n);
	for(int & a : A) scanf("%d", &a);
}

int visId[111][111], visNum;
int dp[111][111];

int solve(int i, int j){
	if(i == sz(R) && j == sz(B)) return 0;
	if(visId[i][j] == visNum) return dp[i][j];
	visId[i][j] = visNum;
	int & ret = dp[i][j];
	ret = -(1 << 29);
	
	if(i < sz(R)) {
		int x = max(0, solve(i + 1, j));
		ret = max(ret, x + R[i]);
	}
	if(j < sz(B)){
		int x = max(0, solve(i, j + 1));
		ret = max(ret, x + B[j]);		
	}
//	cerr << i << " " << j << ": " << ret << endl;
	return ret;
}

void tc(){
	read(R);
	read(B);
	visNum++;
	printf("%d\n", max(0, solve(0, 0)));
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
