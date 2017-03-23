#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int oo = 0x3f3f3f3f;
int dist[20][20];
int n,m;
int dp [20][20][1 << 18];
int vis[20][20][1 << 18],vid;
int lookup[1 << 20];

int solve(int cur,int to,int msk){
	if(!msk) return dist[cur][to];
	if(vis[cur][to][msk] == vid) return dp[cur][to][msk];
	vis[cur][to][msk] = vid;
	int & ret = dp[cur][to][msk];
	ret = oo;
	int bit,t;
	for(int avail = msk;avail;avail ^= LSOne(avail)){
		bit = LSOne(avail);
		t = lookup[bit] + 1;
		ret = min(ret,solve(t,to,msk ^ bit) + dist[cur][t]);
	}
	return ret;
}

int solve(){
	if(n == 3) return 2*(dist[0][1] + dist[1][2]);
	vid++;
	int P[18] = {0},h = (n - 1)/2;
	fill(P + h,P + n - 2,1);
	int ans = oo;
	do{
		int msk[2] = {0};
		loop(i,n-2) msk[P[i]] |= 1 << i;
		int f1 = oo,f2 = oo,bit,to;
		for(int avail = msk[1];avail;avail ^= LSOne(avail)){
			bit = LSOne(avail);
			to = lookup[bit] + 1;
			f1 = min(f1,solve(0,to,msk[0]) + solve(to,n-1,msk[1] ^ bit));
			f2 = min(f2,solve(n-1,to,msk[0]) + solve(to,0,msk[1] ^ bit));
		}
		ans = min(ans,f1 + f2);
	}while(next_permutation(P,P + n - 2));
//	cerr << ans << endl;
	return ans;
}

int main(){
	loop(i,20) lookup[1 << i] = i;
	for(int t = 1;scanf("%d %d",&n,&m) == 2;t++){
		memset(dist,0x3f,sizeof dist);
		loop(i,n) dist[i][i] = 0;
		loop(i,m){
			int a,b,c; scanf("%d %d %d",&a,&b,&c);
			dist[a][b] = dist[b][a] = min(dist[b][a] , c);
		}
		loop(k,n) loop(i,n) loop(j,n) dist[i][j] = min(dist[i][j],dist[i][k] + dist[k][j]);
		printf("Case %d: %d\n",t,solve());
	}
	return 0;
}
