#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<long long, long long> pi;
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

const int MAX = 2*100*1000 + 10;
pi P[MAX], Q[MAX];
int n;
vector<pi> T;

pi operator - (const pi & a, const pi & b){
	return pi(a.first - b.first, a.second - b.second);
}
pi operator + (const pi & a, const pi & b){
	return pi(a.first + b.first, a.second + b.second);
}

ll dist(int a, int b){
	ll dx = P[a].first - P[b].first;
	ll dy = P[a].second - P[b].second;
	return dx*dx + dy*dy;
}

ll cross(pi a, pi b, pi c){
	b = b - a;
	c = c - a;
	return b.first*(ll)c.second - b.second*(ll)c.first;
}

vector<pi> pass(){
	vector<pi> ret;
	for(auto p : T){
		while(sz(ret) > 1 && cross(ret[sz(ret)-2], ret.back(), p) >= 0)
			ret.pop_back();
		ret.pb(p);
	}
	return ret;
}

vector<pi> getCH(){
	sort(all(T));
	auto U = pass();
	reverse(all(T));
	auto D = pass();
	U.pop_back();
	D.pop_back();
	for(auto p : D) U.pb(p);
	reverse(all(U));
	return U;
}

vector<pi> getCanon(vector<pi> V){
	vector<pi> R;
	ll g = 0;
	loop(i, sz(V)){
		int j = (i + 1)%sz(V);
		pi r = V[j] - V[i];
		ll dx = r.first;
		ll dy = r.second;
		g = max(g, abs(dx));
		g = max(g, abs(dy));
		R.emplace_back(dx, dy);
	}
	for(auto & p : R){
		g = __gcd(g, abs(p.first));
		g = __gcd(g, abs(p.second));
	}
	assert(g);
	for(auto & p : R){
		p.first /= g;
		p.second /= g;
	}
	return R;
}

bool are_sim(vector<pi> & CH){
	if(sz(CH) != n) return 0;
	auto A = getCanon(CH);
	auto B = getCanon(vector<pi>{P, P + n});
	/*for(auto p : A) cout << p << " ";
	cout << endl;
	for(auto p : B) cout << p << " ";
	cout << endl;
	*/
	
	int j = 0;
	while(j < sz(B) && B[j] != A[0]) j++;
	if(j == sz(B)) return 0;
	rotate(B.begin(), B.begin() + j, B.end());
	return A == B;
}

void insert(int i, int j){
	T.emplace_back(P[j] - P[i]);	
}

void fix(pi *P){
	int c = 0;
	loop(i, n) {
		if(P[i].second < P[c].second) c = i;
	}
	rotate(P, P + c, P + n);
	loop(k, 5) P[n + k] = P[k];
}

int getR(pi A){
	int x = A.first, y = A.second;
	if(y == 0 && x >= 0) return 0;
	int s = (x > 0) - (x < 0);
	if(y > 0) return 2-s;
	if(y == 0) return 4;
	return 6 + s;
}
bool cmp(pi a, pi b, pi c, pi d){
	pi A = b - a;
	pi B = d - c;	
	int c1 = getR(A);
	int c2 = getR(B);
	if(c1 != c2) return c1 < c2;
	return cross(pi(0, 0), A, B) > 0;	
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) {
		scanf("%lld %lld", &P[i].first, &P[i].second);
		Q[i] = pi(-P[i].first, -P[i].second);
	}

	fix(P);
	fix(Q);

	vector<pi> CH;
	int i = 0, j = 0;
	while(i != n && j != n){
		CH.emplace_back(P[i] + Q[j]);
		if(cmp(P[i], P[i+1], Q[j], Q[j+1])) i++;
		else if(cmp(Q[j], Q[j+1],P[i], P[i+1])) j++;
		else i++, j++;
	}

	puts(are_sim(CH) ? "YES" : "NO");
	
	return 0;
}
