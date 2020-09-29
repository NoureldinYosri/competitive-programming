#include <bits/stdc++.h>
using namespace std;

const int K = 100;
using vi = vector<int>;
vector<vi> adj;
int n, m, cycle_cnt;
vector<int> degree, inMIS, dead, vis, depth;
using pi = pair<int, int>;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void init(){
	degree.resize(n + 1, 0);
	inMIS.resize(n + 1, 0);
	adj.resize(n + 1);
	dead.resize(n+1, 0);
	vis.resize(n+1, 0);
	depth.resize(n+1, 0);
}
void read_lp(string fname) {
	FILE *f = fopen((fname + ".lp").c_str(), "r");
	int n; fscanf(f, "%d", &n);
	for(int i = 1; i <= n; i++) {
		int x; fscanf(f, "%d", &x);
		if(x == 0) dead[x] = 1;
		else if(x == 2) inMIS[x] = 1;
		vis[x] = dead[x] || inMIS[x];
	}

	fclose(f);
}



void solve_greedy(const vi & V) {
	set<pi> S;
	for(int v : V) {
		S.emplace(degree[v], v);
	}


	while(!S.empty()){
		if (rand() & 1) {
			int d = S.begin()->first;
			int k = 0;
			for(auto ptr = S.begin(); ptr != S.end() && ptr->first == d && k < K; ptr++) k++;
			k = rand()%k;
			auto ptr = S.begin();
			for(; k; k--) ptr++;
			int u = ptr->second;
			S.erase(ptr);
			inMIS[u] = 1;
			for(int v : adj[u]) if(!dead[v] && !inMIS[v]) {
				S.erase(pi(degree[v], v));
				dead[v] = 1;
				for(int t : adj[v]) if(!dead[t] && !inMIS[t]) {
					S.erase(pi(degree[t], t));
					degree[t]--;
					S.emplace(degree[t], t);
				}
			}
		} else {
			auto [d, u] = *S.rbegin();
			if(d <= 20) continue;
			S.erase(pi(d, u));
			for(int v : adj[u]) if(!dead[v] && !inMIS[v]) {
				S.erase(pi(degree[v], v));
				degree[v]--;
				S.emplace(degree[v], v);
			}						
		}
	}
}

bool is_bipartite(int u, int p, int d, vi & V) {
	if (vis[u]) {
		cycle_cnt++;
		return (d&1) == (depth[u] & 1);
	}
	vis[u] = 1;
	depth[u] = d;
	V.push_back(u);
	bool ret = 1;
	for(int v : adj[u]) if(v != p) ret &= is_bipartite(v, u, d + 1, V);
	return ret;
}

void solve_bipartite(const vi & V) {
	static vi A[2];
	A[0].clear();
	A[1].clear();
	for(int v : V) A[depth[v] & 1].push_back(v);
	int c = A[1].size() > A[0].size();
	for(int v : A[c]) inMIS[v] = 1;	
}

void solve_tree(const vi & V){
	map<int, int> dp[2], choice[2];
	for(int i = (int)V.size() - 1; i >= 0; i--) {
		int u = V[i];
		for(int c = 0; c < 2; c++) {
			int res = 0;
			for(int d = 0; d < 2; d++) {
				if(d == 1 && c == 0) continue;
				int tmp = 0;
				if(d == 0) {
					for(int v : adj[u]) if(depth[v] > depth[u]) tmp += dp[1][v];
				} else {
					tmp = 1;
					for(int v : adj[u]) if(depth[v] > depth[u]) tmp += dp[0][v];
				}
				if(tmp > res) {
					res = tmp;
					choice[c][u] = d;
				}
			}
		}
	}
	queue<pi> q;
	q.emplace(V[0], 1);
	while(!q.empty()){
		auto [u, c] = q.front(); q.pop();
		inMIS[u] = choice[u][c];
		for(int v : adj[u]) if(depth[v] > depth[u]) {
			q.emplace(v, choice[u][c] ^ 1);
		}
	}
}

void solve(){
	static vi V;
	for(int u = 1; u <= n; u++) if(!vis[u]) {
		V.clear();
		cycle_cnt = 0;
		if(is_bipartite(u, -1, 0, V)) {
			solve_bipartite(V);
		} else if(cycle_cnt == 0) {
			solve_tree(V);
		} else {
			solve_greedy(V);
		}
	}
}

int main(int argc, char **argv) {
	srand((unsigned long long)(new char()));
	assert(argc > 1);
	string fname(argv[1]);
	freopen((fname + ".in").c_str(), "r", stdin);
	freopen((fname + ".out").c_str(), "w", stdout);


	scanf("%d %d", &n, &m);
	init();
	for (int e = 0; e < m; ++e){
		int a, b; scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		degree[a]++;
		adj[b].push_back(a);
		degree[b]++;
	}
	for(int i = 0; i < (int)adj.size(); i++) {
		shuffle(adj[i].begin(), adj[i].end(), rng);
	}
	// cerr << "max degree: " << *max_element(degree.begin(), degree.end()) << endl;
	// cerr << "average degree: " << (2.0*m)/n << endl;

	read_lp(fname);

	solve();

	printf("%d\n", accumulate(inMIS.begin(), inMIS.end(), 0));

	for(int i = 1; i <= n; i++) printf("%d%c", inMIS[i], " \n"[i==n]);

	return 0;
}

