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

const int MAXN = 5000 + 10;
pi P[MAXN];
vi perm;
bool used[MAXN];

ll cross(int a, int b, int c){
	ll x1 = P[b].first - P[a].first, y1 = P[b].second - P[a].second;
	ll x2 = P[c].first - P[a].first, y2 = P[c].second - P[a].second;
	return x1*y2 - x2*y1;
}

ll dot(int a, int b, int c){
	ll x1 = P[b].first - P[a].first, y1 = P[b].second - P[a].second;
	ll x2 = P[c].first - P[a].first, y2 = P[c].second - P[a].second;
	return x1*x2 + y1*y2;
}

void pass(const vi & I, vi & U){
	for(int i : I) {
		while(sz(U) > 1 && cross(U[sz(U) - 2], U[sz(U) - 1], i) >= 0)
			U.pop_back();
		U.push_back(i);
	}
//	print(I, int);
//	print(U, int);
}

vi getCH(vi & I){
	vi U, D;
	pass(I, U);
	reverse(all(I));
	pass(I, D);
	U.pop_back();
	D.pop_back();
	for(int x : D) U.push_back(x);
	reverse(all(I));
	return U;
}

void run(int s, const vi & CH){
	int e = (s + 1)%sz(CH);
	int len = sz(CH);
//	print(perm, int);
//	print(CH, int);
	perm.push_back(CH[s]);
	for(int i = 1; i < len; i++){
		if(i & 1) {
			perm.push_back(CH[e]);
			e++;
			if(e >= len) e -= len;
		} else {
			s--;
			if(s < 0) s += len;
			perm.push_back(CH[s]);
		}
	}
}


bool check(int a, int b, int c){
	return dot(b, a, c) > 0;
}

bool check(int a, int b){
	if(perm.empty()) return true;
	if(!check(perm.back(), a, b)) return false;
	if(sz(perm) > 1 && !check(perm[sz(perm) - 2], perm[sz(perm) - 1], a))
		return false;
	return true;
}

bool check2(int s, const vi & CH){
	int len = sz(CH);
	int e = (s + 1)%len;
	int a = CH[s], b = CH[e];
	for(int i = 2; i < len; i++){
		int c = 0;
		if(i & 1) {
			e++;
			if(e >= len) e -= len;
			c = CH[e];
		} else {
			s--;
			if(s < 0) s += len;
			c = CH[s];
		}
		if(!check(a, b, c)) return false;
		a = b;
		b = c;
	}
	return true;
	
}

bool work(const vi & CH){
	loop(i, sz(CH)) {
		if(!check(CH[i], CH[(i + 1)%sz(CH)])) continue;
		if(!check2(i, CH)) continue;
		run(i, CH);
		return true;
	}
	return false;
}

bool insert(vi & CH){
	loop(c1, 2) {
		if(c1) reverse(all(perm));
		loop(c2, 2){
			if(c2) reverse(all(CH));
			if(work(CH)) return true;
			if(c2) reverse(all(CH));			
		}
		if(c1) reverse(all(perm));
	}
	cerr << "failed to merge " << endl;
	print(perm, int);
	print(CH, int);
	return false;
}

bool onLine(vi & I){
	for(int i = 0; i + 2 < sz(I); i++)
		if(!cross(I[i], I[i + 1], I[i + 2]) == 0)
			return false;
	int s = 0, e = sz(I) - 1;
	for(int d = 0; s <= e; d ^= 1){
		if(d) perm.push_back(I[e--]);
		else perm.push_back(I[s++]);
	}
	return true;
}

bool solve(vi I, int d){
	if(sz(I) <= 2){
		vi CH = vi(I);
		if(d) reverse(all(CH));
		for(int x : CH) perm.push_back(x);
		return true;
	} 
	if(onLine(I)) return true;
	
	vi CH = getCH(I), aux;
//	print(I, int);
//	print(CH, int);
	if(d) reverse(all(CH));
//	print(CH, int);
	for(int i : CH) used[i] = true;
	for(int i : I) if(!used[i]) aux.push_back(i);
	if(!solve(aux, d^1)) return false;
	if(!insert(CH)) return false;
	return true;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n; scanf("%d", &n);
	loop(i, n) scanf("%d %d", &P[i].first, &P[i].second);
	vi I(n);
	iota(all(I), 0);
	sort(all(I), [](const int & a, const int & b){
		return P[a] < P[b];
	});
	if(solve(I, 0)) {
//		cerr << "final check" << endl;
		for(int i = 0; i + 2 < n; i++)
			if(!check(perm[i], perm[i + 1], perm[i + 2])){
//				cerr << perm[i] << " " << perm[i + 1] << " " << perm[i + 2] << "\t"
//					<< P[perm[i]] << " " << P[perm[i + 1]] << " " << P[perm[i + 2]] << endl;
				puts("-1");
				return 0;
			}
		for(int x : perm) printf("%d ", x + 1);
		puts("");
	} else {
		puts("-1");
	}
	return 0;
}
