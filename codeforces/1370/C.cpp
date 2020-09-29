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

vi get_divs(int n){
	vi D;
	for(int i = 1; i*i <= n; i++)
		if(n%i == 0){
			D.pb(i);
			if(i != n/i) D.pb(n/i);
		}
	return D;
}

map<int, int> dp;
int guess(int n){
	if(n == 1) return 1;
	int m = n, s = 0;
	while(m%2 == 0) m >>= 1, s++;
	if(m == 1) return !guess(n-1);
	else return !guess(1 << s);
}

void bf(int N){
	vi is_winner(N+1, 0);
	vi grundy(N+1, 0);
	for(int n = 1; n <= N; n++){
		is_winner[n] = !is_winner[n-1];
		set<int> S; S.insert(grundy[n-1]);
		vi divs = get_divs(n);
		while(!divs.empty() && !is_winner[n]){
			int d = divs.back(); divs.pop_back();
			if((d&1) && (d > 1)) {
				is_winner[n] = !is_winner[n/d];
				S.insert(grundy[n/d]);
			}
		}
		while(S.count(grundy[n])) grundy[n]++;
		int m = n, s = 0;
		while(m%2 == 0) m >>= 1, s ++;
		if(n == LSOne(n)) cerr << n << ": " << is_winner[n] << " " << guess(n) << endl;
	}
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	PRESTDIO();
	int T; cin >> T;
	while(T--){
		int n; cin >> n;
		bool is_one = n == 1;
		bool is_proper_p2 = n > 2 && (n == LSOne(n));
		bool is_double_prime = n%2 == 0 && sz(get_divs(n >> 1)) == 2;
		if(is_one || is_proper_p2 || is_double_prime) puts("FastestFinger");
		else puts("Ashishgup");	

	}
	return 0;
}
