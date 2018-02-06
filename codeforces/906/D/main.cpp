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


const int MAX = 100*1000 + 10;
int A[MAX],n,mod;
vi P;
int notPrime[MAX];

void sieve(){
	for(int i = 2;i < MAX;i++)
		if(notPrime[i] == 0) {
			P.pb(i);
			for(ll j = i*1LL*i;j < MAX;j += i)
				notPrime[j] = 1;
		}
}

int getPhi(int m) {
	static map<int,int> memo;
	if(memo.find(m) != memo.end()) return memo[m];
	int n = m,phi = n;
	for(int p : P){
		if(p*p > n) break;
		if(n%p) continue;
		phi -= phi / p;
		while(n%p == 0) n /= p;
	}
	if(n > 1) phi -= phi/n;
	return memo[m] = phi;
}


int mul(int a,int b,int m) {
	a %= mod,b %= mod;
	return (a*1LL*b)%m;
}

int add(int a,int b,int m) {
	a %= mod,b %= mod;
	a += b;
	if(a >= m) a -= m;
	if(a < 0) a += m;
	return a;
}

int powmod(int x,int p,int m) {
	x %= m;
	if(!p) return 1%m;
	int y = 1;
	for(;p > 1;p >>= 1) {
		if(p & 1) y = mul(x,y,m);
		x = mul(x,x,m);
	}
	return mul(x,y,m);
}

vp factorize(int n) {
	static map<int,vp> memo;
	if(memo.find(n) != memo.end()) return memo[n];
	int m = n;
	vp ret;
	for(int p : P){
		if(p*p > n) break;
		if(n%p) continue;
		int q = 1;
		while(n%p == 0) {
			n /= p;
			q *= p;
		}
		ret.pb(mp(p,q));
	}

	if(n > 1) ret.pb(mp(n,n));
	return memo[m] = ret;
}


int getExponent(int p,int q) {
	int e = 0;
	while(q%p == 0) e++,q /= p;
	return e;
}

bool check(int l,int r,int k,int & d) {
	++d;
//	static map<pair<pi,int>,bool> memo;
	if(l > r) return 0;
	if(A[l] >= k) return 1;
	if(A[l] == 0) return 0;
//	auto t = mp(mp(l,r),k);
//	if(memo.find(t) != memo.end()) return memo[t];
	int nk = 1,p = A[l];
	while(p < k) {
		p *= A[l];
		nk++;
	}
	return check(l+1,r,nk,d);
}

int getVal(int l,int r) {
	static map<pi,int> memo;
	if(l == r) return A[l];
	pi t (l,r);
	if(memo.find(t) != memo.end()) return memo[t];
	int x = getVal(l+1,r),res = 1;
	loop(i,x) res *= A[l];
	return memo[t] = res;
}

int solve(int l,int r,int m) {
	static map<pair<pi,int>,int> memo;
	static map<pi,int> E;
	if(l == r) return A[l]%m;
	if(m <= 2) {
		E[mp(l,m)] = l;
		return A[l]%m;
	}
	if(A[l]%m == 0) {
		E[mp(l,m)] = l;
		return A[l]%m;
	}
	if(E.find(mp(l,m)) != E.end()) r = min(r,E[mp(l,m)]);
	auto t = mp(mp(l,r),m);
	if(memo.find(t) != memo.end()) return memo[t];

	int res = 0,a = A[l]%m,g = __gcd(a,m);

	int a1 = 1,m1 = 1,a2 = a,m2 = m;
	for(auto f : factorize(g)){
		int p = f.xx;
		while(a2%p == 0) {
			a2 /= p;
			a1 *= p;
		}
		while(m2%p == 0) {
			m2 /= p;
			m1 *= p;
		}
	}

	int aL [] = {a1,a2};
	int mL [] = {m1,m2};
	int R[2] = {1,1};

	int en = -1;
	loop(i,2) loop(j,2) if(i+j) {
		int phi = getPhi(mL[j]);
		solve(l+1,r,phi);
		if(E.find(mp(l+1,phi)) != E.end()) en = max(en,E[mp(l+1,phi)]);
	}
	loop(i,2) loop(j,2) if(i+j){
		int a = aL[i],base = mL[j];
		int x = solve(l+1,r,getPhi(base)),r = powmod(a,x,base);
//		cerr << a << "^" << x << " = " << r << " mod " << base << endl;
		R[j] = mul(R[j],r,base);
	}


	loop(i,1) {
		int a = aL[i],base = mL[i];
		int k = 0; ll p = 1;
		while(p%base) {
			k++;
			p *= a;
		}
//		cerr << a << " " << base << " k is " << k << " ch = " << check(l+1,r,k) << endl;
		int d = 0;
		if(check(l+1,r,k,d)){
			R[i] = 0;
			en = max(en,l + d);
		}
		else {
			en = max(en,n);
			int x = getVal(l+1,r);
			int r = powmod(a,x,base);
//			cerr << "... " << a << "^" << x << " = " << r << " mod " << base << endl;
			R[i] = mul(R[i],r,base);
		}
	}

//	prArr(aL,2,int);
//	prArr(mL,2,int);
//	prArr(R,2,int);
	if(en != -1) E[mp(l,m)] = en;
	loop(i,2){
		int b = mL[i],bt = mL[i ^ 1];
		int r = mul(R[i],bt,m);
		int ibt = powmod(bt,getPhi(b) - 1,b);
		r = mul(r,ibt,m);
		res = add(res,r,m);
	}
//	cerr << "ret from " << l << " " << r << " " << m << " -> " << res << endl;
	return memo[t] = res;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	sieve();
	scanf("%d %d",&n,&mod);
	range(i,1,n) scanf("%d",A + i);
	int Q; scanf("%d",&Q);
	for(int q = 1;q <= Q;q++) {
		int l,r; scanf("%d %d",&l,&r);
		printf("%d\n",solve(l,r,mod));
	}
	return 0;
}
