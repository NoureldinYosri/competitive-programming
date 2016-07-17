#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 100000000;
vector<ll> P;
int not_p[MAX + 1];
vector<ll> jam[17];

void sieve(){
	for(ll i = 2;i <= MAX;i++){
		if(not_p[i] == 0){
			P.pb(i);
			for(ll j = i*i; j <= MAX;j += i)
				not_p[j] = 1;
		}
	}
}

ll get_div(ll n){
	for(auto p : P){
		if(p >= n) break;
		if(n%p == 0) return p;
	}
	return 0;
}

ll interpret(char *s,ll base){
	ll m = 0;
	int n = strlen(s);
	loop(i,n) m = m*base + s[i] - '0';
	return m;
}

bool get(ll n,vector<ll> & D,int & L){
	D.clear();
	char s[20]; sprintf(s,"%lld",n);
	L = strlen(s);
	for(int base = 2;base <= 10;base++){
		ll m = interpret(s,base);
		ll d = get_div(m);
		if(d == 0) return 0;
		D.pb(d);
	}
	return 1;
}

int main(){
	sieve();		
	queue<ll> q; q.push(1);
	vector<ll> D; int L;
	cerr << "start precomp" << endl;
	while(!q.empty()){
		ll n = q.front(); q.pop();
		if(n >= 10000000000000LL) continue;		
		if((n & 1) && n != 1 && get(n,D,L)) {
			jam[L].pb(n);
		}
		q.push(n * 10);
		q.push(n * 10 + 1);
	}
	cerr << "done pre" << endl;
	/*int T,N,J;
	scanf("%d",&T);
	loop(t,T){
		scanf("%d %d",&N,&J);
		printf("Case #%d:\n",t + 1);
		cerr << J << " " << sz(jam[N]) <<" " << N<< endl;
		loop(i,J){		
			ll n = jam[N][i];
			printf("%lld",n);
			get(n,D,L);
			loop(j,9) {printf(" %lld",D[j]);}
			puts("");
		}
	}*/
	loop(i,14) cerr << i << " " << sz(jam[i]) << endl;
	return 0;
}
