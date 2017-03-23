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

char line[70];
int base;
int L;
int dp[70],len[70];

int solve(int p){
	if(p == L) return 0;
	if(dp[p] != -1) return dp[p];
	if(line[p] == '0') {
		len[p] = 1;	
		return 1 + solve(p+1);
	}
	int & ret = dp[p]; ret = 1000;
	ll dig = 0; 
	for(int q = p;q < L;q++){
		dig = dig*10 + line[q] - '0';
		if(dig >= base) break;
		if(solve(q + 1) < ret){
			ret = solve(q + 1);
			len[p] = q - p + 1;
		}
	}
	ret++;
	return ret;
}

int main(){
	cin >> base >> line;
	L = strlen(line);	
	memset(dp,-1,sizeof dp);
	cerr << solve(0) << endl;	
	int cur = 0;
	ll num = 0;
	while(cur < L){
		ll dig = 0;
		loop(i,len[cur]) dig = dig*10 + line[cur + i] - '0';
		num = num*base + dig;		
		cur += len[cur];
	}
	cout << num  << endl;
	return 0;
}
