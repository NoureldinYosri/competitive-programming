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

ll p10[100];

ll g(int L){
	if(!L) return 0;
	return 45LL*L*p10[L - 1];
}

ll f(char *num){
	ll ret = 0;
	int L = strlen(num);
	vl cnt(L,0);
	for(int i = 0;i < L;i++){
		for(int j = i+1;j < L;j++)
			cnt[i] = cnt[i]*10 + num[j] - '0';
		cnt[i]++;
	}
	for(int i = 0;i < L;i++){
		int d = num[i] - '0';
		ret += d*g(L-1-i) + d*(d-1)/2*p10[L-1-i] + d*cnt[i];
		//ret += num[i] - '0';
	}
	return ret;
}

ll get(ll n){
	if(!n) return 0;
	char buffer[50]; 
	sprintf(buffer,"%lld",n);
	return f(buffer);
}

ll BS(ll s,ll e,ll T){
	while(s < e){
		ll m = s + (e - s)/2;
		if(get(m) >= T) e = m;
		else s = m + 1;
	}
	return s;
}

int main(){
	p10[0] = 1;
	loop(i,99) p10[i + 1] = 10*p10[i];
	ll mod ; cin >> mod;
	ll r = BS(1,p10[17],mod);
	for(;get(BS(0,r-1,get(r)%mod)) != get(r)%mod;r++);
	cerr << BS(0,r-1,get(r)%mod) + 1 << " " << r << endl;
	cout << BS(0,r-1,get(r)%mod) + 1 << " " << r << endl;
	
	return 0;
}
