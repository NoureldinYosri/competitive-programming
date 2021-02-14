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


int n;
ll T;
string S;

ll f(char c){
	return 1LL << (c - 'a');
}

void no(){
	puts("No");
	exit(0);
}


void makeIt(int b, ll want, vi & ctr){
	for(int i = b-1; i >= 0; i--){
		want <<= 1;
		ll got = min((ll)ctr[i], want);
		want -= got;
		ctr[i] -= got;
		if(want == 0) return;
	}
	no();
}

set<ll>* mem[10][10];

set<ll>* bf(int s, int e){
	if(mem[s][e]) return mem[s][e];
	mem[s][e] = new set<ll>();
	if(s == e) {
		mem[s][e]->insert(f(S[s]));
		return mem[s][e];
	}
	for(int m = s; m < e; m++){
		auto & L = *bf(s, m);
		auto & R = *bf(m+1, e);
		for(auto l : L) for(auto r : R) mem[s][e]->insert(-l + r);
	}
	return mem[s][e];
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> n >> T >> S;
	if(n <= 10){
		auto V = bf(0, n-1);
		puts(V->count(T) ? "Yes" : "No");
		return 0;
	}
	T -= f(S[n-1]);
	T += f(S[n-2]);
	
	T = abs(T);
	
	n -= 2;
	loop(i, 2) S.pop_back();
	
	const int B = 60;
	vi ctr(60, 0);
	for(char c : S) ctr[c - 'a'] ++;
	vi want(B, 0);
	for(int b = 0; b < B; b++) want[b] = (T >> b) & 1;
	
	for(int b = B-1; b >= 0; b--){
		if(want[b]){
			if(ctr[b] == 0) {
				makeIt(b, 1, ctr);
				ctr[b] = 0;
			}
			else ctr[b]--;
		} 
		ctr[b] &= 1;
		if(ctr[b]) {
			makeIt(b, ctr[b], ctr);
		}
	}
	
	puts("Yes");
	return 0;
}
