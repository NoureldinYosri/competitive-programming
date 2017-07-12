#pragma GCC optimize ("O3")
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
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcountll(x)
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

int lst[5010],start[5010],en[5010],val[5010];
int n,A[5010];
int dp[5010];

int solve(int s){
	if(s == n) return 0;
	if(dp[s] != -1) return dp[s];
	int & ret = dp[s];
	ret = solve(s + 1);
	if(start[A[s]] == s) ret = max(ret,val[s] + solve(en[s] + 1));
	return ret;
}


int main(){
	freopen("in.in","r",stdin);
	scanf("%d",&n);
	memset(start,-1,sizeof start);
	loop(i,n) {
		scanf("%d",A + i);
		lst[A[i]] = i;
		if(start[A[i]] == -1) start[A[i]] = i;
	}
	for(int i = n-1;i >= 0;i--){
		en[i] = i;
		for(int j = i;j <= lst[A[i]];j++)
			en[i] = max(en[i],en[j]);
		set<int> S;
		bool cond = 1;
		for(int j = i;j <= en[i];j++){
			if(start[A[j]] == j) S.insert(A[j]);
			else if(S.find(A[j]) == S.end()) cond = 0;
		}
		for(int x : S) val[i] ^= x;
		if(!cond) val[i] = -(1 << 28);
	}
	memset(dp,-1,sizeof dp);
	cout << solve(0) << endl;
	return 0;
}
