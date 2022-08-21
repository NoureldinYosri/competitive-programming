#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
using vi = std::vector<int>;
using pi = std::pair<int,int>;
using vp = std::vector<pi>;
using ll = long long;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
void tc();
auto test_cases = [](){
	int T; scanf("%d", &T);
	while(T--) tc();
};
using namespace std;


const int MAXA = 200*1000 + 10;
int P[1 << 20], n, m;
int loc[1 << 20];
int L[1 << 20], R[1 << 20];
int prime[1 << 20];
list<int> divs[1 << 20];

void sieve() {
	for(int i = 2; i < MAXA; i++)
		if(!prime[i]) {
			prime[i] = i;
			for(ll j = i*(ll)i; j < MAXA; j += i)
				prime[j] = i;
		}
	divs[1].push_back(1);
	for(int i = 2; i < MAXA;i ++) {
		int p = prime[i], n = i, e = 0;
		while(n%p == 0) n /= p, e++;
		ll q = 1;
		while(e-- >= 0) {
			for(int x : divs[n]) divs[i].push_back(x*q);
			q *= p;
		}

		if(i < 10) {
			print(divs[i], int);
		}
	}
}

void preprocess() {
	loop(i, n) loc[P[i]] = i;
	vi ST;
	loop(i, n) {
		while(!ST.empty() && A[ST.back()] < A[i]) ST.pop_back();
		L[i] = ST.empty() ? -1 : ST.back();
		ST.push_back(i);
	}
	ST.clear();
	for(int i = n-1; i >= 0; i--) {
		while(!ST.empty() && A[ST.back()] < A[i]) ST.pop_back();
		R[i] = ST.empty() ? n : ST.back();
		ST.push_back(i);
	}
	
	for(int p = 1; p <= n; p++) {
		for(int a : divs[p]) {
			int b = p / a;
			if(a >= b) continue;
			int s = loc[a], e = loc[b];
			if(s > e) swap(s, e);
			if(s <= L[p] || R[p] <= e) continue;
			if(e < loc[p]) e = loc[p];
			if(s > loc[p]) s = loc[p];
			int l = L[p] + 1, r = R[p] - 1;
			// l <= s <= loc[p] <= e <= r
			
		}
	}
	
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	sieve();
	scanf("%d %d", &n, &m);
	loop(i, n) scanf("%d", P + i);
	preprocess();
	return 0;
}
