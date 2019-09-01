#ifdef ACTIVE
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

const int MAX = 111;
int S[MAX],E[MAX],B[MAX],n,m;
using plan = vi;

plan genPlan(){
	if(n == 1) return plan();
	vi ord(m);
	loop(i,m) ord[i] = i;
	sort(all(ord),[](const int & a,const int &b) {
		return B[a] < B[b];
	});

	plan ret(n-1,0);
	loop(i,m) {
		if(rand()%5 < 2) continue;
		int s = S[i]-1,e = E[i]-1;
		int v = B[i]/(e-s);
		for(int t = s;t < e;t++)
			ret[t] = v;
	}
	loop(i,sz(ret)) {
		int sgn = (rand()%2)*2 - 1;
		ret[i] += sgn*(rand()%10);
		ret[i] = max(ret[i],0);
		ret[i] = min(ret[i],1000000);
	}
	return ret;
}

vector<plan> getPlans(int num = 1000){
	vector<plan> ret;
	loop(i,num) ret.push_back(genPlan());
	return ret;
}


ll fittness(plan & p,bool debug = 0) {
	static int D[MAX];
	D[0] = 0;
	loop(i,sz(p)) D[i + 1] = D[i] + p[i];
	int ret = 0;
	loop(i,m) {
		int a = S[i] - 1,b = E[i] - 1;
		int d = D[b] - D[a];
		if(d <= B[i]) ret += d;
	}
	return ret;
}

void sortPopulation(vector<plan> & population,int num) {
	static vi fit,ord;
	static vector<plan> aux;
	fit.clear();
	ord.clear();
	loop(i,sz(population)) {
		fit.push_back(fittness(population[i]));
		ord.push_back(i);
	}
	sort(all(ord),[](const int & a,const int & b) {
		return fit[a] > fit[b];
	});
	aux.resize(num);
	loop(i,num) aux[i] = population[ord[i]];
	population.swap(aux);
}

int pick(){
	int N = 1000;
	int w = rand()%N + 1,S = 0;
	loop(i,m) S += B[i];
	int s = 0;
	loop(i,m) {
		s += B[i];
		if(s*N >= w*S) return i;
	}
	return m - 1;
}

void mutate(plan & p) {
	static vi I;
	if(p.empty()) return;
	int Q = rand()%min(m,4);
	for(int q = 0;q < Q;q++) {
		int k = pick();
		int a = S[k] - 1,b = E[k] - 1;
		int target = B[k]/(E[k] - S[k]);
		for(int t = a;t < b;t++) {
			int w = p[t];
			int d = target - w;
			int sgn = (d > 0) - (d < 0);
			int step = rand()%min(10,abs(d) + 1);
			p[t] += sgn * step;
		}
	}
}

plan solve(){
	int num = 50;
	vector<plan> population = getPlans(num);
	static vector<plan> children;
	for(int t = 0;t < 210;t++) {
		sortPopulation(population,num);
		children.clear();
		loop(i,num) {
			if(!i) continue;
			int j = rand()%i;
			loop(q,6) {
				int cut = rand()%max(1,n-1);
				int a = rand()%2 ? i : j,b = i+j-a;
				const plan & A = population[a];
				const plan & B = population[b];
				plan child(sz(A),0);
				loop(k,sz(A)) {
					if(k <= cut) child[k] = A[k];
					else child[k] = B[k];
				}
				mutate(child);
				children.push_back(child);
			}
		}
		for(auto p : children) population.push_back(p);
	}
	sortPopulation(population,num);
	return population[0];
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	srand((unsigned ll)(new char()));
// 	srand(6);
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d %d",&n,&m);
		loop(i,m) {
			scanf("%d %d %d",S + i,E + i,B + i);
			if(S[i] > E[i]) swap(S[i],E[i]);
		}
		plan p = solve();
#ifdef HOME
		cout << fittness(p) << endl;
#endif
		loop(j,sz(p)) printf("%d%c",p[j]," \n"[j==sz(p)-1]);
	}
	return 0;
}
#endif
