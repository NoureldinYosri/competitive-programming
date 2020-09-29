#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
using ll = long long;

ll solve(ll a, ll b){
	ll ret = 0, tmp;
	while(a){
//		printf("%lld %lld\n", a, b);
		if(a > 0) {
			ret++;
			tmp = a;
			a = b;
			b = tmp;
			a *= -1;
		}
		a = -a;
		ll d = (a + b - 1)/b;
		ret += d;
		a = d*b - a;
	}
	return ret;
}

ll solve_fast(ll a, ll b){	
	ll ret = 0, tmp;
	while(a){
		//printf("%lld %lld\n", a, b);
		if(a > 0) {
			ret++;
			tmp = a;
			a = b;
			b = tmp;
			a *= -1;
		}
		a = -a;
		if(a%b == 0){
			ret += a/b;
			break;
		}

		if(a > b){
			ll diff = a - b;
			ll ca = a/diff, cb = b/diff;
			ll steps = min(ca, cb);
			steps = max(steps - 1, 0LL);
			ret += 2*steps + max(steps-1, 0LL);
			a -= steps*diff;
			b -= steps*diff;
			if(steps) {
				swap(a, b);
				continue;
			}
		}
	
		ret += a/b;
		a = a%b;
		
		if(!a) break;
		
		a = b - a;
		ret ++;
		
//		ret += b/a;
//		a = b%a;
	}
	return ret;
}

void test(){
	for(int t = 0; t < 1000; t++){
		int a = 2*rand()%1001 - 500;
		int b = rand()%1000 + 1;
		if(solve(a, b) != solve_fast(a, b)){
			cerr << "failed on " << a << " " << b << endl;
			exit(0);
		}
	}
	cerr << "AC :)" << endl;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		ll a, b; scanf("%lld %lld", &a, &b);
		printf("%lld\n", solve_fast(a, b)%mod);
	}

	return 0;
}
