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

const int MAXN = 200*1000 + 10;
char ring[MAXN];
int n;
int dp[MAXN][2][2][2][2];
int visID[MAXN][2][2][2][2], visNum;

bool isGood(int d, bool leftAttack, bool rightAttack){
	if(leftAttack ^ rightAttack) {
		if(rightAttack) return d;
		else return !d;
	} else {
		return true;
	} 
}

int solve(int i, bool decision, bool isBeingAttacked, bool c_0, bool c_neg){
	int c = ring[i] == 'R';
	if(i == n-1){
		if(decision != c_neg) return n + 5;
		int ret = c != c_neg;
		if(isGood(c_neg, isBeingAttacked, !c_0)) return ret;
		return n + 5;
	}
	int & ret = dp[i][isBeingAttacked][decision][c_0][c_neg];
	if(visID[i][isBeingAttacked][decision][c_0][c_neg] == visNum) return ret;
	visID[i][isBeingAttacked][decision][c_0][c_neg] = visNum;
	ret = n + 5;
	
	loop(j, 2) if(isGood(decision, isBeingAttacked, !j)) {
		ret = min(ret, solve(i + 1, j, decision, c_0, c_neg) + (c != decision));
	}
	
	return ret;
}

void tc(){
	scanf("%d %s", &n, ring);
	visNum++;
	int ans = n;
	loop(i, 2) loop(j, 2) ans = min(ans, solve(0, i, j, i, j));
	printf("%d\n", ans);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
