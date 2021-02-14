#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;


vi primes;

void init(){
	for(int i = 2; i <= 500; i++){
		bool isPrime = true;
		for(int j = 2; j*j <= i && isPrime; j++)
			if(i%j == 0)
				isPrime = false;
		if(isPrime) primes.push_back(i);
	}
//	print(primes, int);
}

using row = bitset<128>;
using matrix = vector<row>;

int gauss(matrix & A, int n, int m){
//	loop(i, n) loop(j, m) cerr << A[i].test(j) << " \n"[j==m-1];
//	cerr << endl;
	int rank = 0;
	for(int p = 0; p < m; p++){
		int r = -1;
		for(int i = rank; i < n; i++)
			if(A[i].test(p)){
				r = i;
				break;
			}
		if(r == -1) continue;
		if(r != rank){ 
			swap(A[r], A[rank]);
		}
		for(int i = rank + 1; i < n; i++)
			if(A[i].test(p)){
				A[i] ^= A[rank];
			}
//		loop(i, n) loop(j, m) cerr << A[i].test(j) << " \n"[j==m-1];
//		cerr << endl;
		rank++;
	}	
	return rank;
}

void tc(){
	int n, m = sz(primes); scanf("%d", &n);
	int free = 0;
	static vector<vi> aux;
	aux.clear();
	loop(i, n){
		ll x; scanf("%lld", &x);
		aux.emplace_back();
		loop(j, m){
			int v = 0;
			while(x%primes[j] == 0){
				v ^= 1;
				x /= primes[j];
			} 
			if(v) aux.back().push_back(j);
		} 
		if(aux.back().empty()) {
			free++;
			aux.pop_back();
		}
	}
	n = sz(aux);
	matrix A(n);
	loop(i, n) {
		for(int j : aux[i])
			A[i].set(j);
	}
	int rank = gauss(A, n, m);
//	cerr << rank << " " << free << endl;
	unsigned long long ans = 1;
	ans <<= n - rank + free;
	ans--;
	printf("%llu\n", ans);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	init();
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
