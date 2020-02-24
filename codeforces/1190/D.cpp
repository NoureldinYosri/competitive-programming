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

const int MAXN = 2*100*1000 + 10, MAXST = 1 << 20;
pi P[MAXN];
int n;

int BIT[MAXN];
void add(int p, int v){
	for(;p;p ^= LSOne(p))
		BIT[p] += v;
}
int get(int p){
	int ret = 0;
	for(;p < MAXN; p += LSOne(p))
		ret += BIT[p];
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	map<int, int> M;
	loop(i, n) {
		scanf("%d %d",&P[i].second, &P[i].first);
		P[i].first *= -1;
		M[P[i].second];
	}
	sort(P, P + n);
	loop(i, n) P[i].first *= -1;
	
	int m = 0;
	for(auto & p : M) p.second = ++m;
	loop(i, n) P[i].second = M[P[i].second];

	vi Xs;
	ll ans = 0;
	set<int> S;
	for(int i = 0;i < n;){
		int y = P[i].first;
		int j = i;
		Xs.clear();
		while(j < n && P[j].first == y) {
			Xs.pb(P[j].second);
			j++;
		}
		for(int x : Xs) if(!S.count(x)) add(x, 1), S.insert(x);
		int prv = 0;
		for(int x : Xs){
			ll left = get(prv+1) - get(x+1);
			ll right = get(x);
//			cout << x << " " << left << " " << right << endl;
			ans += left * right;
			prv = x;
		}		
		i = j;
	}
	
	cout << ans << endl;
	return 0;
}
