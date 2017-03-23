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
	copy(&D[0][0],&D[2][0],&C[0][0]);
}
 
void M_EXP(long long A[2][2],long long p){
	if(p == 0){
		copy(&I[0][0],&I[2][0],&A[0][0]);
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
 
vector<pi> get_primes(int K){
	vector<pi> ret;
	for(int i = 2;i*i <= K;i++){
		int tmp = 1;	
		for(;K%i == 0;K /= i) tmp *= i;
		if(tmp != 1) ret.pb(mp(i,tmp));
	}
	if(K > 1) ret.pb(mp(K,K));
	return ret;
}
 
bool is_zero(ll F0,ll F1,int p,int E,int n){
	//cerr << "in" << endl;
	//cerr << F0 << " " << F1 << " " << E << " " << p << endl;
	int ctr0 = 0,ctr1 = 0,ctr = 0;
	while(F0 && F0%p == 0) ctr0++,F0 /= p;
	while(F1 && F1%p == 0) ctr1++,F1 /= p;
	while(E && E%p == 0) ctr++,E /= p;
	ll u = 1,v = 1; int m = 1;
	bool ret;
	//cerr << ctr1 << " " << ctr0 << " " << ctr << endl;
	if(ctr1 + ctr0 == 0) ret = 0;
	else{
		while(ctr1*v + ctr0*u < ctr){
			m++;
			u += v;
			swap(u,v);
		}
		ret = n >= m;
	}
	//cerr << "out + ret = " << ret << endl;
	return ret;
}
int main(){
	int T;
	long long F0,F1,N,A,B,M[2][2];
	scanf("%d",&T);
	for(int t = 1;t <= T;t++){
		scanf("%lld %lld %lld %lld",&F0,&F1,&mod1,&N);
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
		else if(!F0 || !F1) A = 0;
		else{
			vector<pi> P = get_primes(mod1);
			ll ans = 0;
			loop(i,(int)sz(P)){
				if(is_zero(F0,F1,P[i].first,P[i].second,N-2)) continue;
				mod2 = P[i].second - P[i].second/P[i].first;
				M[0][0] = M[0][1] = 1;
				M[1][0] = 1;
				M[1][1] = 0;
				//cerr << "N = " << N << endl;
				M_EXP(M,N - 2);
				A = M[0][0];
				B = M[0][1];
				//cerr << "(" << F1 << "," << A << ")(" << F0 << "," << B <<")"<< endl;
				A = S_EXP(F1,A,P[i].second);
				B = S_EXP(F0,B,P[i].second);
				//cerr << A << " " << B << endl;
				A = (A * B)%mod1;
				//cerr << "A = " << A << endl;
				ans = (ans + A * (mod1/P[i].second)*S_EXP(mod1/P[i].second,P[i].second - P[i].second / P[i].first - 1,P[i].second))%mod1;
			}
			A = ans;
		}
		printf("Case #%d: %lld\n",t,A);
	}
	return 0;
}
