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


int A[3];
vi ord;

int solve(){
	int ret = 0;
	int B[3];
	ord.clear();
	loop(i, 8) if(i) ord.pb(i);
	do{
		copy(A, A + 3, B);
		int tmp = 0;
		for(int m : ord){
			int u = 1;
			loop(i, 3) if(m & (1 << i)) u = min(u, B[i]);
			tmp += u;
			if(!u) break;
			loop(i, 3) if(m & (1 << i)) B[i] -= u;		
		}
		ret = max(ret, tmp);
	}while(next_permutation(all(ord)));
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d\n", &T);
	while(T--){
		loop(i, 3) scanf("%d", A + i);
		printf("%d\n", solve());
	}
	return 0;
}
