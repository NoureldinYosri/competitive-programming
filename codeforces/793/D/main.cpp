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

const int oo = 1 << 29;
vp G[81];
int dp[81][81][2][81];
int n,m,K;


int solve(int s,int e,int pos,int k){
	if(k == 0) return 0;
	if(e < s || s == e) return oo;
	if(dp[s][e][pos][k] != -1) return dp[s][e][pos][k];
	int & ret = dp[s][e][pos][k];
	ret = oo;
	int u = pos ? e : s;
	for(auto E : G[u]){
		int v = E.xx,c = E.yy;
		if(s <= v && v <= e){
			int ns,ne,npos;
			if(u < v) ns = v,ne = e,npos = 0;
			else ns = s,ne = v,npos = 1;
			ret = min(ret,c + solve(ns,ne,npos,k - 1));
			if(u < v) ns = s + 1,ne = v,npos = 1;
			else ns = v,ne = e - 1,npos = 0;
			ret = min(ret,c + solve(ns,ne,npos,k - 1));
		}
	}
	return ret;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	scanf("%d %d %d",&n,&K,&m);
	loop(i,m) {
		int u,v,c; scanf("%d %d %d",&u,&v,&c);
		assert (u != v);
		G[u].pb(mp(v,c));
	}
	range(u,1,n){
		vp tmp ;
		sort(all(G[u]));
		for(int i = 0,L = sz(G[u]);i < L;){
			tmp.pb(G[u][i]);
			int j = i;
			while(j < L && G[u][i].xx == G[u][j].xx) j++;
			i = j;
		}
		G[u] = tmp;
	}
	memset(dp,-1,sizeof dp);
	int ans = oo;
	range(i,1,n){
		int tmp = min(solve(i,n,0,K-1),solve(1,i,1,K-1));
		if(tmp < oo) ans = min(ans,tmp);
	}
	if(ans >= oo) ans = -1;
	cout << ans << endl;
	cerr << ans << endl;

	return 0;
}
