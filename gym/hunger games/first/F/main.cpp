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

const int MAX = 1e5 + 1e2;
const int mod = 1e9 + 7;
int n;
vi E[MAX];
int fr[MAX],to[MAX];
ll A[MAX];
int L[MAX],R[MAX],LIM[MAX],ord[MAX];
ll mx[MAX],cnt[MAX];

int dfs(int u,int p){
	int siz = 1;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v != p) {
			int x = dfs(v,u);
			A[e] = x*(n - x + 0LL);
			siz += x;
		}
	}
	return siz;
}

unordered_map<int,int> dp[MAX];


int solve(int pos,int k){
	if(!k) return 1;
	if(pos == n) return 1;
	if(mx[pos] <= k) return cnt[pos];
	if(A[ord[pos]] > k){
		if(A[ord[n-1]] > k) return 1;
		int s = pos+1,e = n-1;
		while(s < e){
			int m = (s + e) >> 1;
			if(A[ord[m]] <= k) e = m;
			else s = m + 1;
		}
		return solve(s,k);
	}
	if(dp[pos].find(k) != dp[pos].end()) return dp[pos][k];
	int ret = 0;
	for(int i = 0,who = ord[pos],lim = LIM[who];i <= lim && i*A[who] <= k;i++){
		ret += solve(pos + 1,k - i*A[who]);
		if(ret >= mod) ret -= mod;
	}
	dp[pos][k] = ret;
	return ret;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
		freopen("out.out", "w", stdout);
	#endif
	int k; scanf("%d %d",&n,&k);
	loop(i,n-1){
		int a,b; scanf("%d %d %d %d",&a,&b,L + i,R + i);
		fr[i] = a; to[i] = b;
		E[a].pb(i);
		E[b].pb(i);
	}
	dfs(1,0);
	n--;
	ll tot = 0;
	loop(i,n) tot += A[i] * L[i];
	if(tot > k){
		puts("0");
		return 0;
	}
	k -= tot;
	loop(i,n) LIM[i] = R[i] - L[i],ord[i] = i;
	sort(ord,ord + n,[](const int & a,const int & b){
		return A[a] > A[b];
	});
	mx[n] = 0;
	cnt[n] = 1;
	for(int j = n-1;j >= 0;j--){
		int i = ord[j];
		mx[j] = mx[j + 1] + A[i]*LIM[i];
		cnt[j] = (cnt[j + 1] * (LIM[i] + 1))%mod;;
	}
	cout << solve(0,k) << endl;
	return 0;
}
