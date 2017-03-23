#include <bits/stdc++.h>
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

const int mod = 1e9 + 7;

int add(int x,int y){
	x += y;
	if(x >= mod) x -= mod;
	if(x < 0) x += mod;
	return x;
}

int mul(int x,int y){
	return (x * 1LL * y)%mod;
}

int C[4001][4001];
int f[4001],g[4001],n;

int main(){
	cin >> n;
	loop(i,n+1){
		C[i][0] = C[i][i] = 1;
		for(int j = 1;j < i;j++)
			C[i][j] = add(C[i - 1][j],C[i - 1][j - 1]);
	}
	f[0] = g[0] = 1;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= i;j++) f[i] = add(f[i],mul(f[i-j],C[i-1][j-1]));
		g[i] = g[i - 1];
		for(int j = 1;j <= i;j++) g[i] = add(g[i],mul(g[i-j],C[i-1][j-1]));
	}

	printf("%d\n",add(g[n],-f[n]));
	return 0;
}
