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

int dp[1 << 20],n,s,l;
int A[1 << 20],lg[1 << 20];
int sparse[1 << 20][20][2];

int value(int s,int e){
	int l = lg[e - s + 1];
	int other = e - (1 << l) + 1;
	int mx = max(sparse[s][l][1],sparse[other][l][1]);
	int mn = min(sparse[s][l][0],sparse[other][l][0]);
	return mx - mn;
}

void init(){
	fill(dp,dp + n,-1);	
	range(i,1,n){
		lg[i] = lg[i - 1];
		if(i == LSOne(i) && i != 1) lg[i]++;
	}
	loop(i,n) sparse[i][0][0] = sparse[i][0][1] = A[i];
	loop(k,19){
		loop(i,n){
			sparse[i][k + 1][0] = sparse[i][k][0];
			sparse[i][k + 1][1] = sparse[i][k][1];
			if(i + (1 << k) < n){
				sparse[i][k + 1][0] = min(sparse[i][k][0],sparse[i + (1 << k)][k][0]);
				sparse[i][k + 1][1] = max(sparse[i][k][1],sparse[i + (1 << k)][k][1]);
			}
		}
	}
}


int solve(){
	deque<int> cand;
	cand.pb(n);	
	for(int i = n - 1;i >= 0;i--){
		while(!cand.empty() && value(i,cand.front() - 1) > s) cand.pop_front();
		if(cand.empty() || cand.front() - i < l) {
			dp[i] = 1 << 29;
			continue;
		}
		dp[i] = dp[cand.front()] + 1;
		while(!cand.empty() && dp[cand.back()] > dp[i]) cand.pop_back();
		cand.push_back(i);		
	}
	return (dp[0] == (1 << 29)) ? -1 : dp[0];
}

int main(){
	scanf("%d %d %d",&n,&s,&l);
	loop(i,n) scanf("%d",A + i);
	init();
	printf("%d\n",solve());
	return 0;
}
