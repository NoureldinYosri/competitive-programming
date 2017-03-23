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
const int MAX = 1001;
int psi[MAX][51][MAX];
ll fact[MAX];
int phi[MAX][51];
int C[MAX << 1][MAX << 1];

int solve(int n,int k,int mx){
	if(!n) return k <= 1;
	if(n < 0) return 0;
	if(!k || !mx) return 0;
	if(psi[n][k][mx] != -1) return psi[n][k][mx];
	return psi[n][k][mx] = (solve(n,k,mx-1) + solve(n-mx,k-1,mx-1))%mod;
}

int get_psi(int n,int k){
	if(k > 50 || n < 0) return 0;
	return (solve(n,k,n)*fact[k])%mod;
}

int get_phi(int n,int k){
	if(k > 50) return 0;
	if(phi[n][k] != -1) return phi[n][k];	
	phi[n][k] = 0;
	loop(m,n+1){
		if(m+1 < k) continue;
		phi[n][k] += (C[m+1][m-k+1]*1LL*get_psi(n-m-1,k))%mod;
//		cerr << m << " " << C[m+1][m-k+1] << " " << get_psi(n-m-1,k) << endl;
		if(phi[n][k] >= mod) phi[n][k] -= mod;
	}
	return phi[n][k];
}

int main(){
	fact[0] = 1;
	loop(i,MAX-1) fact[i + 1] = ((i + 1LL)*fact[i])%mod;
	loop(n,(MAX << 1)){
		C[n][0] = C[n][n] = 1;
		range(k,1,n-1){
			C[n][k] = C[n-1][k] + C[n-1][k-1];
			if(C[n][k] >= mod) C[n][k] -= mod;
		}
	}	
	memset(psi,-1,sizeof psi);
	memset(phi,-1,sizeof phi);
	int T; scanf("%d",&T);
	while(T--){
		int n,k; scanf("%d %d",&n,&k);
		printf("%d\n",get_phi(n,k));
	}	
	return 0;
}
