#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

const int MAX = 1 << 25;
const int mod = 1e9 + 7;
int fact[MAX],invi[MAX],invf[MAX];

int mul(int a,int b) {
	return (a*1LL*b)%mod;
}
int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}

int C(int n,int k) {
	if(k > n) return 0;
	int r = fact[n];
	r = mul(r,invf[k]);
	r = mul(r,invf[n-k]);
	return r;
}

int coef(int n,int k) {
	n--;
	if(k > n) return 0;
	int r = C(2*n-k,n);
	r = mul(r,C(n,k));
	r = mul(r,invi[n-k+1]);
	return r;
}

void init(){
	fact[0] = 1;
	for(int i = 1;i < MAX;i++)
		fact[i] = mul(i,fact[i-1]);

	invi[1] = 1;
	for(int i = 2;i < MAX;i++){
		invi[i] = mul(mod-mod/i,invi[mod%i]);
		assert(mul(i,invi[i]) == 1);
	}

	invf[0] = 1;
	for(int i = 1;i < MAX;i++){
		invf[i] = mul(invf[i-1],invi[i]);
		assert(mul(fact[i],invf[i]) == 1);
	}
}
int powmod(int x,int p) {
	if(p == 0) return 1;
	int y = 1;
	for(;p > 1;p >>= 1) {
		if(p & 1) y = mul(x,y);
		x = mul(x,x);
	}
	return mul(x,y);
}


int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	init();
	int n,k,A,B;
	cin >> n >> k >> A >> B;
	k %= mod;
	A %= mod;
	B %= mod;

	int bk = mul(B,k);
	int ibk = powmod(bk,mod-2);
	int pbk = powmod(bk,n-1);

	int r = 0,pA = 1;
	loop(k,n) {
		int tmp = coef(n,k);
		tmp = mul(tmp,pA);
		tmp = mul(tmp,pbk);
		r = add(r,tmp);

		pA = mul(pA,A);
		pbk = mul(pbk,ibk);
	}
	r = mul(r,k);
	cout << r << endl;
	return 0;
}
