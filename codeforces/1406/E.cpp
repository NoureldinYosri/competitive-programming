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

const int MAXA = 100*1000;
vi primes;
int smallestPrime[MAXA + 1];

void sieve(){
	iota(smallestPrime, smallestPrime + MAXA + 1, 0);
	for(int i = 2; i <= MAXA; i++)
		if(smallestPrime[i] == i){
			primes.pb(i);
			for(ll j = i*(ll)i; j <= MAXA; j += i)
				smallestPrime[j] = min(smallestPrime[j], i);
		}
}

int read(){
	int r; scanf("%d", &r);
	return r;
}

int ask(int a, char c = 'B'){
	printf("%c %d\n", c, a);
	fflush(stdout);
	return read();
}

bool tried[1 << 20];
int n;

int Expected(const vi & g){
	int f = 0;
	for(int x = 2; x <= n; x++){
		int l = g[0], r = g.back();
		if(l <= smallestPrime[x] && smallestPrime[x] <= r)
			f++;
	}
	return f;
}

int main(){
	sieve();
	n = read();
	int ans = 1;
	for(int p : primes) {
		if(p*(ll)p > n) continue;
		if(ans*(ll)p > n) continue;
		if(ask(p) == 0) continue;
		tried[p] = true;
		if(ans == 1 && ask(ans*p) == 0) continue;
		vi powers;
		for(ll q = ans*p; q <= n; q *= p) powers.pb(q);
		int s = 0, e = sz(powers) - 1;
		while(s < e){
			int m = s + (e-s+1)/2;
			if(ask(powers[m])) s = m;
			else e = m-1;
		}
		ans = powers[s];
	}
	vector<vi> groups;
	for(int p : primes) {
		if(tried[p]) continue;
		if(ans*(ll)p > n) break;
		if(groups.empty() || groups.back().size() == 100) groups.emplace_back();
		groups.back().push_back(p);
	}
	int c0 = ask(1, 'A');
	for(auto & g : groups){
		for(int p : g){
			ask(ans*p);
		}
		int c = ask(1, 'A');
		int lost = c - c0;
		if(lost != Expected(g)) {
			for(int p : g) {
				if(ask(p)) {
					ans *= p;
					break;
				}
			}
			break;
		}
		c0 = c;
	}

	printf("C %d\n", ans);
	return 0;
}
