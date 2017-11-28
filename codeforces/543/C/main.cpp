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

const int MAX = 211;
int f[MAX],g[MAX],n;
int vis[MAX];


ll get_lcm() {
	ll lcm = 1;
	memset(vis,0,sizeof vis);
	int ti = 0;
	range(i,1,n) if(!vis[g[i]]) {
		int cur = g[i],prv = ti;
		while(!vis[cur]) {
			vis[cur] = ++ti;
			cur = g[cur];
		}
		if(vis[cur] <= prv) continue;
		int len = ti - vis[cur] + 1;
		lcm *= len/__gcd(len+0LL,lcm);
	}
	return lcm;
}

bool inCycles(bool debug = 0){
	memset(vis,0,sizeof vis);
	range(i,1,n) if(!vis[g[i]]){
		int cur = g[i];
		while(!vis[cur]) {
			vis[cur] = 1;
			cur = g[cur];
		}
		if(cur != g[i]) return 0;
	}
	return 1;
}

int get_k(){
	range(i,1,n) g[i] = i;
	int k;
	for(k = 1;(k==1) || !inCycles();k++) {
		range(i,1,n) g[i] = f[g[i]];
	//	prArr(g+1,n,int);
	//	cerr << inCycles() << endl;
	}
	return k;
}

bool done(){
	range(i,1,n) if(g[i] != g[g[i]]) return 0;
	return 1;
}

void create(int k){
	range(i,1,n) g[i] = i;
	for(;k;k--) {
		range(i,1,n) g[i] = f[g[i]];
	}
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	range(i,1,n) {
		scanf("%d",f + i);
//		cerr << i << " " << f[i] << endl;
	}
	int k = get_k();
	if(k!=1){
		create(k-1);
		if(done()) {
			cout << k-1 << endl;
			return 0;
		}
	}
	create(1);
	ll lcm = get_lcm();
	ll ans = ((k + lcm - 1)/lcm)*lcm;

	cout << ans << endl;
	return 0;
}
