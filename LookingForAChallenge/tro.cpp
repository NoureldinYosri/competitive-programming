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




int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	vi L;
	for(int x; scanf("%d", &x) == 1 && x && sz(L) < 100;) L.pb(x);

	if(sz(L) <= 10*1000){
		sort(all(L));
		for(int i = 0;i + 1 < sz(L); i++){
			int low = L[i + 1] - L[i];
			int high = L[i + 1] + L[i];
			int j = upper_bound(all(L), low) - L.begin();
			while(j == i || j == i+1) j++;
			if(j < sz(L) && L[j] < high) {
				printf("%d %d %d\n", L[i], L[i+1], L[j]);
				return 0;
			}
		}
		puts("NIE");		
	}
	else {
		for(int t = 0; t < 100*1000; t++){
			int i, j, k;
			for(bool done = 0; !done; ){
				i = rand()%sz(L);
				j = rand()%sz(L);
				k = rand()%sz(L);
				done = !(i == j || j == k || i == k);
			}
			int A[] = {L[i], L[j], L[k]};
			sort(A, A + 3);
			if(A[2] < A[0] + A[1]){
				printf("%d %d %d\n", A[0], A[1], A[2]);
				return 0;
			}
		}
		puts("NIE");
	}
	return 0;
}
