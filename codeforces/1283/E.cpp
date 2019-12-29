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


const int MAX = 200*1000 + 10;
int n;
int X[MAX];

pi dp[MAX][8];

int interpret(int msk, int x0, int x){
	if(x == -1) return 0;
	int ret = 0;
	for(int p = x0-1; p <= x0 + 1;p++){
		int i = p - x0 + 1;
		if(!(msk & (1 << i))) continue;
		int j = p - x;
		assert(j <= 1);
		if(j < -1) continue;
		ret |= 1 << (j + 1);
	}
	return ret;
}

pi solve(int pos,int msk){
	if(pos == n) return pi(0,0);
	pi & ret = dp[pos][msk];
	if(ret != pi(-1,-1)) return ret;
	ret = pi(INT_MAX,0);
	msk = interpret(msk,pos ? X[pos-1] : -1, X[pos]);
	
	for(int i = -1;i <= 1;i++){
		int b = 1 << (i+1);
		int d = (msk & b) ? 0 : 1;
		pi q = solve(pos+1, msk | b);
		q.first += d;
		q.second += d;
		ret.first = min(ret.first,  q.first);
		ret.second = max(ret.second, q.second);
	}
	
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",X + i);
	sort(X, X + n);
	
	fill(dp[0],dp[MAX],pi(-1,-1));
	pi p = solve(0,0);
	printf("%d %d\n",p.first, p.second);
	
	
	return 0;
}
