
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
 
const int MAX = 200*1000 + 10;
 
int L[MAX],R[MAX], n;
vi ord;

vi BIT;
void add(int p, int v){
	for(;p < sz(BIT);p += LSOne(p))
		BIT[p] += v;
}
int get(int p){
	int ret = 0;
	for(;p;p ^= LSOne(p))
		ret += BIT[p];
	return ret;
}

int is_good[MAX];
int pref[MAX];
int in_deg[MAX];

int solve(vi & V){
	if(V.empty()) return 0;
//	for(int i : V) cout << pi(L[i], R[i]) ;
//	cout << endl;
	int ret = sz(V) > 1;
	for(int i = 0;i < sz(V);i++){
		int j = V[i];
		int l = L[j];
		int in = i - get(l - 1);
		is_good[i] = in == 1;
		add(R[j], 1);
	}
	for(int i : V) add(R[i], -1);
	loop(i,sz(V)) pref[i] = is_good[i] + (i ? pref[i-1] : 0);
	loop(i,sz(V)){
		auto ptr = lower_bound(all(V), R[V[i]] + 1, [](const int & a,const int & k){
			return L[a] < k;
		});
		int j = ptr - V.begin(); j--;
		int cnt = pref[j] - pref[i];
//		cout << i << " " << cnt << endl;
		ret = max(ret, cnt + (i > 0));
	}
//	cout << "ret " << ret << endl;
	return ret;
}

void compress(){
	static vi vals;
	vals.clear();
	loop(i,n) vals.pb(L[i]),vals.pb(R[i]);
	sort(all(vals));
	vals.resize(unique(all(vals)) - vals.begin());
	loop(i,n){
		L[i] = upper_bound(all(vals),L[i]) - vals.begin();
		R[i] = upper_bound(all(vals),R[i]) - vals.begin();
	}
	BIT.resize(sz(vals)+1,0);
}

vi aux;
int solve(){
	compress();
	ord.clear();
	loop(i,n) ord.pb(i);
	sort(all(ord), [](const int & a,const int & b){
		return tie(L[a], R[a]) < tie(L[b], R[b]);
	});

	int e = -1;
	int cnt = 0,mx = 0;
	vi subset;
	for(int i : ord){
		if(L[i] > e){
			cnt++;
			mx = max(mx, solve(subset));
			subset.clear();
			e = L[i];
		}
		e = max(e, R[i]);
		subset.pb(i);
	}
	mx = max(mx, solve(subset));
	return cnt - 1 + mx;
}
 
int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T;  scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		loop(i,n) scanf("%d %d",L+i, R+i);
		printf("%d\n",solve());
	}
	return 0;
}
