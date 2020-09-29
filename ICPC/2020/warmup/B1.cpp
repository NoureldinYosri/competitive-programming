#include <bits/stdc++.h>
using namespace std;

const int K = 20;
using vi = vector<int>;
vector<list<int>> adj;
int n, m;
vector<int> degree, inMIS, dead;
using pi = pair<int, int>;

void init(){
	degree.resize(n + 1, 0);
	inMIS.resize(n + 1, 0);
	adj.resize(n + 1);
	dead.resize(n+1, 0);
}

void read_lp(string fname) {
	FILE *f = fopen((fname + ".lp").c_str(), "r");
	int n; fscanf(f, "%d", &n);
	for(int i = 1; i <= n; i++) {
		int x; fscanf(f, "%d", &x);
		if(x == 0) dead[x] = 1;
		else if(x == 2) inMIS[x] = 1;
	}

	fclose(f);
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

	read_lp(fname);

	set<pi> S;
	for(int i = 1; i <= n; i++) if(!dead[i] && !inMIS[i]){
		S.emplace(degree[i], i);
	}


	while(!S.empty()){
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
	}
	

	printf("%d\n", accumulate(inMIS.begin(), inMIS.end(), 0));

	for(int i = 1; i <= n; i++) printf("%d%c", inMIS[i], " \n"[i==n]);

	return 0;
}

