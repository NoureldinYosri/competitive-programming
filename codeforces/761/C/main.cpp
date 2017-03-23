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


const int oo = 1 << 27;
char str[50][100];
int n,m;
int cost[50][3];
int vis[50];
int dp[50][8];

int get_bit(char c){
	if(isdigit(c)) return 0;
	if(islower(c)) return 1;
	if(c == '#' || c == '*' || c == '&') return 2;
	return 3;
}

void get_cost(int s){
	loop(i,3) cost[s][i] = oo;
	loop(i,m) {
		int bit = get_bit(str[s][i]);
		if(bit <= 2){
			int c = min(i,m - i);
			cost[s][bit] = min(cost[s][bit],c);
		}
	}
}

int solve(int p,int msk){
	if(msk == 7) return 0;
	if(p == n) return oo;
	if(dp[p][msk] != -1) return dp[p][msk];
	int & ret = dp[p][msk]; dp[p][msk] = solve(p+1,msk);
	loop(i,3) ret = min(ret,solve(p + 1,msk | (1 << i)) + cost[p][i]);
	return ret;
}

int main(){
	scanf("%d %d",&n,&m);
	loop(i,n) {
		scanf("%s",str[i]);
		get_cost(i);
	}		
	memset(dp,-1,sizeof dp);
	cerr << solve(0,0) << endl;
	cout << solve(0,0) << endl;	
	return 0;
}
