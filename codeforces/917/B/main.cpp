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

const int MAXV = 111,MAXE = MAXV*MAXV;
int fr[MAXE],to[MAXE],W[MAXE];
vi E[MAXV];
int n,m;
int dp[MAXV][MAXV][26];

int solve(int u,int v,int lst) {
	int & ret = dp[u][v][lst] ;
	if(ret != -1) return ret;
	ret = 0;
	for(int e : E[u]) if(W[e] >= lst){
		int t = to[e];
		if(!solve(v,t,W[e])) ret = 1;
	}
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	loop(e,m) {
		char c;
		scanf("%d %d %c",fr + e,to + e,&c);
		E[fr[e]].pb(e);
		W[e] = c - 'a';
	}
	memset(dp,-1,sizeof dp);
	for(int u = 1;u <= n;u++,puts(""))
		for(int v = 1;v <= n;v++)
			putchar("BA"[solve(u,v,0)]);`
	return 0;
}
