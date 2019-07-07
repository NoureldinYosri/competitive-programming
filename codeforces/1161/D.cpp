#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;


const int mod = 998244353 ;
int dp[1024][2][2];
char S[1024];
int m;

int add(ll a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}

bool isPal(int len) {
	loop(i,len) {
		char a = S[i],b = S[m-1-i];
		if(a == b) continue;
		if(a == '?' || b == '?') continue;
		return 0;
	}
	return 1;
}

int F[1024];
int target[1024];

int parse(char c){
	if(c == '0') return 0;
	if(c == '1') return 1;
	return -1;
}

int solve(int len) {
	int n = m-len;
	if(n == 0) return 1;
	for(int i = 0;i < m;i++) {
		F[i] = -1;
		if(i < len) F[i] = target[i];
		if(i >= m-len) F[i] = target[i];
	}
	for(int i = 0;i < len;i++) {
		int j = m-1-i;
		if(F[i] == -1) F[i] = F[j];
		if(F[j] == -1) F[j] = F[i];
		if(F[i] != F[j]) return 0;
	}


	return ret;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%s",S);
	m = strlen(S);
	loop(i,m) target[i] = parse(S[i]);
	int ans = 0;
	for(int len = 0;len <= m;len++) {
		if(!isPal(len)) continue;
		ans = add(ans,solve(len));
	}

	cout << ans << endl;
	return 0;
}
