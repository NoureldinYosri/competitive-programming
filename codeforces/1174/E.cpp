//#pragma GCC optimize ("O3")
//#include <bits/stdc++.h>
//#define loop(i,n) for(int i = 0;i < (n);i++)
//#define range(i,a,b) for(int i = (a);i <= (b);i++)
//#define all(A) A.begin(),A.end()
//#define pb push_back
//#define mp make_pair
//#define sz(A) ((int)A.size())
//#define vi vector<int>
//#define vd vector<double>
//#define vp vector<pair<int,int> >
//#define ll long long
//#define pi pair<int,int>
//#define popcnt(x) __builtin_popcountll(x)
//#define LSOne(x) ((x) & (-(x)))
//#define xx first
//#define yy second
//#define PQ priority_queue
//#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
//#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
//#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
//#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
//#define what_is(x) cerr << #x << " is " << x << endl
//#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
//using namespace std;
//
//
//int gcd(int a,int b) {
//	while(b) {
//		a %= b;
//		swap(a,b);
//	}
//	return a;
//}
//
//void bf(int n) {
//	vi P,G;
//	vector<vi> sol,solG;
//	loop(i,n) {
//		P.push_back(i+1);
//		G.push_back(0);
//	}
//	int mx = 0;
//	do{
//		set<int> S;
//		int g = 0;
//		loop(i,n) {
//			g = gcd(g,P[i]);
//			S.insert(g);
//			G[i] = g;
//		}
//		if(sz(S) > mx) {
//			mx = sz(S);
//			sol.clear();
//			solG.clear();
//		}
//		if(mx == sz(S)) {
//			sol.push_back(P);
//			solG.push_back(G);
//		}
//	}while(next_permutation(all(P)));
//	cerr << n << ": " << sz(sol) << " " << mx << endl;
////	for(int i = 0;i < sz(sol);i++){
////		P = sol[i];
////		vi g = solG[i];
////		print(P,int);
//////		print(g,int);
//////		cerr << string(10,'*') << endl;
////	}
//}
//
//int sig0(int x) {
//	int ret = 0;
//	for(int i = 1;i <= x;i++)
//		ret += x%i == 0;
//	return ret;
//}
//
//int getMaxSig0(int n) {
//	int ret = 1;
//	for(int i = 1;i <= n;i++)
//		ret = max(ret,sig0(i));
//	return ret;
//}
//
//const int MAX = 1000*1000 + 10,mod = 1000000007;
//int prime[MAX],numDiv[MAX];
//int fact[MAX],invf[MAX],invi[MAX];
//vi primes[MAX];
//
//void sieve(){
//	numDiv[1] = 1;
//	for(int i = 2;i < MAX;i++) {
//		if(prime[i] == 0) {
//			prime[i] = i;
//			for(ll j = i*(ll)i;j < MAX;j += i)
//				prime[j] = i;
//		}
//		int p = prime[i],x = i;
//		while(x%p == 0) x /= p,numDiv[i]++;
//		numDiv[i] += numDiv[x];
//		primes[i].push_back(p);
//		for(int q : primes[x]) primes[i].push_back(q);
//	}
//}
//
//int mul(int a,int b) {
//	return (a*(ll)b)%mod;
//}
//int add(int a,int b) {
//	a += b;
//	if(a >= mod) a -= mod;
//	if(a < 0) a += mod;
//	return a;
//}
//
//void init(){
//	sieve();
//	invi[1] = 1;
//	for(int i = 2;i < MAX;i++){
//		invi[i] = mod - mul(mod/i,invi[mod%i]);
//		assert(mul(i,invi[i]) == 1);
//	}
//	invf[0] = fact[0] = 1;
//	for(int i = 1;i < MAX;i++){
//		fact[i] = mul(fact[i-1],i);
//		invf[i] = mul(invi[i],invf[i-1]);
//		assert(mul(fact[i],invf[i]) == 1);
//	}
//}
//
//int C(int n,int k) {
//	if(k > n) return 0;
//	int ret = fact[n];
//	ret = mul(ret,invf[k]);
//	ret = mul(ret,invf[n-k]);
//	return ret;
//}
//
//int N;
//
//unordered_map<int,int> mem[100];
//
//int solve2(int x,int d = 1) {
//	if(mem[d].count(x)) return mem[d][x];
//	if(x == 1) return 1;
//	int ret = 0;
//	for(int p : primes[x]) {
//		int y = x/p;
//		int m = (N/y) - (N/x);
//		int c = mul(fact[m-1],C(N - N/x-1,m-1));
//		int tmp = mul(m,c);
//		if(y > 1) tmp = mul(tmp,solve2(y,d + 1));
////		cerr << y << " " << tmp << " " << m  << " " << N-N/x<< " " << c << endl;
//		ret = add(ret,tmp);
//	}
//	mem[d][x] = ret;
//	return ret;
//}
////4 2 (4/1 - 4/2 = 3 - 2 = 1)
//
//int solve(int n) {
//	if(n == 1) return 1;
//	loop(i,100) mem[i].clear();
//	int mx = 0;
//	for(int i = 2;i <= n;i++)
//		mx = max(mx,numDiv[i]);
////	cerr << "max num: " << mx << endl;
//	int ret = 0;
////	int ctr = 0;
//	for(int i = 2;i <= n;i++)
//		if(numDiv[i] == mx){
////			ctr ++;
//			int tmp = solve2(i);
////			cerr << i << ": " << tmp << endl;
//			ret = add(ret,tmp);
//		}
////	cerr << "there are " << ctr << " of them" << endl;
//	return ret;
//}
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	init();
//	cin >> N;
//	cout << solve(N) << endl;
//	return 0;
//}
