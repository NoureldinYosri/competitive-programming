#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int MAX = 2 << 20;
int prime[MAX];
int divs[300],div_cnt;
int P[64],Q[64],prime_cnt;

void sieve(){
	for(int i = 2;i < MAX;i++)
		if(!prime[i]) {
			prime[i] = i;
			for(ll j = i*1LL*i;j < MAX;j += i)
				prime[j] = i;
		}
}

void factorize(int n,int rest = 1){
	if(rest) {
		prime_cnt = 0;
		memset(Q,0,sizeof Q);
	}
	while(n > 1) {
		int p = prime[n],cur = prime_cnt;
		loop(i,prime_cnt) if(P[i] == p) cur = i;
		if(cur == prime_cnt) prime_cnt++;
		P[cur] = p;
		while(n%p == 0){
			n /= p;
			Q[cur]++;
		}
	}
}


void get_divs(int cur = 0){
	if(cur == prime_cnt) {
		divs[div_cnt = 0] = 1;
		div_cnt++;
		return;
	}
	get_divs(cur + 1);
	int s = 0,e = div_cnt,p = P[cur];
	loop(i,Q[cur]){
		while(s < e) divs[div_cnt++] = divs[s++] * p;
		e = div_cnt;
	}
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	sieve();

	int T; scanf("%d",&T);
	while(T--){
		int n[3],m[3],s[3];
		loop(i,3) scanf("%d",n + i);
		loop(i,3) scanf("%d",m + i);
		loop(i,3) scanf("%d",s + i);
		loop(i,3) factorize(s[i],!i);
		factorize(2,0);
		get_divs();
		vi S {divs,divs + div_cnt};
		ll N = n[0]; N *= n[1]; N *= n[2];
		ll M = m[0]; M *= m[1]; M *= m[2];
		int ans = 0;
		for(int t : S) if(t <= N) {
			ans++;
			cerr << "(0,0) (0," << t << ") some place" << endl;
		}
		print(S,int);
		for(int g : S) {
			// is there a t such that gcd(N ,t) = g and t <= M
			int cur = g;
			while(cur <= M) {
				if(N%cur) continue;
				ans++;
				fprintf(stderr,"(%d,0) (0,%lld) (x,y)\n",cur,N);
				cur += g;
			}
			cerr << "done" << endl;
		}
		break;
		printf("%d\n",ans);
	}
	return 0;
}
