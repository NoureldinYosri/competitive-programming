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

const int MAX = 1e5 + 1e2;
int G[3][MAX];
int vis[MAX],n;
ll dp[3][MAX];
int dfs_vis[3][MAX];
int dx[] = {0,-1,0,1},dy[] = {-1,0,1,0};

#define get(row,col) ((col < 0) ? ((row == 0 && col == -1) ? 0 : (-1LL << 60)) : dp[row][col])




void dfs(int row,int col,int l,int r,ll v){
	if(col < l || r < col) return;
	if(row < 0 || row == 3) return;	
	if(dfs_vis[row][col]) return;
	dfs_vis[row][col] = 1;
	v += G[row][col];
	if(col == r) dp[row][col] = max(dp[row][col],v);
	loop(i,4) {
		if(row + dx[i] < 0 || row + dx[i] > 2 || col + dy[i] < l || col + dy[i] > r) continue;	
		dfs(row + dx[i],col + dy[i],l,r,v);
	}
	dfs_vis[row][col] = 0;
}


int main(){
	scanf("%d",&n);
	loop(i,3) loop(j,n) scanf("%d",&G[i][j]);
	loop(col,n){
		loop(i,3) dp[i][col] = -(1LL << 60);
		loop(i,min(3,col+1)){
			loop(j,3) dfs(j,col-i,col-i,col,get(j,col-i-1));
		}
	}	
	cerr << dp[2][n-1] << endl;
	cout << dp[2][n-1] << endl;
		
	return 0;
}
