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
#define popcnt(x) __builtin_popcount(x)
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

const int MAX = 100*1000 + 10,MAXN = 111;
char P[MAX];
int pf[MAX];
ll dp[MAXN];
int pref[MAXN],suff[MAXN];
int cross[2][2];
int L;

void generate(string & u,string & v,int & n){
	u = "0",v = "1",n = 0;
	while(sz(u) < L) {
		u = v + u;
		u.swap(v);
		n++;
	}
}

int get_len(char c,int l){
	while(l && P[l] != c) l = pf[l - 1];
	if(P[l] == c) l++;
	return l;
}

void build_failure(){
	pf[0] = 0;
	range(i,1,L - 1) pf[i] = get_len(P[i],pf[i - 1]);
}


int match(string T){
	int len = 0,ret = 0;
	for(char c : T){
		len = get_len(c,len);
		if(len == L){
			ret++;
			len = pf[L - 1];
		}
	}
	return ret;
}

void preprocess(){
	memset(dp,-1,sizeof dp);
	L = strlen(P);
	string u,v; int n;
	generate(u,v,n);
	build_failure();

	dp[n] = match(u);
	dp[n + 1] = match(v);
	pref[n] = suff[n] = 0;
	pref[n + 1] = suff[n + 1] = 1;

	cross[0][0] = match(u + u) - 2*dp[n];
	cross[0][1] = match(u + v) - dp[n] - dp[n + 1];
	cross[1][0] = match(v + u) - dp[n] - dp[n + 1];
	cross[1][1] = match(v + v) - 2*dp[n + 1];

	fill(dp,dp + n,0);
}

ll solve(int n){
	if(dp[n] != -1) return dp[n];
	dp[n] = solve(n - 1) + solve(n - 2);
	dp[n] += cross[suff[n - 1]][pref[n - 2]];
	pref[n] = pref[n - 1];
	suff[n] = suff[n - 2];
	return dp[n];
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
	#endif
	for(int N,t = 1;scanf("%d %s",&N,P) == 2;t++){
		preprocess();
		printf("Case %d: %lld\n",t,solve(N));
	}
	return 0;
}
