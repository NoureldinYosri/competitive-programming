#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

vi G[1 << 20];

int vis[1 << 20][2];
pl dp[1 << 20][2];

pl solve(int u,int p,int c){
	if(vis[u][c]) return dp[u][c];
	vis[u][c] = 1;
	dp[u][c] = mp(c + 0LL,1LL);
	for(int v : G[u])
		if(v != p){
			pl tmp;			
			if(c)	 {
				tmp = solve(v,u,0);
				pl tmp1 = solve(v,u,1);
				if(tmp.xx == tmp1.xx) tmp.yy += tmp1.yy;
				else if(tmp1.xx < tmp.xx) tmp = tmp1;
			}
			else tmp = solve(v,u,1);
			dp[u][c].xx += tmp.xx;
			dp[u][c].yy *= tmp.yy;
			dp[u][c].yy %= 10007;
		}
	return dp[u][c];
}

int main(){
	int n,a,b;
	scanf("%d",&n);
	loop(i,n - 1){
		scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	auto tmp = solve(1,0,0);
	auto tmp1 = solve(1,0,1);
	//prp(tmp);
	//prp(tmp1);	
	if(tmp.xx == tmp1.xx) tmp.yy += tmp1.yy;
	else if(tmp1.xx < tmp.xx) tmp = tmp1;
	tmp.yy %= 10007;
	cout << tmp.xx << " " << tmp.yy << endl;
	prp(tmp);		
	return 0;
}
