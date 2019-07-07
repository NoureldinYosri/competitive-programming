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
//map<int,int> primeFactors;
//
//void init(){
//	vi primes {2,3,5,7,11,13};
//	for(int p : primes){
//		int q = p;
//		int e = 0;
//		while(q <= 13) {
//			e += 13/q;
//			q *= p;
//		}
//		primeFactors[p] = e;
//	}
//	for(auto pe : primeFactors){
//		prp(pe);
//	}
//	cerr << endl;
//	ll thirteenFactorial = 1;
//	for(auto pe : primeFactors) {
//		int p = pe.xx,e = pe.yy;
//		loop(i,e) thirteenFactorial *= p;
//	}
//	cerr << "phi = " << thirteenFactorial << endl;
//}
//
//ll phi(ll n) {
//	ll ret = n;
//	for(int i = 2;i*i <= n;i++) {
//		if(n%i == 0){
//			ret -= ret/i;
//			while(n%i == 0) n /= i;
//		}
//	}
//	if(n > 1) ret -= ret/n;
//	return ret;
//}
//
//vector<ll> divs;
//
//void getDivs(){
//	divs.push_back(1);
//	for(auto pe : primeFactors){
//		int len = sz(divs);
//		int p = pe.first,e = pe.second,q = p;
//		for(;e > 0;e--,q *= p)
//			for(int i = 0;i < len;i++)
//				divs.push_back(divs[i]*q);
//	}
//	sort(all(divs));
//	print(divs,ll);
//}
//
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	init();
//	getDivs();
//	//p^e - p^(e-1) =
//	//p^(e-1)*(p - 1)
//	//e >= 1
//	//p^k * (p - 1)
//	//k >= 0
//
//
//	return 0;
//}
