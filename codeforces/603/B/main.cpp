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

const int MAX = 1'000'000 + 10,mod = 1'000'000'007;
int T[MAX],R[MAX],p,k;
int cnt[MAX],vis[MAX];
int f[MAX];

int pow_mod(ll val,int b){
	if(!b) return 1;
	int y = 1;
	for(;b > 1;b >>= 1){
		if(b & 1) y = (y*1LL*val)%mod;
		val = (val*val)%mod;
	}
	val = (val*y)%mod;
	return val;
}

int main(){
	scanf("%d %d",&p,&k);
	if(!k){
		printf("%d\n",pow_mod(p,p - 1));
		return 0;
	}
	loop(i,p) T[i] = (i*1LL*k)%p;
	loop(i,p) if(!vis[i]){
		int j = i,len = 0;
		while(!vis[j]){
			vis[j] = 1;
			len++;
			j = T[j];
		}
		cnt[len]++;
	}
	int ans = 1;
	range(len,1,p) {
		for(int j = len;j <= p;j += len)
			f[j] = (f[j] + len*1LL*cnt[len])%mod;
		int val = pow_mod(f[len],cnt[len]);
		ans = (ans*val)%mod;
	}
	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
