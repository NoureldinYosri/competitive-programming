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

const int MAX = 1 << 20,mod = 1e9 + 7;
int F[MAX],r[MAX];

int mul(int a,int b){
	return (a*1LL*b)%mod;
}

int pow_mod(int a,int p){
	if(!p) return 1;
	int b = 1;
	for(;p > 1;p >>= 1){
		if(p & 1) b = mul(a,b);
		a = mul(a,a);
	}
	return mul(a,b);
}

void init(){
	F[0] = r[0] = 1;
	loop(i,MAX-1) F[i+1] = mul(i+1,F[i]);
	loop(i,MAX) r[i] = pow_mod(F[i],mod - 2);
}

int C(int n,int k){
	if(n < k) return 0;
	assert(n >= 0 && n < MAX);
	assert(k >= 0 && k < MAX);
	int res = mul(F[n],r[k]);
	res = mul(res,r[n-k]);
	return res;
}


int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	init();
	int T; scanf("%d",&T);
	range(t,1,T) {
		int x1,y1,x2,y2,x,y;
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		x = x2 - x1;
		y = y2 - y1;
		int m = min(x,y);
		int res = 0;
		for(int k = 0;k <= m;k++){
			res += mul(C(m,k),C(x+y-k,m));
			if(res >= mod) res -= mod;
		}
		printf("Case %d: %d\n",t,res);
	}
	return 0;
}
