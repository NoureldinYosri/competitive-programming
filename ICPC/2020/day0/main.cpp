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

const int MAXITR = 5;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
using dna = vi;
vector<vi> adj;
int V, E;

void read_graph(string fname){
	freopen((fname + ".in").c_str(), "r", stdin);
	
	vp adj_list;
	for(int a, b; scanf("%d %d", &a, &b) == 2;){
		adj_list.emplace_back(a, b);
		V = max(V, max(a, b));
	}
	V++;
	E = adj_list.size();
	cerr << "read V: " << V << ", E: " << E << endl; 
	adj.resize(V);
	for(auto [a, b] : adj_list){
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
}

void canonize(dna & s){
	static map<int, int> M;
	M.clear();
	for(int & x : s){
		if(M.count(x)) x = M[x];
		else {
			int q = M.size();
			x = M[x] = q;
		}
	}
}

double Regularization(const vector<vi> & C, const dna & s){
	int n = C.size();
	double R = 0;
	
	for(const vi & B : C){
		if(sz(B) == 1) {
			R += 1;
		} else {
			int E_in = 0, m = sz(B);
			for(int u : B) for(int v : adj[u]) E_in += s[u] == s[v];
			R += E_in/(0.5*m*(m - 1));
		}
	}
	
	R /= n;
	R -= n/(double)V;
	R /= 2;
//	cerr << "Regularization " << R << endl;
	return R;
}

double Modularity(const vector<vi> & C, const dna & s) {
	double M = 0;
	for(const vi & B : C){
		int E_in = 0;
		int sum_degree = 0;
		for(int v : B){
			sum_degree += sz(adj[v]);
			for(int u : adj[v]) E_in += s[v] == s[u];
		}
		assert(E_in%2 == 0);
		E_in >>= 1;
		M += E_in/(double)E - pow(sum_degree/(2.0 * E), 2.0);
	}
//	cerr << "Modularity " << M << endl;
	return M;
}

void dna_split(dna & s, vector<vi> & C){
	canonize(s);
	C.clear();
	C.resize(*max_element(all(s)) + 1);	
	loop(i, sz(s)) C[s[i]].push_back(i);
}

double fitness(dna & s){
	static vector<vi> C;
	dna_split(s, C);
	return Modularity(C, s) + Regularization(C, s);	
}

dna create_random(int n){
	static vi Q;
	dna s(V, 0);
	Q.resize(V);
	loop(i, V) Q[i] = i;
	loop(i, n) {
		int nt = n - i;
		int di = (rng()%(n - i) + nt)%nt;
		if(di) swap(Q[i], Q[i + di]);
		s[Q[i]] = i;
	}
	for(int i = n; i < V; i++) s[Q[i]] = (rng()%n + n)%n;
	return s;
}



int get_center(vi & C){
	static vi D, R, visID;
	static queue<int> q;
	static int visNum = 0;
	if(D.empty()) {
		D.resize(V);
		R.resize(V);
		visID.resize(V);
	}
	visNum++;
	for(int v : C) D[v] = 0, visID[v] = visNum;
	
	shuffle(all(C), rng);
	int m = 0.01*sz(C); 
	m = max(m, min(50, sz(C)));
	m = min(m, 70);
	
//	cerr << "getting center of a " << sz(C) << " block using " << m << " roots" << endl;
	loop(i, m){
		int root = C[i];
		for(int v : C) R[v] = -1;
		R[root] = 0;
		q.push(root);
		while(!q.empty()){
			int u = q.front(); q.pop();
			for(int v : adj[u]) if(visID[v] == visID[u] && R[v] == -1) {
				R[v] = R[u] + 1;
				q.push(v);
			}
		}
		for(int v : C) D[v] += R[v];
//		cerr << "done with " << i+1 << "/" << m << endl;
	}
		
	int best = INT_MAX, c = C[0];
	for(int v : C) {
		int tmp = D[v];
		if(tmp < best){
			best = tmp;
			c = v;
		}
	}
	return c;
}

vi get_centers(dna & s){
	static vector<vi> C;
	dna_split(s, C);
	vi S;
	cerr << "get centers" << endl;
	int i = 0;
	for(auto & B : C){
		S.push_back(get_center(B));
		i++;
		cerr << "got center of block " << i << "/" << sz(C) << endl;

/*		shuffle(all(B), rng);
		int mx = 0, cent = 0;
		for(int v : B) {
			int deg = 0;
			for(int u : adj[v]) deg += s[u] == s[v];
			if(deg > mx){
				mx = deg;
				cent = v;
			}
		}
		S.push_back(cent);
*/	}
	return S;
}

dna bfs(const vi & S){
	static vi R;
	static queue<int> q;
	R.clear(); R.resize(V, -1);
	loop(i, sz(S)) {
		int s = S[i];
		R[s] = i;
		q.push(s);
	}
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int v : adj[u]) if(R[v] == -1) {
			R[v] = R[u];
			q.push(v);
		}
	}
	return dna(R);
}

void majority(dna & s){
	static vi Q, aux;
	if(Q.empty()) {
		Q.resize(V);
		loop(i, V) Q.push_back(i);
	}
	shuffle(all(Q), rng);
	for(int i : Q) {
		map<int, int> freq;
		int mx = 0;
		for(int j : adj[i]) {
			freq[s[j]]++;
			mx = max(mx, freq[s[j]]);
		}
		aux.clear();
		for(auto [c, q] : freq) if(q == mx) aux.push_back(c);
		int r = aux.size();
		s[i] = (rng()%r + r)%r;
	}
}

dna solve(int n){
	dna s = create_random(n);
	
	for(int itr = 0; itr < MAXITR; itr++){
		vi S = get_centers(s);
		cerr << "reassign" << endl;
		s = bfs(S);
		majority(s);
	}
	return s;
}

void spit(dna & s, string fname){
	FILE *f = fopen((fname + ".out").c_str(), "w");
	vector<vi> C;
	dna_split(s, C);
	for(auto & B : C){
		for(int x : B) fprintf(f, "%d ", x);
		fprintf(f, "\n");
	}
	fclose(f);
}

int main(int argc, char **argv){
	assert(argc > 1);
	read_graph(string(argv[1]));
	
	dna ans = create_random(2);
	double best = fitness(ans);
	spit(ans, string(argv[1]));
	
	int r = min(V, 30);
	int l = min(V, 30);
	int W = r-l+1; 
	
	int MAXI = 20;
	for(int itr = 0; itr < MAXI; itr++){
		int k = (rng()%W + W)%W;
		k = l + k;
		dna s = solve(k);
		double tmp = fitness(s);
		if(tmp > best){
			best = tmp;
			ans = s;
		}
		spit(ans, string(argv[1]));
		cerr << "after " << itr+1 << "/" << MAXI << " " << best << " score should be " << (best + 1)*1e5 << endl;
	}
	
	cerr << best << endl;
	return 0;
}
