#pragma GCC optimize("O4")
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int oo = 1 << 28,MAX = 2010;


char S1[MAX],S2[MAX];
int n,m;
int nxt[MAX];
int dp[MAX][MAX];

int solve(int pos,int r){
	if(n - pos < r) return -oo;
	if(pos == n) return 0;
	if(nxt[pos] == -1) return 0;
	if(dp[pos][r] != -1) return dp[pos][r];
	int & ret = dp[pos][r];
	ret = solve(pos + 1,r);
	int len = nxt[pos] - pos - m;
	if(len <= r) ret = max(ret,1 + solve(nxt[pos],r - len));
	if(r) ret = max(ret,solve(pos + 1,r - 1));	
	return ret;
}

int main(){
	scanf("%s %s",S1,S2);
	n = strlen(S1),m = strlen(S2);
	for(int i = 0;i < n;i++){
		int j = i,k = 0;
		while(j < n && k < m) {
			if(S1[j] == S2[k]) k++;
			j++;
		}
		nxt[i] = (k == m) ? j : -1;
	}
	memset(dp,-1,sizeof dp);
	for(int del = 0;del <= n;del++)
		printf("%d%c",solve(0,del)," \n"[del == n]);
	return 0;
}
