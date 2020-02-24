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
int A[MAX], T[MAX], n;
vi ord;

map<int, int> L;
int get(int x){
	auto ptr = L.lower_bound(x);
	if(ptr == L.end()) return x;
	int l = ptr->second;
	int r = ptr->first;
	if(x < l) return x;
	return r+1;
}

void insert(int x){
	auto ptr = L.emplace(x, x).first;
	auto nxt = ptr;
	auto prv = ptr;
	if(prv != L.begin()) prv--;
	nxt++;
	int l1 = prv->second;
	int r1 = prv->first;
	
	
	int l = x, r = x;
	
	if(r1+1 == x){
		L.erase(prv);
		l = l1;
	}
	
	if(nxt != L.end() && nxt->second-1 == x){
		r = nxt->first;
		L.erase(nxt);
	}
	if(r != x) L.erase(x);
	
	L[r] = l;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i);
	loop(i, n) scanf("%d", T + i);
	loop(i, n) ord.pb(i);
	sort(all(ord), [](const int & a, const int & b){
		return T[a] > T[b];
	});
	ll ans = 0;
	for(int i : ord){
		int x = A[i];
		auto ptr = L.lower_bound(x);
		int y = get(x);
//		cerr << i << ": " << x << " -> " << y << endl;
		ans += (y-x+0LL)*T[i];
		insert(y);
//		for(auto p : L) cerr << p << endl;
	}
	cout << ans << endl;
	return 0;
}
