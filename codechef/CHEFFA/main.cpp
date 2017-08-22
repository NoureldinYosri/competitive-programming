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

const int mod = 1e9 + 7,MAX = 150 + 1;
int T,n;
int A[50 + MAX];
int dp[2][MAX][MAX];

int add(int a,int b){
	a += b;
	if(a >= mod) a -= mod;
	return a;
}

int solve(){
	int sum = n;
	for(int i = 0;i < n;i++) sum += A[i];
	memset(dp,0,sizeof dp);
	loop(i,2) loop(a,MAX) loop(b,MAX) assert(dp[i][a][b] == 0);
	int prv = 0,cur = 1;
	dp[0][A[0]][A[1]] = 1;
	for(int i = 1;i < sum;i++){
		loop(a,MAX) loop(b,MAX) dp[cur][a][b] = 0;
		for(int a = 0;a < MAX;a++)
			for(int b = 0;b < MAX;b++)
				if(dp[prv][a][b])
					for(int c = 0;c <= min(a,b);c++){
						if(c + A[i + 1] >= MAX) cerr << c + A[i + 1] << endl;
						assert(c + A[i + 1] < MAX);
						dp[cur][b - c][c + A[i+1]] = add(dp[cur][b - c][c + A[i+1]],dp[prv][a][b]);
					}
		//loop(a,MAX) loop(b,MAX) fprintf(stderr,"%d%c",dp[cur][a][b]," \n"[b==MAX-1]);
		//cerr << endl;
		prv ^= cur ^= prv ^= cur;
		bool done = 1;
		loop(a,MAX) loop(b,MAX) {
			if(!a && !b) continue;
			if(dp[prv][a][b]) done = 0;
		}
		if(done) break;
	}
	int ans = 0;
	loop(a,MAX) loop(b,MAX) ans = add(ans,dp[prv][a][b]);
	return ans;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&T);
	while(T--) {
		memset(A,0,sizeof A);
		scanf("%d",&n);
		loop(i,n) scanf("%d",A + i);
		printf("%d\n",solve());
		//break;
	}
	return 0;
}
