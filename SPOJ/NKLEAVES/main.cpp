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

const ll oo = 1LL << 60;
const int MAX = 100001;
ll sum[MAX],w_sum[MAX],A[MAX];
ll dp[2][MAX];

void solve(int i,int jleft,int jright,int kleft,int kright,ll *cur,ll *prv){
	if(jleft > jright) return;
	int jmid = (jleft + jright) >> 1;
	int best_k = kleft;
	ll best_val = oo;
	for(int k = kleft;k <= kright && k < jmid;k++){
		ll val = prv[k] + w_sum[jmid] - w_sum[k] - (sum[jmid] - sum[k])*(k + 1);
		if(val < best_val){
			best_val = val;
			best_k = k;
		}
	}
	cur[jmid] = best_val;
	solve(i,jleft,jmid - 1,kleft,best_k,cur,prv);
	solve(i,jmid + 1,jright,best_k,kright,cur,prv);
}

int main(){
	int n,k; 
	scanf("%d %d",&n,&k);
	range(i,1,n) {
		scanf("%lld",A + i);
		sum[i] = sum[i - 1] + A[i];
		w_sum[i] = w_sum[i - 1] + A[i]*i;
	}		
	fill(dp[0] + 1,dp[1],oo);
	int one = 1,other = 0;
	for(int i = 1;i <= k;i++){
		solve(i,i,n,0,n,dp[one],dp[other]);
		swap(one,other);
	}
	//cerr << dp[other][n] << endl;
	cout << dp[other][n] << endl;
	return 0;
}
