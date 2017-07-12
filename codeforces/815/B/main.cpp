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

const int MAX = 200 * 1000 + 10,mod = 1e9 + 7;
int F[MAX],r[MAX];

int mul(int x,int y){
	return (x*1LL*y)%mod;
}
int add(int x,int y){
	x += y;
	if(x >= mod) x -= mod;
	if(x < 0) x += mod;
	return x;
}

int pow_mod(int x,int p){
	if(!p) return 1;
	int y = 1;
	for(;p > 1;p >>= 1) {
		if(p & 1) y = mul(x,y);
		x = mul(x,x);
	}
	return mul(x,y);
}

int C[MAX];

void get_coef(int n){
	if(n%4 == 0){
		int m = n/2 - 1;
		for(int i = 0;i <= m;i++)
			C[2*i + 1] = -1*(C[2*i] = mul(F[m],mul(r[i],r[m - i])));
	}
	else if(n%4 == 1) {
		int m = (n - 1)/2;
		for(int i = 0;i <= m;i++)
			C[2*i] = mul(F[m],mul(r[i],r[m - i]));
	}
	else if(n%4 == 2) {
		int m = (n - 2)/2;
		for(int i = 0;i <= m;i++)
			C[2*i] = C[2*i + 1] = mul(F[m],mul(r[i],r[m - i]));
	}
	else {
		get_coef(n - 1);
		int aux[MAX];
		copy(C,C + n - 1,aux);
		memset(C,0,sizeof C);
		int sgn = 1;
		for(int i = 0;i < n-1;i++) {
			C[i] += aux[i];
			C[i + 1] += sgn * aux[i];
			sgn *= -1;
		}
	}
//	prArr(C,n,int);
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	F[0] = r[0] = 1;
	loop(i,MAX-1) {
		F[i + 1] = mul(F[i],i + 1);
		r[i + 1] = pow_mod(F[i + 1],mod - 2);
	}
	int n; scanf("%d",&n);
	get_coef(n);
	int ans = 0;
	loop(i,n){
		int x; scanf("%d",&x);
		ans = add(ans,mul(C[i],x));
	}
	cout << ans << endl;
	return 0;
}
