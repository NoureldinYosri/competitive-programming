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
const int oo = 1 << 29;

ll ST[MAX], LA[MAX];
pair<int, pi> monster[MAX];
int n, m, p;
pi sord[MAX], shield[MAX];
map<int, int> M;
map<int, int> initial_profit;


void build(int cur, int s, int e){
	LA[cur] = 0;
	if(s == e) {
		ST[cur] = -(1LL << 60);
		if(initial_profit.count(s))
			ST[cur] = initial_profit[s];
		return;
	}
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	build(left, s, m);
	build(right, m+1, e);
	ST[cur] = max(ST[left], ST[right]);
}

void update(int cur, ll v){
	ST[cur] += v;
	LA[cur] += v;
}

void push_down(int cur){
	if(!LA[cur]) return;
	int left = 2*cur + 1, right = left + 1;
	update(left, LA[cur]);
	update(right, LA[cur]);
	LA[cur] = 0;
}

void update(int cur, int s, int e, int l, int r, int v){
	if(l <= s && e <= r) return update(cur, v);
	push_down(cur);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(r <= m) update(left, s, m, l, r, v);
	else if(m < l) update(right, m+1, e, l, r, v);
	else {
		update(left, s, m, l, m, v);
		update(right, m+1, e, m+1, r, v);
	}
	ST[cur] = max(ST[left], ST[right]);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d", &n, &m, &p);
	loop(i, n) scanf("%d %d", &sord[i].first, &sord[i].second);
	loop(i, m) scanf("%d %d", &shield[i].first, &shield[i].second);
	loop(i, p) scanf("%d %d %d", &monster[i].first, &monster[i].second.first, &monster[i].second.second);
	
	loop(i, m) M[shield[i].first];
	loop(i, p) M[monster[i].second.first];
	int z = 0;
	for(auto & q : M) q.second = z++;
	
	loop(i, m) shield[i].first = M[shield[i].first];
	loop(i, p) monster[i].second.first = M[monster[i].second.first];
	loop(i, m){
		int x = shield[i].first;
		int v = shield[i].second;
		if(initial_profit.count(x)) initial_profit[x] = max(initial_profit[x], -v);
		else initial_profit[x] = -v;
	}
	build(0, 0, sz(M)-1);
	
	sort(sord, sord + n);
	sort(monster, monster + p);
	int j = 0;
	ll ans = LLONG_MIN;
	loop(i, n){
		while(j < p && monster[j].first < sord[i].first){
//			cerr << "insert " << monster[j] << endl;
			int x = monster[j].second.first;
			int v = monster[j].second.second;
			if(x+1 < sz(M)) update(0, 0, sz(M)-1, x+1, sz(M)-1, v);
			j++;
		}
		ll tmp = ST[0] - sord[i].second;
//		cerr << "at " << sord[i] << " " << tmp << " " << ST[0] << endl;
		ans = max(ans, tmp);
	}
	cout << ans << endl;		
	return 0;
}
