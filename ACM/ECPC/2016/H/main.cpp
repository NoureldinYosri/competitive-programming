#pragma GCC optimize ("O3")
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


int A[11][11][11];
int dp[11][11][11];

int solve(int h,int x,int y) {
	if(!h || !x || !y || x == 11 || y == 11) return 0;
	int & ret = dp[h][x][y];
	if(ret != -1) return ret;
	ret = 0;
	ret = max(ret,solve(h-1,x,y));
	ret = max(ret,solve(h,x+1,y));
	ret = max(ret,solve(h,x,y+1));
	ret += A[h][x][y];
	return ret;
}

int main(){
	if(!freopen("commandos.in", "r", stdin)){
		cerr << "failed to opend file" << endl;
		exit(0);
	}
	int T; scanf("%d",&T);
	while(T--) {
		memset(A,0,sizeof A);
		memset(dp,-1,sizeof dp);
		int N; scanf("%d",&N);
		loop(i,N){
			int F,Y,X,H; scanf("%d %d %d %d",&F,&Y,&X,&H);
			A[F][X][Y] += H;
		}
		printf("%d\n",solve(10,1,1));
	}
	return 0;
}
