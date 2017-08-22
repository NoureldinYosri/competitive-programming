#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;


const int mod = 1e9 + 7;
const int MAX = 2010;
int dp[MAX][MAX],C[MAX][MAX];

int add(int a,int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}

int mul(int a,int b){
	return (a*1LL*b)%mod;
}

void init(){
	loop(i,MAX){
		C[i][0] = C[i][i] = 1;
		range(j,1,i-1)
			C[i][j] = add(C[i - 1][j],C[i - 1][j - 1]);
	}
	memset(dp,-1,sizeof dp);
}

int solve(int num_rows,int len){
	if(len < 0) return 0;
	if(!num_rows) return 1;
	int & ret = dp[num_rows][len];
	if(ret != -1) return ret;
	ret = solve(num_rows,len - 2);
	ret = add(ret,mul(2,solve(num_rows,len - 1)));
	ret = add(ret,solve(num_rows-1,len));
	return ret;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	init();
	int n,m; scanf("%d %d",&n,&m);
	int ans = 0;
	range(l,1,n){
		int num = n - l + 1,tmp = 0;
		range(center,1,l) {
			range(I,0,m-2)
					tmp = add(tmp,mul(m-(I + 2)+1,mul(solve(center-1,I),solve(l-center,I))));
		}
		cerr << l << " " << tmp << endl;
		ans = add(ans,mul(tmp,num));
	}
	cout << ans << endl;

	return 0;
}
