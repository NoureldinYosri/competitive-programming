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
	int n, D, m; scanf("%d %d %d", &n, &D, &m);
	vi A(n);
	for(int & a : A) scanf("%d", &a);
	sort(all(A));
	vi B;
	while(!A.empty() && A.back() > m) {
		B.pb(A.back());
		A.pop_back();
	}
	reverse(all(B));

	
	vi R(n, -1);
	loop(i, sz(A)) R[i] = A[i];
	for(int i = sz(A); i < n; i += D + 1){
		R[i] = B.back();
		B.pop_back();
	}
	vi pos;
	for(int i = n-1; i >= 0; i--) if(R[i] == -1){
		pos.pb(i);
	}

	for(int i = 0; i + D + 1 <= sz(A) && !B.empty(); i += D + 1){
		ll sum = 0;
		loop(j, D + 1) sum += R[i + j];
		while(!B.back() && B.back() <= sum){
			R[pos.back()] = B.back();
			B.pop_back();
			pos.pop_back();
		}
		if(!B.empty()){
			R[pos.back()] = R[i];
			R[i] = B.back();
			pos.pop_back();
			B.pop_back();			
		}
	}

	print(R, int);

	ll ans = 0;
	for(int i = 0; i < n; ) {
		int a = R[i++];
		ans += a;
		if(a > m) i += D;
	}
	cout << ans << endl;
	return 0;
}

