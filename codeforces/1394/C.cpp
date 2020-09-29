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

const int M = 1000;

pi read(){
	static char buffer[1 << 20];
	scanf("%s", buffer);
	pi ret(0, 0);
	for(char *ptr = buffer; *ptr; ptr++){
		ret.first += *ptr == 'B';
		ret.second += *ptr == 'N';
	}
	return ret;
}


void update(pi & info, int x){
	info.first = min(info.first, x);
	info.second = max(info.second, x);
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

vi stratify(pi lim){
	auto [l, r] = lim;
	int step = max((r-l)/M, 1);
	vi V;
	for(int x = l; x <= r; x += step)
		V.pb(x);
	shuffle(all(V), rng);
	return V;
}

pair<int, pi> ans(INT_MAX, pi(0, 0));
vp P;

int fitness(pi q){
	int ret = 0;
	for(auto p : P){
		int dx = p.first - q.first;
		int dy = p.second - q.second;
		if(dx*(ll)dy >= 0) ret = max(ret, max(abs(dx), abs(dy)));
		else ret = max(ret, abs(dx) + abs(dy));
	}
	if(q.first + q.second)
		ans = min(ans, mp(ret, q));
	return ret;
}

void search(int b, int n){
	int f0 = fitness(pi(b, n));
	for(int T = 30, ctr = 0; T && ctr < 10; T--){
		pi nxt(b, n);
		int fn = f0;
		loop(i, 20){
			int db = rng()%19 - 10;
			int dn = rng()%19 - 10;
			int xb = b + db, xn = n + dn;
			if(!(xb >= 0 && xn >= 0 && xb + xn)) continue;
			int ft = fitness(pi(xb, xn));
			if(ft < f0){
				fn = ft;
				nxt = pi(xb, xn);
				ctr = 0;
			}
		}
		ctr++;
		tie(b, n) = nxt;
		f0 = fn;
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n ; scanf("%d", &n);
	P.resize(n);
	pi LB(INT_MAX, INT_MIN), LN(INT_MAX, INT_MIN);
	for(auto & p : P){
		p = read();
		update(LB, p.first);
		update(LN, p.second);
	}
	
	vi B = stratify(LB), N = stratify(LN);
	
	int m = min(sz(B), sz(N));
	
	loop(i, m){
		search(B[i], N[i]);
	}

	printf("%d\n", ans.first);
	auto [rb, rn] = ans.second;
	loop(i, rb) putchar('B');
	loop(i, rn) putchar('N');
	puts("");
	return 0;
}
