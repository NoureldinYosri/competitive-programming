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

const int MAXN = 222,MAXLEN = 6*MAXN;
char S[2][MAXN];
int len[2];
int dp[MAXN][MAXN][MAXLEN];
char choice[MAXN][MAXN][MAXLEN];
string alpha = "()";

void getNext(int & i,int & j,int & open,char c){
	i += c == S[0][i] && i < len[0];
	j += c == S[1][j] && j < len[1];
	open += (c == '(') - (c == ')');
}

int solve(const int i,const int j,const int open){
	if(i == len[0] && j == len[1] && open == 0) return 0;
	if(dp[i][j][open] != -1) return dp[i][j][open];
	int & ret = dp[i][j][open];
	ret = 1 << 28;
	for(char c : alpha){
		int ni = i,nj = j,nopen = open;
		getNext(ni,nj,nopen,c);
		if(nopen < 0) continue;
		if(i == ni && j == nj && c == '(' && open) continue;
//		cout << i << " " << j << " " << open << " -> " << ni << " " << nj << " " << nopen << endl;
		int tmp = solve(ni,nj,nopen) + 1;
		if(tmp < ret){
			ret = tmp;
			choice[i][j][open] = c;
		}
	}
//	cerr << i << " " << j << " " << open << endl;
	assert(ret < (1 << 28));
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	loop(i,2){
		scanf("%s",S[i]);
		len[i] = strlen(S[i]);
	}
	memset(dp,-1,sizeof dp);
	cerr << solve(0,0,0) << endl;
	
	for(int i = 0,j = 0,open = 0;!(i == len[0] && j == len[1] && open == 0);){
		char c = choice[i][j][open];
		putchar(c);
		getNext(i,j,open,c);
	}
	puts("");
	return 0;
}
