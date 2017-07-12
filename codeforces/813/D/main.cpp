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


int n,A[5001];
int dp[5001][5001];
int f[5001][5001 + 5];
int g[5001][7];
int Q[5001][3];
int m;

int solve(int x,int y){
	if(x > y) return 0;
	if(dp[x][y] != -1) return dp[x][y];
	int & ret = dp[x][y]; ret = 0;
	for(int z = y + 1;z <= n;z++){
		if(!y || abs(A[y] - A[z]) <= 1 || A[y]%7 == A[z]%7)
			ret = max(ret,1 + solve(x,z));
		if(!x || abs(A[x] - A[z]) <= 1 || A[x]%7 == A[z]%7)
			ret = max(ret,1 + solve(y,z));
	}
	return ret;
}

int solve(){
	memset(g,-1,sizeof g);
	memset(f,-1,sizeof f);
	for(int x = n;x >= 0;x--){
		for(int y = n;y > x - (x == 0);y--){
			int & ret = dp[x][y]; ret = 0;
			if(!y) ret = max(ret,1 + *max_element(f[x],f[x] + m));
			else{
				range(d,-1,1) ret = max(ret,1 + f[x][Q[y][d + 1]]);
				ret = max(ret,1 + g[x][A[y]%7]);

			}
			if(!x) ret = max(ret,1 + *max_element(f[y],f[y] + m));
			else{
				range(d,-1,1) ret = max(ret,1 + f[y][Q[x][d + 1]]);
				ret = max(ret,1 + g[y][A[x]%7]);
			}
			g[x][A[y]%7] = max(g[x][A[y]%7],ret);
			f[x][Q[y][1]] = max(f[x][Q[y][1]],ret);
		}
	}
	/*range(x,0,n) {
		prArr(dp[x],n+1,int);
	}*/
	return dp[0][0];
}

void preprocess(){
	vi B(A + 1,A + n + 1);
	sort(all(B));
	B.resize(unique(all(B)) - B.begin());
	m = sz(B);
	range(i,1,n){
		int pos = lower_bound(all(B),A[i]) - B.begin();
		if(pos && B[pos - 1] == A[i] - 1) Q[i][0] = pos - 1;
		else Q[i][0] = sz(B);
		Q[i][1] = pos;
		if(pos + 1 < sz(B) && B[pos + 1] == A[i] + 1) Q[i][2] = pos + 1;
		else Q[i][2] = sz(B);
	}
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	cin >> n;
	range(i,1,n) cin >> A[i];
	preprocess();
	cout << solve() << endl;
	return 0;
}
