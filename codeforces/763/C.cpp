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

int n, m;
int A[1 << 20];
int st;

bool check(int d){
//	cerr << "check " << d << endl;
	static set<int> done;
	d %= m;
	if(done.count(d)) return false;
	done.insert(d);
	int ctr = 0, y = -1;
	loop(i, n){
		int x = (A[i] + d)%m;
		if(!binary_search(A, A + n, x)) {
			ctr++;
			y = x;
		}
	}
	if(ctr > 1) return false;
	
	if(y == -1){
		assert(ctr == 0);
		st = A[0];
	} else {
		loop(i, n) {
			y -= d;
			y = (y%m + m)%m;
		}
		st = y;
	}
	
	return true;
}


void appendDiffs(vi & C){
	vi B;
	int a = 0;
	while(a < m && sz(B) < n){
		if(!binary_search(A, A + n, a)) B.pb(a);
		a++;
	}
	loop(i, sz(B)) C.pb(B[i] - B[(i+1)%sz(B)]);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &m, &n);
	loop(i, n) scanf("%d", A + i);
	if(n == 1){
		printf("%d %d\n", A[0], 1);
		return 0;
	}
	sort(A, A + n);
	//prArr(A, n, int);
	vi C;
	loop(i, n){
		int j = (i + 1)%n;
		C.pb(A[j] - A[i]);
	}
	
	appendDiffs(C);

	for(int & x : C) x = abs(x);

	sort(all(C));
	C.resize(unique(all(C)) - C.begin());

	
	for(int x : C){
		for(int d = 1; d*d <= x && d < m; d++){
			if(x%d == 0){
				if(check(d)) {
					printf("%d %d\n", st, d);
					return 0;
				}
				if(d != x/d && check(x/d)){
					printf("%d %d\n", st, (x/d)%m);
					return 0;				
				}
			}
		}		
	}
	puts("-1");
	
	return 0;
}
