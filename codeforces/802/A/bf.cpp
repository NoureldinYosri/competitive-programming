/*
 * #pragma GCC optimize ("O3")
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

const int MAX = 400000 + 10;
int A[MAX],K,n;
vi dp[MAX];

int solve(int cur,int have){
	if(cur == n) return 0;
	if(dp[cur][have] != -1) return dp[cur][have];
	if(have & (1 << A[cur])) return solve(cur + 1,have);
	if(popcnt(have) < K) return dp[cur][have] = 1 + solve(cur + 1,have | (1 << A[cur]));
	int & ret = dp[cur][have];
	ret = 1 << 29;
	for(int thave = have;thave;thave ^= LSOne(thave)){
		int t = LSOne(thave);
		ret = min(ret,1 + solve(cur + 1,have ^ t ^ (1 << A[cur])));
	}
	return ret;
}

void read(){
	scanf("%d %d",&n,&K);
	loop(i,n) {
		scanf("%d",A + i);
		A[i]--;
	}
}

int solve(){
	fill(dp,dp + n,vi(1<<10,-1));
	return solve(0,0);
}

int main(){
	read();
	printf("%d\n",solve());
	return 0;
}
*/
