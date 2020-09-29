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


const double eps = 1e-4;
int n, D;
int A[1 << 20];
double pref[1 << 20];

pair<int, pi> can(double avg){
	static vector<pair<double, int>> V;
	V.clear();
	V.emplace_back(0, -1);
	double sum = 0;
	loop(i, n){
		sum += A[i] - avg;
		pref[i] = sum;
		V.emplace_back(sum, i);
	}
	sort(all(V));
	int l = n;
	pair<int, pi> best;
	for(auto [_, r] : V){
		if(l < r){
			best = max(best, mp(r - l, pi(l + 1, r)));
		}
		l = min(l, r);
	}
	return best;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &D);
	loop(i, n) scanf("%d", A + i);
	double s = 0, e = *max_element(A, A + n);
	for(int t = 0; e-s > eps && t < 70; t++){
		double m = s + (e-s)/2;
		if(can(m).first >= D) s = m;
		else e = m;
	}
	auto best = can(s);
	auto [l, r] = best.second;
	cout << l+1 << " " << r+1 << endl;
	
	return 0;
}
