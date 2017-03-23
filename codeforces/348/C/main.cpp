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

const int MAX = 100*1000 + 1;
ll A[MAX],sum[MAX],bond[MAX];
vi S[MAX],adj[MAX],to[MAX],heavy;
int n,m,q;
int blkSize;

void update(int k,int x){
	if(sz(S[k]) < blkSize){
		for(int pos : S[k]) A[pos] += x;
	}
	else{
		bond[k] += x;
	//	sum[k] += x*1LL*sz(S[k]);
	}
	loop(i,sz(heavy)){
		int h = heavy[i];
		vi & adj = ::adj[i];
		sum[h] += x*1LL*adj[k];
	//	cerr << h << " " << k << " " << adj[k] << " " << x << " -> " << sum[h] << endl;
	}
//	cerr << endl;
}

ll solve(int k){
	ll ret = 0;
	if(sz(S[k]) < blkSize) {
		for(int pos : S[k]) ret += A[pos];
		loop(i,sz(heavy)){
			int h = heavy[i];
			vi & adj = ::adj[i];
			ret += bond[h]*adj[k];
	//		cerr << h << " " << k << " " << bond[h] << " " << adj[k] << endl;
		}
	}
	else ret = sum[k];
//	cerr << endl;
	return ret;
}


int main(){
	scanf("%d %d %d",&n,&m,&q); blkSize = sqrt(n) + 1;
	loop(i,n) scanf("%lld",A + i);
	
	loop(i,m){
		int k ; scanf("%d",&k);
		S[i] = vi(k,0);
		loop(j,k){
			int x; scanf("%d",&x); x--;
			S[i][j] = x;
			sum[i] += A[x];
			to[x].pb(i);
		}
		if(k >= blkSize) heavy.pb(i);
	}

	loop(i,sz(heavy)){
		int h = heavy[i];
		adj[i] = vi(n,0);
		for(int x : S[h]){
			for(int y : to[x])
				adj[i][y]++;
		}
	}

	loop(i,q){
		char c; int k;
		scanf(" %c %d",&c,&k); k--;
		if(c == '?') printf("%lld\n",solve(k));
		else{
			int x; scanf("%d",&x);
			update(k,x);
		}
	}
	return 0;
}
