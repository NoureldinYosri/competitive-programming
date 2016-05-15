#include <queue>
#include <cstdio>
#include <cmath>
#define ll long long

const ll mod = 1e9 + 7;
inline ll pmod(ll b,ll p){
	if(p == 0) return 1;
	ll ret = b,tmp = 1;
	while(p > 1){
		if(p & 1) tmp = (tmp * ret)%mod;
		ret = (ret * ret)%mod;
		p >>= 1;
	}	
	ret = (ret * tmp)%mod;
	return ret;
}

ll Y[1 << 20];

ll sumk(ll n,ll k){
	if(n <= k + 1) return Y[n];
	ll A = 1,B = 1;
	queue<ll> q;
	for(ll i = 0;i <= k + 1;i++) A = (A*(n - i)) % mod;
	for(ll i = k + 1;i;i--) {
		B = (B * (mod-i))%mod;
		q.push(mod-i);	
	}
	ll ans = 0;
	for(ll i = 0;i <= k + 1;i++){
		ll a = A * pmod(n - i,mod - 2);
		a %= mod;
		a = (a * pmod(B,mod - 2))%mod;
		ans = (ans + a *Y[i])%mod;
		B = (B * pmod(q.front(),mod - 2))%mod;
		q.pop();
		q.push(i + 1);
		B = (B * (i + 1))%mod;
	}
	return ans;	
}

ll f(ll n,ll k){
	ll u = sqrt(n) + 5;
	while(u * u > n) u--;
	ll ans = 0;
	for(ll i = 1;i <= u;i++){
		ll tmp = pmod(i,k)*(n/i - u); tmp %= mod;
		ans += tmp + sumk(n/i,k);
		while(ans >= mod) ans -= mod;
		while(ans < 0) ans += mod;
	}
	return ans;
}

int main(){
	int T;	
	ll a,b,k;
	scanf("%d",&T);
	while(T--){
		scanf("%lld %lld %lld",&a,&b,&k);	
		for(ll i = 1;i <= k + 1;i++) 
			Y[i] = (Y[i - 1] + pmod(i,k))%mod;
		ll ans = f(b,k) - f(a - 1,k);
		ans = (ans%mod + mod)%mod;
		printf("%lld\n",ans);	
	}
	return 0;
}	

