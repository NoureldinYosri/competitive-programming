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

const long double eps = (1.0/(long double)999999999 - 1e-9)*0.9;
vi aux;
int n, K, h;

bool can(long double t, const vector<pair<pi, int>> & A){
	aux.clear();
	for(auto [p, i] : A){
		auto [_, v] = p; 
		ll big = floor(t*v + eps);
		if(big > sz(aux)){
			aux.pb(i);
		}
		if(sz(aux) == K) return true;
	}
	return false;
}

auto cmp = [](const pi & a, const pi & b){
	return a.first*(ll)b.second < a.second*(ll)b.first;
};

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d", &n, &K, &h);
	vector<pair<pi, int>> A(n);
	loop(i, n) A[i].second = i+1;
	for(auto & [p, _] : A) scanf("%d", &p.first);
	for(auto & [p, _] : A) scanf("%d", &p.second);
	sort(all(A));
	long double s = 0, e = K;
	for(int t = 0; e-s > eps && t < 85; t++){
		long double m = s + (e-s)/2.0;
		if(can(m, A)) e = m;
		else s = m ;
	}
	can(e, A);
	vi speed(n + 1);
	for(auto [p, i] : A) speed[i] = p.second;
	pi t(0, 1);
	loop(i, K) {
		printf("%d ", aux[i]);
		t = max(t, pi(i+1, speed[aux[i]]), cmp);
	}
	puts("");
	cerr << "time is " << t << " ~ " << t.first/(double)t.second << endl;
	return 0;
}
