#ifdef ACTIVE
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100*1000 + 10;

int f[MAXN],A[MAXN];
int L[MAXN],R[MAXN];
int n;
int low[MAXN];

int ST[1 << 20];

void build(int cur,int s,int e) {
	ST[cur] = 0;
	if(s == e) return ;
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	build(left,s,m);
	build(right,m+1,e);
}
void update(int cur,int s,int e,int p,int v) {
	ST[cur] = max(ST[cur],v);
	if(s == e) return;
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	if(p <= m) update(left,s,m,p,v);
	else update(right,m+1,e,p,v);
}
int query(int cur,int s,int e,int l,int r) {
	if(l <= s && e <= r) return ST[cur];
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	if(r <= m) return query(left,s,m,l,r);
	if(m < l) return query(right,m+1,e,l,r);
	return max(query(left,s,m,l,m),query(right,m+1,e,m+1,r));
}

void solve(){
	for(int i = 0;i < n;i++) low[f[i]] = INT_MAX;
	build(0,0,n);
	for(int i = n-1; i >= 0;i--) {
		L[i] = max(L[i],query(0,0,n,0,f[i]));
		update(0,0,n,f[i],L[i]);
	}
	low[0] = 0;
	for(int i = 0;i < n;i++) {
		int x = max(L[i],low[f[i]-1]);
		low[f[i]] = min(low[f[i]],x+1);
		A[i] = x;
	}
}

int main(){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T; scanf("%d",&T);
	for(int t = 0;t < T;t++){
		scanf("%d",&n);
		for(int i = 0;i < n;i++) scanf("%d",f + i);
		for(int i = 0;i < n;i++) scanf("%d %d",L + i,R + i);
		solve();
		for(int i = 0;i < n;i++) printf("%d%c",A[i]," \n"[i==n-1]);
	}
	return 0;
}
#endif
