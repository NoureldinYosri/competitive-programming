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
#define popcnt(x) __builtin_popcount(x)
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

double dp[100][100][3][3];
int X[100],Y[100],n;
int g[2];
double dist[100][100];
int who[100][100][3][3];

double solve(int lstl,int lstr,int take1,int take2){
	if(take1 == 1 && take2 == 1) return 1LL << 60;
	if(take1 == 2 && take2 == 2) return 1LL << 60;
	if(lstr == 1) return 1LL << 60;
	int cur = max(lstl,lstr) + 1;
	if(cur == n) return dist[lstl][lstr];
	double & ret = dp[lstl][lstr][take1][take2];
	if(ret == ret) return ret;
	ret = 1LL << 60;
	// give it to path A
	double t1 = solve(cur,lstr,(g[0] == cur) ? 1 : take1,(g[1] == cur) ? 1 : take2) + dist[cur][lstl];
	// give it to path B
	double t2 = solve(lstl,cur,(g[0] == cur) ? 2 : take1,(g[1] == cur) ? 2 : take2) + dist[cur][lstr];

	if(t1 < t2){
		ret = t1;
		who[lstl][lstr][take1][take2] = 1;
	}
	else{
		ret = t2;
		who[lstl][lstr][take1][take2] = 2;
	}


	return ret;
}

int main(){
	freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	for(int t = 1; scanf("%d %d %d",&n,g,g + 1) == 3 && !(n == 0 && g[0] == 0 && g[1] == 0);t++){
		loop(i,n) scanf("%d %d",X + i,Y + i);
		loop(i,n) loop(j,n) dist[i][j] = hypot(X[i] - X[j],Y[i] - Y[j]);
		memset(dp,-1,sizeof dp);
		printf("Case %d: %.2f\n",t,solve(0,0,0,0));
		vi pathA(1,0),pathB(1,0);
		int lstl = 0,lstr = 0,take1 = 0,take2 = 0;
		for(int cur = 1;cur < n;cur++){
			int c = who[lstl][lstr][take1][take2];
			if(c == 1) {
				pathA.pb(cur);
				lstl = cur;
				take1 = (cur == g[0]) ? 1 : take1;
				take2 = (cur == g[1]) ? 1 : take2;
			}
			else {
				assert(c == 2);
				pathB.pb(cur);
				lstr = cur;
				take1 = (cur == g[0]) ? 2 : take1;
				take2 = (cur == g[1]) ? 2 : take2;
			}
		}
		for(int x : pathA) printf("%d ",x);
		while(!pathB.empty()){
			int x = pathB.back(); pathB.pop_back();
			printf("%d%c",x," \n"[x == 0]);
		}
		print(pathA,int);
		print(pathB,int);
	}
	return 0;
}
