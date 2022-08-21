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

const int billion = 1000000000;
int n, m;
int A[1 << 20];
map<int, int> cnt;
vp B;

int getDiameter() {
	static vi ST;
	int mn = *min_element(A, A + n);
	int dia = 0;
	ST.clear();
	for(int i = 1; i < n;i ++){
		int e = min(A[i - 1], A[i]);
		// cerr << i-1 << " " << i << " => " << e << " vs " << 2*mn << " " << mn << endl;
		dia = max(dia, min(e, 2*mn));
	}
	return dia;
}

set<pi> E, S;

void add(int i) {
	int v = min(A[i - 1], A[i]);
	if(v == billion) return;
	E.emplace(v, i);
}

void change(int i, int &m) {
	if(m == 0) return;
	cerr << "kill " << pi(i, A[i]) << endl;
	S.erase(pi(A[i], i));
	A[i] = billion;
	m--;
	S.emplace(A[i], i);
	add(i);
	if(i + 1 < n) add(i + 1);
}

void tc() {
	scanf("%d %d", &n, &m);
	loop(i, n) scanf("%d", A + i);
	E.clear();
	S.clear();
	for(int i = 1; i < n; i++)
		E.emplace(min(A[i - 1], A[i]), i);
	loop(i, n) S.emplace(A[i], i);
	while(!E.empty() && m) {
		auto [v, i] = *E.rbegin();
		if(v != min(A[i - 1], A[i])){
			E.erase(pi(v, i));
			continue;
		}
		if(v < 2*S.begin()->first) {
			cerr << "mood 1 " << pi(v, i) << endl;
			E.erase(pi(v, i));
			if(A[i] == v) {
				change(i, m);
			} else {
				change(i - 1, m);
			}
		} else {
			int mn = S.begin()->first;
			while(m && !S.empty() && S.begin()->first == mn) {
				cerr << "mood 2 " << (*S.begin()) << endl;
				change(S.begin()->second, m);
			}
		}
	}
	// for(auto p : S) cerr << p;
	// cerr << endl;
	// cerr << "m = " << m << endl;
	// for(auto p : S) {
	// 	change(p.second, m);
	// }
	// prArr(A, n, int);	
	printf("%d\n", getDiameter());
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
