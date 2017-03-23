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

const int mod = 1e9 + 7;
char line[1024];
int A[128],n;
int dp[1024],L;


int get_max(int p){
	if(p == L) return 0;
	if(dp[p] != -1) return dp[p];
	int mn = INT_MAX;	
	dp[p] = 0;
	for(int j = p;j < L;j++){
		mn = min(mn,A[line[j]]);
		if(j - p + 1 > mn) break;
		dp[p] = max(dp[p],max(j-p+1,get_max(j+1)));
	}
	return dp[p];
}
int get_min(int p){
	if(p == L) return 0;
	if(dp[p] != -1) return dp[p];
	int mn = INT_MAX;	
	dp[p] = 1000000;
	for(int j = p;j < L;j++){
		mn = min(mn,A[line[j]]);
		if(j - p + 1 > mn) break;
		dp[p] = min(dp[p],get_min(j+1) + 1);
	}
	return dp[p];
}

int get_cnt(int p){
	if(p == L) return 1;
	if(dp[p] != -1) return dp[p];
	int mn = INT_MAX;	
	dp[p] = 0;
	for(int j = p;j < L;j++){
		mn = min(mn,A[line[j]]);
		if(j - p + 1 > mn) break;
		dp[p] += get_cnt(j+1);
		if(dp[p] >= mod) dp[p] -= mod;
	}
	return dp[p];
}

int main(){
	scanf("%d %s",&n,line);
	loop(i,26) scanf("%d",A + 'a' + i);
	L = strlen(line);
	memset(dp,-1,sizeof dp);
	int mx_len = get_max(0);	
	memset(dp,-1,sizeof dp);
	int mn_num = get_min(0);	
	memset(dp,-1,sizeof dp);
	int cnt = get_cnt(0);
	cout << cnt << endl;
	cout << mx_len << endl;
	cout << mn_num << endl;
	return 0;
}
