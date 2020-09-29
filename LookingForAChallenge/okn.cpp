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


const int MAXN = 1 << 20;
pi L, R, L2, R2;
pi P[MAXN];
int n;

bool in_range(int s, int e, int x){
	if(s > e) swap(s, e);
	return s <= x && x <= e;
}


int sgn(ll x){
	return (x > 0) - (x < 0);
}

ll cross(pi o, pi a, pi b){
	a.first -= o.first, a.second -= o.second;
	b.first -= o.first, b.second -= o.second;
	return a.first*(ll)b.second - a.second*(ll)b.first;
}

bool point_on_segment(pi a, pi b, pi p){
	if(cross(a, b, p)) return 0;
	return in_range(a.first, b.first, p.first) && in_range(a.second, b.second, p.second);
}

bool point_in_polygon(pi p){
	int parity = 0;
	pi E(INT_MAX, p.second);
	loop(i, n){
		int j = (i + 1)%n;
		pi a = P[i], b = P[j];
		if(a.second == b.second) continue; // ignore horizontal

		int s1 = sgn(cross(a, b, p));
		int s2 = sgn(cross(a, b, E));
	
		if(s1 == 0 or s2 == 0) continue;
		
		parity ^= s1 != s2;
	}
	return parity;
}

bool point_in_rectangle(pi p){
	return in_range(L.first, R.first, p.first) && in_range(L.second, R.second, p.second);
}


void get_points(pi a, pi b, vp & V){
	cerr << "check " << a << " " << b << endl;
	if(point_in_rectangle(a) && point_in_rectangle(b)){
		V.pb(a);
		V.pb(b);
		cerr << "+ " << V[sz(V)-2] << " " << V[sz(V)-1] << endl;
		return;
	}
	if(!point_in_rectangle(a) && !point_in_rectangle(b)){
		if(a.first == b.first) {
			int y1 = L.second, y2 = R.second;
			if(a.second > b.second) swap(y1, y2);
			V.emplace_back(a.first, y1);
			V.emplace_back(a.first, y2);
			cerr << "+ " << V[sz(V)-2] << " " << V[sz(V)-1] << endl;
		}
		else {
			int x1 = L.first, x2 = R.second;
			if(a.first > b.first) swap(x1, x2);
			V.emplace_back(x1, a.second);
			V.emplace_back(x2, a.second);
			cerr << "+ " << V[sz(V)-2] << " " << V[sz(V)-1] << endl;
		}
		return;
	}
	
	if(a.first == b.first) V.emplace_back(a.first, in_range(a.second, b.second, L.second) ? L.second : R.second);
	else V.emplace_back(in_range(a.first, b.first, L.first) ? L.first : R.first, a.second);
	cerr << "+ " << V[sz(V)-1] << endl;
}

void visualize(const vp & V){
	int mnx = INT_MAX, mny = INT_MAX;
	int mxx = INT_MIN, mxy = INT_MIN;
	for(auto p : V){
		mnx = min(mnx, p.first);
		mny = min(mny, p.second);
		mxx = max(mxx, p.first);
		mxy = max(mxy, p.second);
	}
	int width = mxx - mnx + 1;
	int height = mxy - mny + 1;
	vector<string> G(height, string(width, '*'));
	
	auto get_repr = [mnx, mxy, height](const pi & p){
		int c = p.first - mnx;
		int r = mxy - p.second;
		//r = height - 1 - r;
		return pi(r, c);		
	};

	loop(i, sz(V)){
		pi a = V[i], b = V[(i+1)%sz(V)];
		char c = (a.first == b.first) ? '|' : '-';
		int dx = b.first - a.first;
		int dy = b.second - a.second;
		while(a != b){
			pi p = get_repr(a);
			G[p.first][p.second] = c;
			a.first += dx;
			a.second += dy;
		}
	}

	for(string s : G)
		cerr << s << endl;
	
}

int clip(int x, int s, int e){
	return min(max(x, s), e);
}

void fix(){
	vp aux;
	rotate(P, min_element(P, P + n), P + n);
	if(n > 1 && P[0] == P[n-1]){
		int k = n-1;
		while(k  && P[k-1] == P[0]) k--;
		rotate(P, min_element(P, P + n), P + n);
	}
	loop(i, n){
		while(sz(aux) > 1 && cross(aux[sz(aux)-2], aux.back(), P[i]) == 0) aux.pop_back();
		aux.pb(P[i]);
	}
	copy(all(aux), P);
	n = sz(aux);
	int xl = L.first, xr = R.first;
	int yu = R.second, yd = L.second;
	
	set<int> L, R, U, D;
	loop(i, n){
		pi p = P[i];
		if(p.first == xl) L.insert(p.second);
		if(p.first == xr) R.insert(p.second);
		if(p.second == yd) D.insert(p.first);
		if(p.second == yu) U.insert(p.first);
	}
	
//	loop(i, n) cerr << P[i];
//	cerr << endl;
	
	aux.clear();
	
	vi tmp;
	set<pair<pi, pi>> done;
	int W = 10;
	loop(i, n){
		pi a = P[i], b = P[(i+1)%n];
		pair<pi, pi> t(a, b);
		if(done.count(t)) {
			aux.pb(a);
			continue;
		}
		done.insert(t);
		tmp.clear();
		if(point_on_segment(::L, R2, a) && point_on_segment(::L, R2, b)){
			// down
//			cerr << "down " << a << " " << b << endl;
//			print(D, int);
			int x1 = min(a.first, b.first), x2 = max(a.first, b.first);
			for(auto ptr = D.find(x1); *ptr != x2 && sz(tmp) <= W; ptr++)
				tmp.pb(*ptr);
			tmp.pb(x2);
			if(a.first != tmp[0]) reverse(all(tmp));
			tmp.pop_back();
			for(int x : tmp) aux.emplace_back(x, a.second);			
		}
		else if(point_on_segment(::L, L2, a) && point_on_segment(::L, L2, b)){
			// left
//			cerr << "left " << a << " " << b << endl;
//			print(L, int);
			int y1 = min(a.second, b.second), y2 = max(a.second, b.second);
			for(auto ptr = L.find(y1); *ptr != y2 && sz(tmp) <= W; ptr++)
				tmp.pb(*ptr);
			tmp.pb(y2);
			if(a.second != tmp[0]) reverse(all(tmp));
			tmp.pop_back();
			for(int y : tmp) aux.emplace_back(a.first, y);			
		}
		else if(point_on_segment(L2, ::R, a) && point_on_segment(L2, ::R, b)){
			// up
//			cerr << "up " << a << " " << b << endl;
//			print(U, int);
			int x1 = min(a.first, b.first), x2 = max(a.first, b.first);
			for(auto ptr = U.find(x1); *ptr != x2 && sz(tmp) <= W; ptr++)
				tmp.pb(*ptr);
			tmp.pb(x2);
			if(a.first != tmp[0]) reverse(all(tmp));
			tmp.pop_back();
			for(int x : tmp) aux.emplace_back(x, a.second);			
		}
		else if(point_on_segment(R2, ::R, a) && point_on_segment(R2, ::R, b)){
			// right
//			cerr << "right " << a << " " << b << endl;
//			print(R, int);
			int y1 = min(a.second, b.second), y2 = max(a.second, b.second);
			for(auto ptr = R.find(y1); *ptr != y2 && sz(tmp) <= W; ptr++)
				tmp.pb(*ptr);
			tmp.pb(y2);
			if(a.second != tmp[0]) reverse(all(tmp));
			tmp.pop_back();
			for(int y : tmp) aux.emplace_back(a.first, y);			
		}
		else aux.pb(a); 
	}
	copy(all(aux), P);
	n = sz(aux);	
}


list<int> G[MAXN];
int vis[MAXN];

int dfs(int u, int p, ll area){
	if(vis[u] == 1) return area != 0;
	if(vis[u] == 2) return 0;
	vis[u] = 1;
	int ret = 0;
	for(int v : G[u]) if(v != p) ret += dfs(v, u, area + cross(pi(0, 0), P[u], P[v]));
	vis[u] = 2;
	return ret;
}

int count_regions(){
	vp V;
	int ret = 0;
	loop(i, n){
		pi & p = P[i];
		p.first = clip(p.first, L.first, R.first);
		p.second = clip(p.second, L.second, R.second);
	}
	fix();
//	loop(i, n) cerr << P[i];
//	cerr << endl;
	map<pi, int> M;
	loop(i, n) M[P[i]] = i;
	
	
	loop(i, n){
		int j = (i + 1)%n;
		int a = M[P[i]], b = M[P[j]];
		if(a == b) continue;
		G[a].pb(b);
	}
	
	loop(i, n) {
		pi p = P[i];
		if(M[p] != i) continue;
		if(p.first != L.first && p.first != R.first && p.second != L.second && p.second != R.second) continue;                                                  
		
		ret += dfs(i, -1, 0);
	}
	return ret;
}

int solve(){
	n = unique(P, P + n) - P;
	int count_inter = 0;
	loop(i, n) count_inter += point_in_rectangle(P[i]);
	if(count_inter == n) return 1;	

	return count_regions();
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d %d", &L.first, &L.second, &R.first, &R.second);
	if(L.first > R.first) swap(L.first, R.first);
	if(L.second > R.second) swap(L.second, R.second);
	L.first *= 2, R.first *= 2;
	L.second *= 2, R.second *= 2;
	L2.first = L.first, L2.second = R.second;
	R2.first = R.first, R2.second = L.second;
	//cerr << L << " " << R << endl;
	
	scanf("%d", &n);
	loop(i, n) {
		scanf("%d %d", &P[i].first, &P[i].second);
		P[i].first *= 2;
		P[i].second *= 2;
	}
	cout << solve() << endl;
	
	return 0;
}
