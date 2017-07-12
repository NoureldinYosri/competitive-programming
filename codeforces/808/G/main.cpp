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

const int MAX = 100*1000 + 10;
char T[MAX],P[MAX];
int pf[MAX];
int n,m;
vector<vi> dp;
int KMP[128][MAX];

int GetLen(char c,int l){
	if(KMP[c][l] != -1) return KMP[c][l];
	int & ret = KMP[c][l];
	while(l && P[l] != c) l = pf[l - 1];
	if(P[l] == c) l++;
	return ret = l;
}

void BuildFailure(){
	pf[0] = 0;
	range(i,1,n - 1) pf[i] = GetLen(P[i],pf[i - 1]);
}

int solve(int pos,int len){
	if(dp[pos][len] != -1) return dp[pos][len];
	if(pos == m) return len == n;
	if(len == n) return dp[pos][n] = 1 + solve(pos,pf[n-1]);
	if(T[pos] != '?') return dp[pos][len] = solve(pos + 1,GetLen(T[pos],len));
	dp[pos][len] = 0;
	for(char c = 'a';c <= 'z';c++)
		dp[pos][len] = max(dp[pos][len],solve(pos + 1,GetLen(c,len)));
	return dp[pos][len];
}


int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%s %s",T,P);
	n = strlen(P);
	m = strlen(T);
	memset(KMP,-1,sizeof KMP);
	BuildFailure();
	dp = vector<vi>(m+1,vi(n+1,-1));
	cout << solve(0,0) << endl;
	return 0;
}
