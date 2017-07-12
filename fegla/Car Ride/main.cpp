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
#define pl pair<ll,ll>
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

const int MAX = 1000;
int dp[MAX + 1][MAX + 1];
vi G[MAX + 1];

void init(){
	for(int i = 1;i <= MAX;i++)
		for(int j = i+1;j <= MAX;j++)
			if(__gcd(i,j) == 1)
				G[i].pb(j);
	for(int i = MAX;i > 0;i--){
		dp[i][i] = 1;
		for(int j = i+1;j <= MAX;j++)
			for(int k : G[i])
				dp[i][j] = max(dp[i][j],dp[k][j] + 1);
	}
}

int main(){
	freopen("car.in", "r", stdin);
	init();
	int T; scanf("%d",&T);
	while(T--){
		int S,N; scanf("%d %d",&S,&N);
		printf("%d\n",dp[S][N]);
	}
	return 0;
}
