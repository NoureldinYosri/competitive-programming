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

const ll oo = 1LL << 60;
int A[3011],B[3011],n;
ll S[3011][3011];
ll dp[3011];

void preprocess(){
	for(int e = 1;e <= n;e++)
		range(i,1,n)
			S[e][i] = S[e][i-1] + abs(B[i] - e);
}



int solve(int pos){
	if(pos == n+1) return 0;
	if(dp[pos] != -1) return dp[pos];
	ll & ret = dp[pos];
	ret = oo;
	for(int nxt = pos;nxt <= n;nxt++){
		ret = min(ret,solve(nxt+1) + getCost(pos,nxt));
	}

	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	range(i,1,n) {
		scanf("%d",A + i);
		B[i] = A[i] + i;
	}
	preprocess();
	memset(dp,-1,sizeof dp);
	cout << solve(0) << endl;
	return 0;
}
