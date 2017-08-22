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

const int MAX = 200*1000 + 10,MAXA = 2*2000 + 10,MAXB = 2*MAXA,mod = 1e9 + 7;
int A[MAX],B[MAX],n;
int cnt[MAXA][MAXA],f[MAXA][MAXA];
int fact[MAXB],inv[MAXB];

int add(int a,int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}

int mul(int a,int b){
	return (a*1LL*b)%mod;
}

int pow_mod(int a,int b){
	if(!b) return 1;
	int x = 1;
	for(;b > 1;b >>= 1){
		if(b & 1) x = mul(a,x);
		a = mul(a,a);
	}
	return mul(a,x);
}


void init(){
	fact[0] = 1;
	loop(i,MAXB-1) fact[i + 1] = mul(fact[i],i + 1);
	loop(i,MAXB) inv[i] = pow_mod(fact[i],mod-2);
}

int C(int n,int k){
	if(n < k) return 0;
	return mul(fact[n],mul(inv[k],inv[n - k]));
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	init();
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d %d",A + i,B + i);
		cnt[2000-A[i]][2000-B[i]]++;
	}
	for(int x = 0;x <= 4000;x++)
		for(int y = 0;y <= 4000;y++) {
			f[x][y] = cnt[x][y];
			if(x) f[x][y] = add(f[x][y],f[x - 1][y]);
			if(y) f[x][y] = add(f[x][y],f[x][y - 1]);
		}
	int ans = 0;
	loop(i,n){
		int x = A[i],y = B[i];
		ans = add(ans,f[x + 2000][y + 2000]);
		ans = add(ans,-C(2*x + 2*y,2*y));
	}
	ans = (ans * 500000004LL)%mod;
	cout << ans << endl;

	return 0;
}
