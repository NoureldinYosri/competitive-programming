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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

const int MAX = 300*1000 + 10;
int W[MAX],id[MAX];
bool inForest[MAX];
ll S[MAX];
int n,m,A[MAX];
vi G[MAX];

void init(){
	loop(i,n+1) W[i] = 1,id[i] = i,S[i] = A[i];
}
int find(int a){
	return id[a] = (a == id[a]) ? a : find(id[a]);
}
void join(int a,int b) {
	a = find(a),b = find(b);
	if(a == b) return;
	if(W[a] < W[b]) swap(a,b);
	W[a] += W[b];
	id[b] = a;
	S[a] += S[b];
	m--;
}
void insert(int u) {
	m++;
	inForest[u] = 1;
	for(int v : G[u]) if(inForest[v]) {
		int a = find(u),b = find(v);
		if(a == b) continue;
		ll s = S[a] + S[b];
		if(s > S[a] && s > S[b])
			join(u,v);
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	vi ord;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",A + i),ord.push_back(i);
	loop(e,n-1) {
		int a,b; scanf("%d %d",&a,&b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	sort(all(ord),[](const int & a,const int & b) {
		return A[a] > A[b];
	});
	init();
	pair<ll,ll> ans(-1e15,1);
	auto cmp = [](const pair<ll,ll> & a,const pair<ll,ll> &b) {
		ll diff = a.first*b.second - b.first*a.second;
		if(diff == 0) return a.second < b.second;
		return diff < 0;
	};
	ll s = 0;
	for(int u : ord) {
		insert(u);
		s += A[u];
		pi cand(s,m);
		if(cmp(ans,cand)) ans = cand;
	}
	s = 0;
	m = 0;
	for(int u : ord) {
		s += A[u];
		m ++;
		ll g = __gcd(ans.second,abs(ans.first));

		ll x = (ans.second/g)*s;
		ll y = ans.first/g;
		if(y){
			if(abs(x)%abs(y) == 0) {
				ll k = x/y;
				pair<ll,ll> cand(s,k);
				if(k > ans.second && k <= m && cmp(ans,cand))
					ans = cand;
			}
		}
		else {
			if(s == 0) ans.second = max(ans.second,m + 0LL);
		}
	}
	cout << ans.first << " " << ans.second << endl;
	return 0;
}
