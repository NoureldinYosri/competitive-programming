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
int constraint[20][20];
int dp[20][20][20];
int n,m,k;

int add(int a,int b){
	a += b;
	if(a >= mod) a -= mod;
	return a;
}

int mul(int a,int b){
	return (a*1LL*b)%mod;
}


int solve(int s,int e,int bit){
	if(s > e || bit == n-1) return 1;
	int & ret = dp[s][e][bit];
	if(ret != -1) return ret;
	//cerr << s << " " << e << " " << bit << endl;
	ret = 0;
	int firstOne = -1,lstZero = -1;
/*	for(int i = s;i <= e;i++){
		if(constraint[i][bit] == 1) {
			firstOne = i;
			break;
		}
	}
	for(int i = s;i <= e;i++){
		if(constraint[i][bit] == 0) {
			lstZero = i;
		}
	}
*/
	for(int cntLeft = 0;cntLeft <= e - s + 1;cntLeft++){
		int nxt = s + cntLeft;
		ret = add(ret,mul(solve(0,nxt-1,bit + 1),solve(nxt,e,bit + 1)));
	}
	//cerr << s << " " << e << " " << bit << " " << ret << endl;
	return ret;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	memset(dp,-1,sizeof dp);
	memset(constraint,-1,sizeof constraint);
	/*scanf("%d %d %d",&n,&m,&k);
	loop(i,k){
		int a,b,c; scanf("%d %d %d",&a,&b,&c);
		a--,b--;
		constraint[a][b] = c;
	}
	printf("%d\n",solve(0,m-1,0));
	*/
	for(n = 1;n <= 5;n++,cerr << endl)
		for(m = 1;m <= n;m++){
			memset(dp,-1,sizeof dp);
			cerr << solve(0,m-1,0) << " ";
		}
	return 0;
}
