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

ll DIV[1<<20],aux[1 << 20];
int cnt,aux_cnt,idx = 0;
ll out[1<<20];
int P[1<<20],prime_cnt;
int not_prime[1<<20];
int dp_prime[1<<20];
vl divs[1<<20];

void sieve(){
	int mx = 1 << 20;
	for(int i = 2;i < mx;i++)
		if(not_prime[i] == 0){
			P[prime_cnt++] = i;
			if(i*1LL*i >= mx) continue;
			for(int j = i*i;j < mx;j += i)
				not_prime[j] = 1;
		}
}
bool is_prime(ll n){
	int idx = lower_bound(DIV,DIV + cnt,n) - DIV;
	if(dp_prime[idx] != -1) return dp_prime[idx];
	loop(i,prime_cnt){
		if(P[i]*1LL*P[i] > n) break;
		if(n%P[i] == 0) return dp_prime[idx] = 0;
	}
	return dp_prime[idx] = n > 1;
}

void get_DIVs(ll n,ll *DIV,int & cnt){
	int idx = lower_bound(::DIV,::DIV + ::cnt,n) - ::DIV;
	if(::cnt && !divs[idx].empty()) {
		copy(all(divs[idx]),DIV);
		cnt = divs[idx].size();
		return;
	}
	cnt = 0;
	for(ll i = 1;i*i <= n;i++)
		if (n%i == 0){
			DIV[cnt++] = i;
			if(i*i != n)
				DIV[cnt++] = n/i;
		}
	sort(DIV,DIV + cnt);
	divs[idx] = vl(DIV,DIV + cnt);
}


void work(ll n,ll k,int & mx){
	if(k == 0) {
		if(mx) out[idx++] = n,mx--;
	}
	else if(n == 1){
		if(mx){
			out[idx++] = 1;
			mx--;
		}
	}
	else if(is_prime(n)){
		for(int i = 0;i < k && mx;i++,mx--)
			out[idx++] = 1;		
		work(n,0,mx);
	}
	else{
		get_DIVs(n,aux,aux_cnt);
		vl DIVs(aux,aux + aux_cnt);
		for(int i = 0;i < sz(DIVs) && mx;i++)
			work(DIVs[i],k-1,mx);
	}
}

int main(){
	sieve();
	memset(dp_prime,-1,sizeof dp_prime);
	ll n,k; cin >> n >> k;
	int mx = 100*1000;
	get_DIVs(n,DIV,cnt);
	work(n,k,mx);
	loop(i,idx) printf("%lld%c",out[i]," \n"[i==idx-1]);
	return 0;
}
