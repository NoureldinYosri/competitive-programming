#ifndef __my_math
#define __my_math
#include <vector>
#include <iostream>

const double NaN = nan("");
typedef long long int64;


int64 add64(int64 a,int64 b,int64 m) {
	a += b;
	if(a >= m) a -= m;
	if(a < 0) a += m;
	return a;
}

int mul(int a,int b,int m) {
	return (a*(int64)b)%m;
}

int64 mul64(int64 a,int64 b,int64 m) {
	if(m <= INT_MAX) {
		a %= m,b %= m;
		return mul(a,b,m);
	}
	if(a <= LLONG_MAX/b) return (a*b)%m;
	if(a > b) {
		int64 c = a;
		a = b;
		b = c;
	}
	int64 res = mul64(a,b >> 1,m);
	res = add64(res,res,m);
	if(b & 1) res = add64(res,a,m);
	return res;
}


int add(int a,int b,int m) {
	a += b;
	if(a >= m) a -= m;
	if(a < 0) a += m;
	return a;
}


bool is_square(long long x) {
	long long u = sqrt(x) + 3;
	while(u*u > x) u--;
	return u*u == x;
}

int64 gcd(int64 a,int64 b) {
	a = abs(a),b = abs(b);
	while(b) {
		int64 t = a%b;
		a = b;
		b = t;
	}
	return a;
}
int64 lcm(int64 a,int64 b) {
	return a*(b/gcd(a,b));
}

int64 powmod(int64 a,int64 r,int64 m) {
	if(r == 0) return 1%m;
	int64 b = 1;
	while(r > 1) {
		if(r & 1) b = mul64(a,b,m);
		a = mul64(a,a,m);
		r >>= 1;
	}
	return mul64(a,b,m);
}

bool isProbablePrime(int64 x,int cnt = 20) {
	static std::vector<int> smallPrimes {2,3,5,7,11,13};
	if(x <= 1) return 0;
	for(int p : smallPrimes){
		if(p == x) return 1;
		if(x%p == 0) return 0;
	}

	for(int i = 0;i < cnt;i++) {
		int64 y = rand()%(x - 1) + 1;
		if(gcd(x,y) != 1) return 0;
		int64 t = powmod(y,x-1,x);
		if(t != 1) return 0;
	}
	return 1;
}

int Cipolla(int n,int p) {
	assert(0);
	int a,m;
	do{
		a = rand()%p;
		m = mul(a,a,p);
		m = add(m,-n,p);
	}while(is_square(m));
	return 0;
}


void sieve(int MAXN,int *prime){
	for(int i = 2;i <= MAXN;i++){
		if(!prime[i]) {
			prime[i] = i;
			for(long long j = i*(long long)i;j <= MAXN;j += i)
				prime[j] = i;
		}
	}
}


#endif
