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

const int MAX = 1 << 20;
vi ans;
ll best;

int lim[MAX];
int A[MAX], n;

void work(int p){
	for(int i = p, h = INT_MAX; i < n;i++){
		h = min(h, lim[i]);
		A[i] = h;
	}
	
	for(int i = p, h = INT_MAX; i >= 0;i--){
		h = min(h, lim[i]);
		A[i] = h;
	}
	
	ll sum = 0;
	loop(i, n) {
		sum += A[i];
		assert(A[i] <= lim[i]);
	}
	if(sum >= best){
		best = sum;
		ans.clear();
		loop(i, n) ans.pb(A[i]);
	}
}

ll L[1 << 20], R[1 << 20];

ll get_best(){
	vi ST;
	loop(i, n){
		ll h = lim[i];
		while(!ST.empty() && lim[ST.back()] > h) ST.pop_back();
		L[i] = ST.empty() ? 0 : L[ST.back()];
		L[i] += h*(i - (ST.empty() ? -1 : ST.back()));
		ST.pb(i);
	}
	ST.clear();
	for(int i = n-1;i >=0 ; i--){
		ll h = lim[i];
		while(!ST.empty() && lim[ST.back()] > h) ST.pop_back();
		R[i] = ST.empty() ? 0 : R[ST.back()];
		R[i] += h*((ST.empty() ? n : ST.back()) - i);
		ST.pb(i);
	}
	int c = 0;
	ll best = 0;
	loop(i, n){
		ll sum = L[i] + R[i] - lim[i];
		if(sum >= best){
			best = sum;
			c = i;
		}
	}
//	cerr << best << endl;
	return c;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) scanf("%d", lim + i);
	int p = get_best();
	work(p);
	loop(i, n) printf("%d ", ans[i]);
	puts("");
	return 0;
}
