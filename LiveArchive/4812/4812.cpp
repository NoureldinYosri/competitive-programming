#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

pi I[100];
int n,m;
ll dp[111][111][2];
const ll mod = 1e8;

bool cmp(const pi & u,const pi & v){
	return u.yy < v.yy;
}

int greedy(){
	if(I[n - 1].yy != m) return 0;
	int ret = 0,e = 0;
	loop(i,n){
		if(e == m) break;
		ret++;
		int j = i;
		while(j < n && I[j].xx <= e) j++;
		if(i == j) return 0;
		i = j - 1;
		e = I[i].yy;
	}
	return ret;
}

int main(){
	while(scanf("%d %d",&m,&n) == 2 && !(m == 0 && n == 0)){
		loop(i,n) scanf("%d %d",&I[i].xx,&I[i].yy);
		I[n++] = mp(0,0);
		sort(I,I + n,&cmp);
		int c = greedy(); cerr << c << endl;
		loop(i,n + 3) loop(j,n + 3) loop(k,2) dp[i][j][k] = 0;
		dp[0][0][1] = 1;
		loop(i,n){
			loop(k,i) loop(j,n + 1) {
				dp[i][j][0] = (dp[i][j][0] + dp[k][j][0] + dp[k][j][1])%mod;
			}
			loop(k,i) {
				if(!(I[k].xx <= I[i].xx && I[i].xx <= I[k].yy)) continue;
				loop(j,n){
					dp[i][j + 1][1] = (dp[i][j + 1][1] + dp[k][j][1])%mod;
				}
			}	
			loop(j,n + 1) cerr << dp[i][j][0] << " ";
			cerr << endl;
			loop(j,n + 1) cerr << dp[i][j][1] << " ";
			cerr << endl;
			cerr << endl;
		}
		int ans = (dp[n - 1][c][0] + dp[n - 1][c][1])%mod;
		if(I[n - 1].yy != m) ans = 0;
		printf("%d\n",ans);
	}
	return 0;
}		
