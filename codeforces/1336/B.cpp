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


vi A[3];

void read(){
	loop(i, 3){
		A[i].clear();
		int len; scanf("%d", &len);
		A[i].resize(len);
	}
	loop(i, 3){
		for(int & x : A[i]) scanf("%d", &x);
		sort(all(A[i]));
		A[i].resize(unique(all(A[i])) - A[i].begin());
//		print(A[i], int);
	}
}

ll cost(ll a, ll b, ll c){
	ll X[] = {a, b, c};
	ll ret = 0;
	loop(i, 3) loop(j, i) ret += (X[i] - X[j])*(X[i] - X[j]);
//	cerr << a << " " << b << " " << c << " " << ret << endl;
	return ret;
}

ll solve(){
	int ord[3] = {0, 1, 2};
	ll ret = LLONG_MAX;
	do{
		int a = ord[0], b = ord[1], c = ord[2];
		for(int x : A[a]){
			auto ptr = lower_bound(all(A[b]), x);
			if(ptr == A[b].end()) break;
			int y = *ptr;
			ptr = upper_bound(all(A[c]), x);
			if(ptr != A[c].begin()){
				ptr--;
				int z = *ptr;
				ret = min(ret, cost(x, y, z));
			}
		}
		
	}while(next_permutation(ord, ord + 3));
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		read();
		printf("%lld\n", solve());
	}
	return 0;
}
