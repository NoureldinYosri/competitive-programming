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

const int MAXST = 1 << 20;
vi aux;
vector<pi> V[2];
int ST[2][MAXST];
int LA[2][MAXST];

void update(int cur, int v, int *ST, int *LA){
	ST[cur] += v;
	LA[cur] += v;
}
void push_down(int cur, int *ST, int *LA){
	if(!LA[cur]) return ;
	int left = 2*cur + 1, right = left + 1;
	update(left, LA[cur], ST, LA);
	update(right, LA[cur], ST, LA);
	LA[cur] = 0;
}

void update(int cur, int s, int e, int p, int v, int *ST, int *LA){
	if(s == e){
		ST[cur] = max(ST[cur], v);
		return;
	}
	push_down(cur, ST, LA);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(p <= m) update(left, s, m, p, v, ST, LA);
	else update(right, m+1, e, p, v, ST, LA);
	ST[cur] = max(ST[left], ST[right]);
}

void update(int cur, int s, int e, int l, int r, int v, int *ST, int *LA){
	if(l > r) return ;
	if(l <= s && e <= r) return update(cur, v, ST, LA);
	push_down(cur, ST, LA);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(r <= m) update(left, s, m, l, r, v, ST, LA);
	else if(m < l) update(right, m+1, e, l, r, v, ST, LA);
	else {
		update(left, s, m, l, m, v, ST, LA);
		update(right, m+1, e, m+1, r, v, ST, LA);
	}
	ST[cur] = max(ST[left], ST[right]);
}

int query(int cur, int s, int e, int l, int r, int *ST, int *LA){
	if(l > r) return 0;
	if(l <= s && e <= r) return ST[cur];
	push_down(cur, ST, LA);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(r <= m) return query(left, s, m, l, r, ST, LA);
	if(m < l) return query(right, m+1, e, l, r, ST, LA);
	return max(query(left, s, m, l, m, ST, LA), query(right, m+1, e, m+1, r, ST, LA));
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n; scanf("%d", &n);
	loop(i, n) {
		int l, r; scanf("%d %d", &l, &r);
		int t; scanf("%d", &t);
		t--;
		V[t].emplace_back(l, r);
		aux.pb(l);
		aux.pb(r);
	}
	sort(all(aux));
	aux.resize(unique(all(aux)) - aux.begin());
	aux.pb(aux.back() + 1);
	aux.pb(aux.back() + 2);
	aux.pb(aux.back() + 3);
	
	
	loop(c, 2) {
		for(auto & [l, r] : V[c]) {
			l = lower_bound(all(aux), l) - aux.begin();
			r = lower_bound(all(aux), r) - aux.begin();
		}
		sort(all(V[c]));
	}
	
	
	
	int idx[] = {sz(V[0]) - 1, sz(V[1]) - 1};
	
	while(max(idx[0], idx[1]) >= 0){
		int c = 0;
		if(idx[0] >= 0 && idx[1] >= 0){
			c = V[1][idx[1]] > V[0][idx[0]];
		} else {
			c = idx[0] < 0;
		}
		auto [l, r] = V[c][idx[c]--];
		
		int other = c^1;
		int q = query(0, 0, sz(aux)-1, r+1, sz(aux)-1, ST[other], LA[other]);
		
//		cerr << c << " " << pi(aux[l], aux[r]) << " " << q << endl;
		
		update(0, 0, sz(aux)-1, l, q + 1, ST[c], LA[c]);
		update(0, 0, sz(aux)-1, r+1, sz(aux)-1, 1, ST[other], LA[other]);
	}
	
	
	
	
	
	cout << max(ST[0][0], ST[1][0]) << endl;
	
	
	
	return 0;
}
