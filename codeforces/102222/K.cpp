#include <bits/stdc++.h>
using namespace std;

const int MAXV = 36,MAXE = MAXV*MAXV;
int mod;
int n,m;
int fr[MAXE],to[MAXE];
int val[MAXV];

int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}

int mul(int a,int b) {
	return (a*(long long)b)%mod;
}

int f[1 << 20],g[1 << 20];
using pi = pair<int,int>;

pi getInfo(int l,int r,int msk) {
	int v = 1;
	for(int i = 0;i < r-l;i++) if(msk & (1 << i)) {
		int u = l + i;
		v = mul(v,val[u]);
	}
	int cnt = 0;
	for(int e = 0;e < m;e++) {
		int x = fr[e],y = to[e];
		if(l <= x && l <= y && x < r && y < r) {
			bool isCovered = 0;
			x = x - l;
			y = y - l;
			if(msk & (1 << x)) isCovered = 1;
			if(msk & (1 << y)) isCovered = 1;
			cnt += isCovered;
		}
	}
	return pi(v,cnt);
}

int solve(){
	int b = n/2;
	assert(b <= 20);
	int leftCount = 0,rightCount = 0;
	for(int e = 0;e < m;e++){
		leftCount += max(fr[e],to[e]) < b;
		rightCount += min(fr[e],to[e]) >= b;
	}
	int goodLeft = 0,badLeft = 0,totLeft = 0;
	for(int msk = 0;msk < (1 << b);msk++)
		f[msk] = g[msk] = 0;
	for(int msk = 0;msk < (1 << b);msk++) {
		pi tmp = getInfo(0,b,msk);
		int v = tmp.first;
		int cnt = tmp.second;
		assert(cnt <= leftCount);
		totLeft = add(totLeft,v);
		f[msk] = 0;
		if(cnt != leftCount) goodLeft = add(goodLeft,v);
		else {
			f[msk] = v;
			badLeft = add(badLeft,v);
		}
	}
//	cout << leftCount << endl;
//	cout << goodLeft << " " << badLeft << " " << totLeft << endl;
	for(int i = 0;i < b;i++) {
		for(int msk = 0;msk < (1 << b);msk++)
			if(!(msk & (1 << i)))
				f[msk] = add(f[msk],f[msk | (1 << i)]);
	}
//	for(int msk = 0;msk < (1 << b);msk++){
//		int rem = (1 << b) - 1;
//		rem ^= msk;
//		g[msk] = f[msk];
//		for(int x = rem;x;x = (x-1)&rem)
//			g[msk] = add(g[msk],g[msk | x]);
//	}
//	for(int msk = 0;msk < (1 << b);msk++)
//		assert(g[msk] == f[msk]);
	for(int msk = 0;msk < (1 << b);msk++)
		g[msk] = f[msk];
	int ans = 0;
	for(int msk = 0;msk < (1 << (n-b));msk++) {
		pi aux = getInfo(b,n,msk);
		int v = aux.first;
		int cnt = aux.second;
//		cout << msk << ": " << v << " " << cnt << endl;
		assert(cnt <= rightCount);
		if(cnt != rightCount) {
			ans = add(ans,mul(v,totLeft));
			continue;
		}
		ans = add(ans,mul(v,goodLeft));
		int omsk = 0;
		for(int e = 0;e < m;e++) {
			int x = fr[e],y = to[e];
			if(x > y) swap(x,y);
			if(!(x < b && b <= y)) continue;
			y -= b;
			if(msk & (1 << y)) continue;
			omsk |= 1 << x;
		}
		int tmp = add(badLeft,-g[omsk]);
//		cout << badLeft << " - " << g[omsk] << ": " << tmp << endl;
		ans = add(ans,mul(v,tmp));
	}
	int tot = 1;
	for(int i = 0;i < n;i++) {
		tot = mul(tot,add(val[i],1));
//		cout << tot << endl;
	}
//	cout << tot << endl;
	ans = add(tot,-ans);
	return ans;
}


int main(){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T; scanf("%d",&T);
	for(int t = 1;t <= T;t++) {
		scanf("%d %d %d",&n,&m,&mod);
		for(int i = 0;i < n;i++){
			scanf("%d",val + i);
			val[i] %= mod;
		}
		for(int e = 0;e < m;e++){
			scanf("%d %d",fr + e,to + e);
			fr[e]--,to[e]--;
		}
		printf("Case #%d: %d\n",t,solve());
	}
}
