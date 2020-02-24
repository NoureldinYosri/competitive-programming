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
	st << std::fixed << std::setprecision(3) << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

const int MAXN = 20;
double P0[4];
vector<pair<double, ll>> A;
int n;
double powers[4][MAXN + 1];

ll fact[MAXN+1];
vi aux;

void bt(int i, int r, double p, ll c){
	if(i == 4){
		assert(!r);
		A.emplace_back(p, c);
//		cout << p << " " << c << ": ";
//		print(aux, int);
		return;
	}
	int lo = (i == 3) * r;
	int hi = r;
	for(int x = lo; x <= hi; x++){
		aux.pb(x);
		bt(i+1, r-x, p * pow(P0[i], x), c / fact[x]);
		aux.pop_back();
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	fact[0] = 1;
	for(int i = 1; i <= MAXN;i++)
		fact[i] = i * fact[i - 1];

	scanf("%d",&n);
	loop(i, 4) scanf("%lf", P0 + i);
		
		
	bt(0, n, 1, fact[n]);
	double s = 0;
	for(auto p : A) s += p.first * p.second;
//	cout << s << endl;
	
	double ans = 0;

	multiset<pair<double, ll> > S{all(A)};
	
	while(!S.empty()){
		auto p = *S.begin();
		S.erase(S.begin());
		
		if(p.second == 1){
			if(S.empty()) break;
			auto q = *S.begin(); S.erase(S.begin());
			q.second--;
			if(q.second) S.insert(q);
			ans += q.first + p.first;
			S.emplace(q.first + p.first, 1);
		}
		else {
			if(p.second & 1){
				S.emplace(p.first, 1);
				p.second ^= 1;
			}
			ans += p.second * p.first;
			S.emplace(p.first*2, p.second / 2);
		}
//		for(auto t : S) cout << t ;
//		cout << endl;
	}
		
	printf("%.10f\n", ans);
	return 0;
}
