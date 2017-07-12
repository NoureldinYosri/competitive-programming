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

const int MAX = 100*1000 + 10;
const int mod = 1e9 + 7;
int n,m,K;
int id[MAX],W[MAX];

int find(int a){
	return id[a] = (a == id[a]) ? a : find(id[a]);
}

void join(int a,int b){
	a = find(a),b = find(b);
	if(a == b) return;
	if(W[a] < W[b]) swap(a,b);
	W[a] += W[b];
	id[b] = a;
	K --;
}

int mul(int x,int y){
	return (x*1LL*y)%mod;
}
int add(int x,int y){
	x += y;
	if(x >= mod) x -= mod;
	return x;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d %d",&n,&m);
		range(i,1,n) id[i] = i,W[i] = 1;
		K = n;
		while(m--){
			int a,b; scanf("%d %d",&a,&b);
			join(a,b);
		}
		if(K == 1) puts("-1");
		else{
			int ans = 1;
			cerr << n << " " << K << endl;
			while(K > 1) ans = mul(ans,mul(n,--K));
			printf("%d\n",ans);
		}
	}
	return 0;
}
