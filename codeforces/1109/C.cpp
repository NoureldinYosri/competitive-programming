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
 
const int MAX = 800;
map<int,int> T;
int R[1 << 20];
vector<int> Q[1 << 20];
int m;
int B;
 
vector<pi> blks[MAX];
ll tot[MAX];
ll mn_val[MAX];
 
void fix(int u){
	tot[u] = 0;
	mn_val[u] = LLONG_MAX;
	auto & blk = blks[u];
	int prv_t = -1;
	for(auto p : blk){
		assert(prv_t < p.first);
		prv_t = p.first;
	}
	int t = 0;
	ll s = 0;
	for(auto p : blk){
		tot[u] += (R[p.first] - R[t]) * s;
		t = p.first;
		s = p.second;
		mn_val[u] = min(mn_val[u], tot[u]);
	}
	int et = u*B + B - 1;
	assert(R[et] >= R[t]);
	tot[u] += (R[et] - R[t])*s;
	mn_val[u] = min(mn_val[u], tot[u]);
/*	cout << u << " : {";
	for(auto p : blk) cout << p;
	cout << "} | " << tot[u] << " " << mn_val[u] << " big time is " << u*B + B - 1<< endl;
*/
}
 
 
void update(int u, pi p){
	static vector<pi> aux;
	auto & blk = blks[u];
	while(!blk.empty() && blk.back().first >= p.first) {
		assert(blk.back().first > p.first);
		if(blk.back().first > p.first) aux.push_back(blk.back());
		blk.pop_back();
	}
	blk.push_back(p);
	while(!aux.empty()) {
		blk.push_back(aux.back());
		aux.pop_back();
	}
	
	fix(u);
}
 
void remove(int u, int t){
	static vector<pi> aux;
	auto & blk = blks[u];
	while(!blk.empty() && blk.back().first >= t) {
		aux.push_back(blk.back());
		blk.pop_back();
	}
	assert(!aux.empty());
	assert(aux.back().first == t);
	aux.pop_back();
	while(!aux.empty()) {
		blk.push_back(aux.back());
		aux.pop_back();
	}
	fix(u);
}
 
 
double getT(ll c, ll s){
	assert(c > 0);
	assert(s < 0);
	return c/(0.0 - s);
}
 
bool process_blk(int u, int & t, int r, ll & s, ll & c, double & ans){
	auto & blk = blks[u];
	int E = u*B+B-1;
	assert(r <= E);
	if(blk.empty()) {
		ll step = s * (R[r] - R[t]);
		if(c + step <= 0){
			ans = R[t] + getT(c, s);
			return 1;
		}
		t = r;
		c += step;
		return 0;
	}
		
	int e = min(r, blk[0].first);
	ll step = s * (R[e] - R[t]);
	if(c + step <= 0){
		ans = R[t] + getT(c, s);
		return 1;
	}
	c += step;
	t = e;
	/*
	if(E == r && c + mn_val[u] > 0) {
		t = E;
		c += tot[u];
		s = blk.back().second;
		return 0;
	}
	*/
	for(auto & p : blk){
		if(p.first < t) continue;
		if(p.first > r) break;
		ll step = s * (R[p.first] - R[t]);
		if(c+step <= 0){
			ans = R[t] + getT(c, s);
			return 1;
		}
		t = p.first;
		c += step;
		s = p.second;
	}
	
	step = s * (R[r] - R[t]);
	if(c+step <= 0){
		ans = R[t] + getT(c, s);
		return 1;
	}
	c += step;
	t = r;
	return 0;	
}
 
 
double query(int l, int r,ll c){
	if(c == 0) return l;
	l = T[l], r = T[r];
	int u = l/B, v = r/B;
//	cout << R[l] << " " << R[r] << " " << u << " " << v << endl;
	double ans = -1;
	int t = l;
	ll s = 0;
	for(;u <= v;u++){
		if(process_blk(u, t, min(r, u*B + B - 1), s, c, ans))
			return ans;
	}
	return -1;
}
 
int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&m);
	loop(i,m){
		int type; scanf("%d",&type);
		Q[i].push_back(type);
		if(type == 1){
			int t, s; scanf("%d %d",&t,&s);
			Q[i].push_back(t);
			Q[i].push_back(s);
			T[t];
		}
		else if(type == 2){
			int t; scanf("%d",&t);
			T[t];
			Q[i].push_back(t);
		}
		else if(type == 3){
			int l, r, v;
			scanf("%d %d %d",&l,&r,&v);
			T[l], T[r];
			Q[i].push_back(l);
			Q[i].push_back(r);
			Q[i].push_back(v);
		}
	}
	
	B = sqrt(sz(T));
	
	while(sz(T)%B) {
		int lst_key = T.rbegin()->first; 
		T[lst_key + 1] = 0;
	}
	
	int val = 0;
	for(auto & p : T) {
		p.second = val++;
		R[p.second] = p.first;
	}
	
	
	
	for(int q = 0;q < m;q++){
		int type = Q[q][0];
//		print(Q[q], int);
		if(type == 1){
			int t = Q[q][1];
			int s = Q[q][2];
			t = T[t];
			update(t/B, pi(t, s));
		}
		else if(type == 2){
			int t = Q[q][1];
			t = T[t];
			remove(t/B, t);
		}
		else {
			int l = Q[q][1];
			int r = Q[q][2];
			int v = Q[q][3];
			printf("%.6f\n", query(l,r,v));
		}
	}
	
	
	return 0;
}
