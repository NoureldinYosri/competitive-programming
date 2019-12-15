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


const int MAXN = 150000 + 10,B = 7;
int dp[MAXN][B][B];
bool choice[MAXN][B][B];
int n;
char S[MAXN];
int one[3] = {'o','n','e'};
int two[3] = {'t','w','o'};
string good = "onetw";


vector<int> V;

void solve(char *S,int offset){
	loop(i,B) loop(j,B) dp[n][i][j] = 0;
	n = strlen(S);
	if(n == 0) return;
	for(int i = n-1;i >= 0;i--){
		int c3 = find(all(good),S[i]) - good.begin() + 1;
		loop(c1,B) loop(c2,B){
			int & res = dp[i][c1][c2];
			res = 1 + dp[i+1][c1][c2];
			choice[i][c1][c2] = 0;
			int C[] = {c1,c2,c3};
			bool isOne = 1,isTwo = 1;
			loop(k,3) {
				isOne &= one[k] == C[k];
				isTwo &= two[k] == C[k];
			}
			if(!isOne && !isTwo) {
				int tmp = dp[i+1][c2][c3];
				if(tmp < res){
					res = tmp;
					choice[i][c1][c2] = 1;
				}
			}
		}
	}
//	cerr << S << ": " << dp[0][0][0] << endl;
	int i = 0,c1 = 0,c2 = 0;
	for(;i < n;i++){
		int c3 = find(all(good),S[i]) - good.begin() + 1;
		if(choice[i][c1][c2]){
			c1 = c2;
			c2 = c3;
		}
		else {
			V.push_back(i + offset);
		}
	}
//	print(V,int);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	loop(i,3){
		one[i] = find(all(good),one[i]) - good.begin() + 1;
		two[i] = find(all(good),two[i]) - good.begin() + 1;
	}
	int T; scanf("%d",&T);
	while(T--){
		scanf("%s",S);
		n = strlen(S);
		loop(i,n) if(find(all(good),S[i]) == good.end()) S[i] = 0;
//		prArr(S,n,char);
		V.clear();
		for(int i = 0;i < n;) if(S[i]){
			solve(S + i,i);
			i += strlen(S + i);
		}
		else i++;
		printf("%d\n",sz(V));
		loop(i,sz(V)) printf("%d ",V[i] + 1);
		puts("");

	}
	return 0;
}
