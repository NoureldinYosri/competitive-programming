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

const int MAX = 100*1000 + 10;
ll oo = 1LL << 60;
int A[MAX],n,K;
ll dp[21][MAX];
ll pref[MAX],suff[MAX];
int cnt[MAX];



void preprocess() {
	range(i,1,2*n) {
		pref[i] = pref[i - 1] + cnt[A[i]];
		cnt[A[i]]++;
	}
	memset(cnt,0,sizeof cnt);
	for(int i = n;i >= 1;i--){
		suff[i] = suff[i + 1] + cnt[A[i]];
		cnt[A[i]]++;
	}
}

//abca
//pref[l-1] = a^2
//suff[r+1] = c^2
//pref[r] = a^2 + b^2 + ab
//suff[l] = b^2 + bc + c^2
//tot = a^2 + b^2 + c^2 + ab + bc + ac
//suff2[r+1] = tot + ac + bc + c^2
//pref[n+l-1] = tot + a^2 + ab + ac
//suff2[r+1] + pref[n + l - 1] - 2*tot = a^2 + c^2 + 2*ac + ab + bc

ll get_cost(int l,int r) {
	ll A = pref[n + l - 1] - pref[r];
	ll B = pref[r] + suff[l];
	ll tot = pref[n];
	return A + B - tot - pref[l-1] - suff[r+1];
}

void solve(int s,int e,int l,int r,int k) {
	if(s > e) return;

	int optPos = l,m = (s + e) >> 1;
	ll optVal = oo,cost;

	for(int cut = min(m,r);cut >= l;cut--) {
		cost = get_cost(cut,m);
		cerr << cut << " " << m << " -> " << cost << endl;
		ll tmp = cost + dp[k-1][cut-1];
		if(tmp < optVal) {
			optVal = tmp;
			optPos = cut;
		}
	}

	dp[k][m] = optVal;
	solve(s,m-1,l,optPos,k);
	solve(m+1,e,optPos,r,k);
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&K);
	range(i,1,n) scanf("%d",A + i);
	preprocess();
/*	fill(dp[0],dp[1],oo);
	dp[0][0] = 0;
	for(int k = 1;k <= K;k++){
		solve(1,n,1,n,k);
//		prArr(dp[k],n+1,ll);
	}
	cout << dp[K][n] << endl;
*/
/*	range(i,1,n)
		range(j,i,n)
			cout << i << " " <<
*/
	cout << get_cost(1,1) << endl;
	return 0;
}
