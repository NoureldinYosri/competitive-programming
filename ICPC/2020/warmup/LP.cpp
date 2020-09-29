#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pi = pair<int, int>;
#define all(A) A.begin(), A.end()

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
vector<vi> adj;
vi L, R, vis, state;
int n, m;

void init(){
	L.resize(n, -1);
	R.resize(n, -1);
	vis.resize(n, 0);
	adj.resize(n);
	state.resize(n);
}

void greedy(){
	vi V;
	for(int i = 0; i < n; i++) V.push_back(i);
	shuffle(all(V), rng);

	for(int i : V) if(L[i] == -1) {
		for(int j : adj[i]) {
			if(R[j] == -1) {
				L[i] = j;
				R[j] = i;
				break;
			}
		}
	}
}

bool dfs(int u) {
	if(vis[u]) return 0;
	vis[u] = 1;
	for(int v : adj[u]) if(R[v] == -1 || dfs(R[v])){
		L[u] = v;
		R[v] = u;
		return 1;
	}
	return 0;
}

void kuhn(){
	vi V;
	for(int i = 0; i < n; i++) V.push_back(i);
	shuffle(all(V), rng);

	for(int i : V) if(L[i] == -1) {
		fill(all(vis), 0);
		dfs(i);
	}
}


vi vis2[2];

void floodfill(int u, int side) {
	if(vis2[side][u]) return;
	vis2[side][u] = 1;
	if(side == 0) {
		for(int v : adj[u]) {
			if(v == L[u]) {
				continue;
			} else {
				floodfill(v, 1);
			}
		}

	} else {
		if(R[u] != -1) floodfill(R[u], 0);
	}
}

void get_state(){
	for(int c = 0; c < 2; c++) {
		vis2[c].resize(n, 0);
	}
	for(int i = 0; i < n; i++) if(L[i] == -1) {
		floodfill(i, 0);
	}
	for(int i = 0; i < n; i++) {
		// cerr << i << ": " << vis2[0][i] << " " << vis2[1][i] << endl;
		state[i] = vis2[0][i] + (!vis2[1][i]);
		// state[i] = max(state[i], 1);
	}
}

int main(int argc, char **argv) {
	srand((unsigned long long)(new char()));
	assert(argc > 1);
	string fname(argv[1]);
	freopen((fname + ".in").c_str(), "r", stdin);
	freopen((fname + ".lp").c_str(), "w", stdout);

	scanf("%d %d", &n, &m);
	init();
	for (int e = 0; e < m; ++e){
		int a, b; scanf("%d %d", &a, &b);
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for(int i = 0; i < n; i++) {
		shuffle(all(adj[i]), rng);
	}

	greedy();
	kuhn();

	get_state();

	for(int i = 0; i < n; i++) if(state[i] == 2) {
		for(int j : adj[i]) assert(state[j] != 2);
	}
	for(int i = 0; i < n; i++) if(state[i] == 1) {
		for(int j : adj[i]) if(state[j] == 2) {
			state[i] = 0;
			break;
		}
	}

	printf("%d\n", n);

	for(int i = 0; i < n; i++) {
		printf("%d%c", state[i], " \n"[i==n-1]);
	}
	return 0;
}

