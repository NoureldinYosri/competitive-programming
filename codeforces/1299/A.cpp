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


const int MAX = 100*1000 + 10;
int A[MAX], n;

int solve(){
	vi who[32];
	loop(i, n){
		int x = A[i];
		for(int j = 0; x; j++, x>>= 1){
			if(x & 1) who[j].pb(i);
		}
	}
//	prArr(A, n, int);
	for(int b = 31;b >= 0;b--){
		//print(who[b], int);
		if(sz(who[b]) == 1){
			int i = who[b][0];
			if(i) {
			//	cerr << A[i] << " with " << A[0] << endl;
				swap(A[i], A[0]);
			}
			break;
		}
	}

/*	sort(A, A + n, [x](const int & a, const int & b){
		return (a & x) > (b & x);
	});
*/	int f = A[0];
	for(int i = 1;i < n;i++)
		f = (f | A[i]) - A[i];
	return f;
}

int bf(){
	vi ord;
	loop(i, n) ord.pb(i);
	int ret = 0;
	do{
		int f = A[ord[0]];
		for(int i = 1;i < n;i++)
			f = (f | A[ord[i]]) - A[ord[i]];
		ret = max(ret, f);
	}while(next_permutation(all(ord)));
	return ret;
}

void test(){
	n = rand()%5 + 1;
	loop(i, n) A[i] = rand()%17;
	int res = solve();
	int ans = bf();
	if(res != ans){
		cerr << "expected " << ans << " found " << res << endl;
		prArr(A, n, int);
		exit(0);
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	/*for(int t = 1;;t++){
		test();
		cout << "test " << t << endl;
	}
	*/
	scanf("%d", &n);
	loop(i, n) scanf("%d", A +i );
	int f = solve();
	cerr << f << endl;
	loop(i, n) printf("%d%c", A[i], " \n"[i==n-1]);
	return 0;
}
