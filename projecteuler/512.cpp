#ifdef ACTIVE
#pragma GCC optimize ("O3")
#include <algorithm>
#include <iostream>
#include <cassert>
#define ll long long
using namespace std;

const int MAXN = 500*1000*1000;
int prime[MAXN + 1];
int phi[MAXN+1];

void sieve(){
	for(int i = 2;i <= MAXN;i++){
		if(!prime[i]) {
			prime[i] = i;
			for(ll j = i*(ll)i;j <= MAXN;j += i)
				prime[j] = i;
		}
	}
}

void compute_phi(){
	phi[1] = 1;
	for(int i = 2;i <= MAXN;i++){
		int u = i,p = prime[i],q = 1;
		while(u%p == 0) q *= p,u /= p;
		phi[i] = phi[u]*(q - q/p);
	}
}

int mul(int a,int b,int m) {
	return (a*(ll)b)%m;
}
int add(int a,int b,int m) {
	a += b;
	if(a >= m) a -= m;
	if(a < 0) a += m;
	return a;
}

int powmod(int a,int r,int m) {
	if(r == 0) return 1%m;
	int b = 1;
	for(;r > 1;r >>= 1) {
		if(r & 1) b = mul(a,b,m);
		a = mul(a,a,m);
	}
	return mul(a,b,m);
}


int get_sum(int r,int n,int mod,int depth,int *powers) {
	if(n == 0) return 1;
	if(n == 1) return add(1,r,mod);
	// assert(depth < ppp);
	int k = n/2;
	int g = get_sum(r,k,mod,depth + 1,powers);
	int u = powmod(r,k+1,mod);
	int v = powers[depth];
	v = mul(v,r,mod);
	assert(u == v);
	u = add(1,u,mod);
	int ret = mul(u,g,mod);
	if(n%2 == 0) ret = add(ret,powmod(r,n,mod),mod);
	return ret;
}


int get_sum(int n) {
	int powers[32];
	int E[32];
	int ppp;
	if(n == 1) return 1;
	ppp = 0;
	int qqq = 0;
	int N = n-1;
	while(N > 1) {
		N >>= 1;
		E[qqq++] = N;
	}

	if(qqq){
		if(E[qqq-1] == 0) powers[ppp++] = 1;
			else powers[ppp++] = n;

			int v = powers[ppp-1];
			int i = qqq - 2;
			while(qqq != ppp) {
				v = mul(v,v,n+1);
				if(E[i--]%2) v = mul(v,n,n+1);
				powers[ppp++] = v;
			}
			reverse(powers,powers + ppp);
//			print(E,int);
//			print(powers,int);

	}
	return get_sum(n,n-1,n+1,0,powers);
}

//int bf(int n) {
//	int m = n + 1;
//	int r = 0;
//	for(int k = 1;k <= n;k++) {
//		int t = powmod(n,k-1,m);
//		r = add(r,t,m);
////		if(k != 1) cerr << " + ";
////		cerr << t;
//	}
////	cerr << " = " << r << endl;
//	r = mul(r,phi[n],m);
//	return r;
//}

int main(int argc,char **argv){
	cerr << "sieving" << endl;
	sieve();
	cerr << "compute phi" << endl;
	compute_phi();
	cerr << "compute answer" << endl;
	ll res = 0;
	for(int i = 1;i <= MAXN;i += 2){
		// int g = get_sum(i);
		// int f = mul(phi[i],g,i+1);
		res += phi[i];
		// cerr << f << " " << phi[i] << endl;
		// if(i%10000000 == 0) cerr << "done with " << i << endl;
//		cerr << i << ": " << f << endl;
	}
	cout << res << endl;
	return 0;
}
#endif
