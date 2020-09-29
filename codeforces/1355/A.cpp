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



void get_digits(ll x, int & a, int & b){
	a = 9;
	b = 0;
	while(x){
		int d = x%10;
		x /= 10;
		a = min(a, d);
		b = max(b, d);
	}
}


void f(ll x, int num){
	if(num == 0) return cout << endl, void();
	int a, b;
	get_digits(x, a, b);
	cout << x << " ";
	f(x + a*b, num-1);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		ll a, K;  scanf("%lld %lld", &a, &K);
		while(K > 1){
			K--;
			int l, h;
			get_digits(a, l, h);
			if(l == 0) break;
			a += l*h;
		}
		printf("%lld\n", a);
	}
	return 0;
}
