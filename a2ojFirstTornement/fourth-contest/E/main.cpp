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

const int MAX = 300*1000 + 10;
int n,m,k;
int A[MAX],B[MAX],C[MAX],IDX[MAX];
ll ST[MAX*4],LA[MAX*4];
ll ST2[MAX*4],LA2[MAX*4];
ll dp[MAX];
vector<vl> P;

void clear(int node,int s,int e,ll *ST,ll *LA) {
	ST[node] = 0;
	LA[node] = 0;
	if(s == e) {
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	clear(left,s,m,ST,LA);
	clear(right,m+1,e,ST,LA);
}

void update(int node,int s,int e,int l,int r,ll val,ll *ST,ll *LA) {
	if(l <= s && e <= r) {
		LA[node] = max(LA[node],val);
		ST[node] = max(ST[node],val);
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) update(left,s,m,l,r,val,ST,LA);
	else if(m < l) update(right,m+1,e,l,r,val,ST,LA);
	else {
		update(left,s,m,l,m,val,ST,LA);
		update(right,m+1,e,m+1,r,val,ST,LA);
	}
	ST[node] = max(LA[node],max(ST[right],ST[left]));
}

ll query(int node,int s,int e,int l,int r,ll *ST,ll *LA) {
	if(l <= s && e <= r) return ST[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	ll ret = 0;
	if(r <= m) ret = query(left,s,m,l,r,ST,LA);
	else if(m < l) ret = query(right,m+1,e,l,r,ST,LA);
	else ret = max(query(left,s,m,l,m,ST,LA),query(right,m+1,e,m+1,r,ST,LA));
	ret = max(ret,LA[node]);
	return ret;
}

void brute_force(int d,vi Path,int score = 0){
	if(d == m) {
		cerr << "with score " << score << " ";
		print(Path,int);
		return;
	}
	range(i,1,n) {
		Path.pb(i);
		brute_force(d+1,Path,score + P[d][i-1]);
		Path.pop_back();
	}
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d %d",&n,&m,&k);
	P = vector<vl> (m,vl(n+1));
	loop(i,m) {
		range(j,1,n) scanf("%lld",&P[i][j]);
//		print(P[i],int);
	}
	memset(IDX,-1,sizeof IDX);
	loop(i,k) {
		scanf("%d %d %d",A + i,B + i,C + i);
		IDX[C[i]] = i;
	}
//	brute_force(0,vi());
//	return 0;
	for(int d = m-1;d >= 0;d--) {
		for(int i = 1;i <= n;i++){
			dp[i] = max(dp[i],query(1,1,n,i,i,ST2,LA2));
			if(IDX[i] != -1){
				int j = IDX[i];
				dp[i] = max(dp[i],query(1,1,n,A[j],B[j],ST,LA));
			}
//			cerr << dp[i] << " ";
			dp[i] += P[d][i];
		}
//		cerr << endl;
		//update
		clear(1,1,n,ST,LA);
		clear(1,1,n,ST2,LA2);
		for(int i = 1;i <= n;i++){
			update(1,1,n,i,i,dp[i],ST,LA);
//			cerr << i << " updates itself with " << dp[i] << endl;
			if(IDX[i] != -1){
				int j = IDX[i];
//				cerr << i << " updates " << A[j] << " to " << B[j] << " with " << dp[i] << endl;
				update(1,1,n,A[j],B[j],dp[i],ST2,LA2);
			}
		}
//		prArr(dp+1,n,ll);
	}
	ll ans = 0;
	range(j,1,n) ans = max(ans,dp[j]);
	cout << ans << endl;
	return 0;
}
