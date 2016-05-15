#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
using namespace std;
 
long long mod1,mod2;
 
long long I[2][2] = {{1,0},{0,1}};
 
void multiply(long long A[2][2],long long B[2][2],long long C[2][2]){
	long long D[2][2] = {{0,0},{0,0}};
	for(int i = 0;i < 2;i++)
		for(int j = 0;j < 2;j++)
			for(int k = 0;k < 2;k++)
				D[i][j] = (D[i][j] + A[i][k]*B[k][j])%mod2;
	copy(&D[0],&D[2],&C[0]);
}
 
void M_EXP(long long A[2][2],long long p){
	if(p == 0){
		copy(&I[0],&I[2],&A[0]);
		return;
	}
	if(p == 1) return;
	long long B[2][2];
	multiply(A,A,B);
	M_EXP(B,p/2);
	if(p%2)
		multiply(A,B,A);
	else
		multiply(I,B,A);
}
 
long long S_EXP(long long b,long long p,int mod){
	if(p == 0) return 1;
	else if(p == 1) return b%mod;
	return (S_EXP((b*b)%mod,p >> 1,mod) * S_EXP(b,p & 1,mod))%mod;
}
 

void get_loop(ll f,int K,int & u,int & l){
	vi V(K,-1);
	int t = 1; u = f%K;
	while(V[u] == -1){
		V[u] = t++;
		u = (u * f)%K;
	}
	l = t - V[u];
	u = V[u];
}
 
int main(){
	int T;
	long long F0,F1,N,A,B,M[2][2];
	scanf("%d",&T);
	for(int t = 1;t <= T;t++){
		scanf("%lld %lld %lld %lld",&F0,&F1,&mod1,&N);
		ll n = N;
		if(N == 1) {
			A = 1 - (B = 1);
			A = S_EXP(F1,A,mod1);
			B = S_EXP(F0,B,mod1);
			A = (A * B)%mod1;
		}
		else if(N == 2) {
			A = 1 - (B = 0);
			A = S_EXP(F1,A,mod1);
			B = S_EXP(F0,B,mod1);	
			A = (A * B)%mod1;
		}
		else if(F0%mod1 == 0 || F1%mod1 == 0){
			A = 0;
		}
		else{
			int u0,v0,u1,v1;
			get_loop(F0,mod1,u0,v0);
			get_loop(F1,mod1,u1,v1);
			cerr << n - 2 << " " << u0 << " " << u1 << " " << v0 << " " << v1 << endl;
			if(n - 2 <= u0){
				A = 1;
				loop(i,n - 2) A = (A * F0)%mod1;
			}
			else{
				loop(i,2) loop(j,2) M[i][j] = 1;
				M[1][1] = 0;
				mod2 = v0;
				M_EXP(M,n - 2);
				A = M[0][0];
				A -= u0;
				A = (A%v0 + v0)%v0;
				A = S_EXP(F0,A,mod1);
			}
			if(n - 2 <= v0){
				B = 1;
				loop(i,n - 2) B = (B * F1)%mod1;
			}
			else{
				loop(i,2) loop(j,2) M[i][j] = 1;
				M[1][1] = 0;
				mod2 = v1;
				M_EXP(M,n - 2);
				B = M[0][0];
				B -= u1;
				B = (A%v1 + v1)%v0;
				B = S_EXP(F1,B,mod1);
			}
			A = (A*B)%mod1;
		}
		printf("Case #%d: %lld\n",t,A);
	}
	return 0;
} 
 


