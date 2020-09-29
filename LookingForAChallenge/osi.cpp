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

using pl = pair<ll, ll>;
const double eps = 1e-12;
const int MAXN = 100*1000 + 10;
pi P[MAXN];
int n;



ll dist2(pi a, pi b){
	ll dx = a.first - b.first;
	ll dy = a.second - b.second;
	ll d2 = dx*dx + dy*dy;
	return d2;
}

double dist(pi a, pi b){
	return sqrt(dist2(a, b));
}

ll cross(pi o, pi a, pi b){
	a.first -= o.first, a.second -= o.second;
	b.first -= o.first, b.second -= o.second;
	return a.first*(ll)b.second - a.second*(ll)b.first;
}

ll dot(pi o, pi a, pi b){
	a.first -= o.first, a.second -= o.second;
	b.first -= o.first, b.second -= o.second;
	return a.first*(ll)b.first + a.second*(ll)b.second;
}

void canon(pi & v){
	int g = 1;
	if(v.first || v.second) g = __gcd(abs(v.first), abs(v.second));
	v.first /= g;
	v.second /= g;	
}

int get_half(pi a){
	if(a.second > 0) return 0;
	else if(a.second < 0) return 1;
	return a.first < 0;
}

bool cmp(pi a, pi b){
	int h1 = get_half(a);
	int h2 = get_half(b);
	
	if(h1 == h2) return cross(pi(0, 0), a, b) > 0;
	return h1 < h2;	
}



double get_angle(pi a){
	double t = atan2(a.second, a.first);
	if(abs(t) < eps) t = 0;
	if(t < 0) t += 2*M_PI;
	return t;
}


double get_angle(pi o, pi a, pi b){
	a.first -= o.first, a.second -= o.second;
	b.first -= o.first, b.second -= o.second;

	double t1 = get_angle(a), t2 = get_angle(b);
	double dt = t2 - t1;
	if(abs(dt) < eps) dt = 0;
	if(dt < 0) dt += 2*M_PI;

	return dt;
}
	
void remove_collinear(){
	static vp aux;
	rotate(P, min_element(P, P + n), P + n);
	aux.clear();
	loop(i, n) {
		pi p = P[i];
		while(sz(aux) > 1 && cross(aux[sz(aux)-2], aux[sz(aux)-1], p) == 0) aux.pop_back();
		aux.pb(p);
	}
	copy(all(aux), P);
	n = sz(aux);
}

int Q[1 << 20];

void manacher (const vector<double> & S) {
	int N = S.size();
	for (int i = 0,r = -1,c = -1;i < N;i++) {
		int l = 0;
		if (i <= r)
			l = min(Q[2*c - i],r - i);
		while (i-l-1 >= 0 && i+l+1 < N && abs(S[i-l-1] - S[i+l+1]) <= eps)
			l++;
		Q[i] = l;
		if(i + l > r) {
			r = i + l;
			c = i;
		}
	}
}

int solve(){
	static vector<double> V;
	V.clear();
	remove_collinear();
	
	loop(i, n){
		int j = (i + 1)%n;
		int prv = i-1;
		if(prv == -1) prv += n;
		V.pb(get_angle(P[i], P[prv], P[j]));
		V.pb(dist(P[i], P[j]));
	}
	
	loop(i, 4*n) V.pb(V[i]);
	
//	loop(i, 6*n) cerr << V[i] << " ";
//	cerr << endl;
	
	manacher(V);
//	prArr(Q, 6*n, int);

//	cerr << P[0] << endl;
	int ans = 0;
	loop(i, 6*n)
		ans += (Q[i]*2 + 1) >= 4*n+1;
	
	return ans/2;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		loop(i, n) scanf("%d %d", &P[i].first, &P[i].second);
		printf("%d\n", solve());
	}
	return 0;
}
