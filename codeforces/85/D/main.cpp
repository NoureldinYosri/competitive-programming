#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long>
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

const int MAX = 1e5 + 1e3;

int prime[MAX];

unordered_map<int,vi> M;


void sieve(){
	for(ll i = 2;i < MAX;i++)
		if(!prime[i]){
			prime[i] = i;
			for(ll j = i*i; j < MAX; j += i)
				prime[j] = i; 
		}
}

vp factor(int x){
	vp D;
	while(x > 1){
		int p = prime[x],ctr = 0;
		while(x%p == 0){
			++ctr;
			x /= p;
		}
		D.pb(mp(p,ctr));
	}
	return D;
}

void getDiv(int p,vp & D,vi & V){
	if(p == sz(D)) {
		V.pb(1);
		return;
	}
	getDiv(p + 1,D,V);
	int k = sz(V);
	int q = 1;
	loop(i,D[p].yy){
		q *= D[p].xx;
		loop(j,k) V.pb(q*V[j]);
	}
}

int main(){
	sieve();
	int n,x,y;
	scanf("%d",&n);
	loop(q,n){
		scanf("%d %d",&x,&y);
		vp D = factor(x);
		vi div ;
		getDiv(0,D,div);
		int ans = 0;		
		for(int p : div) ans += !(M[p].end() - lower_bound(all(M[p]),q - y));
		for(int p : div) M[p].pb(q);
		printf("%d\n",ans);
	}
	return 0;
}
