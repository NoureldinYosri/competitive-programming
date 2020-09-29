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
	PRESTDIO();
	int n; cin >> n;
	vi A(n);
	for(int & x : A) {
		cin >> x;
		x &= 1;
	}

	vi V;
	for(int x : A){
		int y = x;
		while(!V.empty() && y != 2){
			if(V.back() == y){
				V.pop_back();
				y = 2;
			} else if (V.back() == 2){
				V.pop_back();
			} else break;
		}
		V.push_back(y);
	
	}
	bool seen[3] = {0, 0, 0};
	for(int x : V){
		seen[x] = 1;
	}
	if(seen[0] && seen[1]) puts("NO");
	else puts("YES");
	return 0;
}
