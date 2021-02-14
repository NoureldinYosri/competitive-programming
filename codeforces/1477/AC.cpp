#include<bits/stdc++.h>
#define ll long long
#define ls rt*2,le,mi
#define rs rt*2+1,mi+1,ri
using namespace std;

long long n,m,i,p,x,y,k;
char s[510000];
ll a[510000],b[510000],l[510000],r[510000];
ll lazy[2100000],sm[2100000];

void update(ll rt){
	if(lazy[rt*2]==lazy[rt*2+1])lazy[rt]=lazy[rt*2];
	else lazy[rt]=-1;
	sm[rt]=sm[rt*2]+sm[rt*2+1];
}

void build(ll rt,ll le,ll ri){
//	cout << t << ' ' << le << ' ' << ri << endl;
	if(le == ri){
		sm[rt] = a[le];
		lazy[rt]=-1;
		return;
	}
	int mi = (le + ri) / 2;
	build(rt * 2,le,mi);
	build(rt * 2 + 1,mi + 1,ri);
	update(rt);
}

void pushDown(ll rt,ll le,ll ri){
	ll mi=(le+ri)/2;
	if(lazy[rt] != -1){
		lazy[rt*2]=lazy[rt];
		lazy[rt*2+1]=lazy[rt];
		sm[rt*2]=(mi-le+1)*lazy[rt];
		sm[rt*2+1]=(ri-mi)*lazy[rt]; 
		lazy[rt]=-1;
	}
}

bool check(ll rt,ll le,ll ri){
	pushDown(rt,le,ri);
	ll mi=(le+ri)/2;
	if(le<ri){
		if(!check(ls))return 0;
		if(!check(rs))return 0;
	}
	else{
		if(b[le]!=sm[rt])return 0;
	}
	return 1;
}

void Add(ll rt,ll le,ll ri,ll x,ll y,ll k){
	if(le >= x && ri <= y){
		lazy[rt]=k;
		sm[rt]=k*(ri-le+1);
		return;
	}
	pushDown(rt,le,ri);
	long long mi = (le + ri) / 2;
	if(x <= mi)Add(rt * 2,le,mi,x,y,k);
	if(y > mi)Add(rt * 2 + 1,mi + 1,ri,x,y,k);
	update(rt);
}

long long makesum(ll rt,ll le,ll ri,ll x,ll y){
//	cout << t << ' ' << le << ' ' << ri << endl;
	if(le >= x && ri <= y){
		return sm[rt];
	}
	ll ans = 0;
	ll mi = (le + ri) / 2;
	if(x <= mi){
		pushDown(rt,le,ri);
		ans += makesum(ls,x,y);
	}
	if(y > mi){
		pushDown(rt,le,ri);
		ans += makesum(rs,x,y);
	}
	return ans;
}

void Prin(int rt,int le,int ri,int s){
	for(ll i=1;i<=s;i++){
		cout << "	";
	}
	printf("num %d: from %d to %d, sum = %d, addmark = %d\n",rt,le,ri,sm[rt],lazy[rt]);
	if(le < ri){
		ll mi = (le + ri) / 2;
		Prin(ls,s+1);
		Prin(rs,s + 1);
	}
}

int main(){
	ll ttttt;
	cin >> ttttt;
	while(ttttt--){
		//cout << "\n---------------------\n" << endl;
		cin >> n >> m;
		scanf("%s",s+1);
		for(ll i=1;i<=n;i++){
			b[i]=s[i]-48;
		}
		scanf("%s",s+1);
		for(ll i=1;i<=n;i++){
			a[i]=s[i]-48;
		}
		build(1,1,n);
//	Prin(1,1,n,0);
		for(ll i=1;i<=m;i++){
			scanf("%lld%lld",&l[i],&r[i]);
//		Prin(1,1,n,0);
		}
		bool f=0;
		for(ll i=m;i>=1;i--){
			ll kans = makesum(1,1,n,l[i],r[i]);
			if(kans < (r[i]-l[i]+2)/2)Add(1,1,n,l[i],r[i],0);
			else if(kans > (r[i]-l[i]+1)/2)Add(1,1,n,l[i],r[i],1);
			else{
				cout << "NO" << endl;
				f=1;
				break;
			} 
		//	Prin(1,1,n,0);
		}
		if(f)continue;
		if(check(1,1,n))cout << "YES" << endl;
		else cout << "NO" << endl;
		//Prin(1,1,n,0);
	}
	return 0;
}
