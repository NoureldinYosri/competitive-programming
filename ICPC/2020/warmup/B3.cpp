#include <bits/stdc++.h>
using namespace std;

#define all(A) A.begin(), A.end()
const int K = 20, Q = 20;
int population = 100;
using vi = vector<int>;
vector<list<int>> adj;
int n, m, best;
vector<int> degree, inMIS, dead;
using pi = pair<int, int>;
vector<vi> people;
vi ord;
vector<pi> fitness;

void init(){
	degree.resize(n, 0);
	inMIS.resize(n, 0);
	adj.resize(n);
	dead.resize(n, 0);
}

pi compute_fitness(const vi & I) {
	int mis = accumulate(all(I), 0);
	int bad_edges = 0;
	for(int i = 0; i < n; i++) if(I[i]) {
		for(int j : adj[i]) bad_edges += i < j && I[j];
	}
	return pi(mis - bad_edges, bad_edges);
}

int get_weighted(int n) {
	long long M = (n*(n + 1LL)) >> 1;
	long long w = (rand()*(long long)rand())%M;
	//i*(i + 1)/2 = w
	double a = 1, b = 1, c = -2*w;
	double d = b*b - 4*a*c;
	long long x = floor((-b + sqrt(d))/2 - 0.1);
	x = max(x, 1LL);
	while(x*(x+1) < 2*w) x++;
	return n - x;
}

void marry(const vi &A ,const vi & B, vi & child, pi & f) {
	child.resize(n, 0);
	for(int i = 0; i < n; i++) {
		child[i] = rand()%2 ? A[i] : B[i];
	}
	f = compute_fitness(child);
}


void mutate(int i) {
	for(int & x : people[i]) {
		x = (rand()%1000 <= 3) ? rand()%2 : x;
	}
	fitness[i] = compute_fitness(people[i]);
}

void extract_best(){
	static vector<vi> aux_p;
	static vector<pi> aux_f;

	ord.clear();
	for(int i = 0; i < (int)people.size(); i++) ord.push_back(i);
	sort(all(ord), [](const int & a, const int & b) {
		if(fitness[a].first != fitness[b].first) return fitness[a].first > fitness[b].first; 
		return fitness[a].second < fitness[b].second;
	});
	for(int i = 0; i < (int)people.size(); i++) {
		if(fitness[i].second == 0 && fitness[i].first > best) {
			copy(all(people[i]), inMIS.begin());
			best = fitness[i].first;
		} 
	}

	aux_f.clear();
	aux_p.clear();
	for(int i = 0; i < population; i++) {
		aux_p.emplace_back(people[ord[i]]);
		aux_f.emplace_back(fitness[ord[i]]);
	}

	people.swap(aux_p);
	fitness.swap(aux_f);
}

int main(int argc, char **argv) {
	srand((unsigned long long)(new char()));
	assert(argc > 1);
	string fname(argv[1]);
	freopen((fname + ".in").c_str(), "r", stdin);
	freopen((fname + ".out").c_str(), "w", stdout);


	if(argc > 2) {
		sscanf(argv[2], "%d", &population);
	}

	scanf("%d %d", &n, &m);
	init();
	for (int e = 0; e < m; ++e){
		int a, b; scanf("%d %d", &a, &b);
		a--, b--;
		adj[a].push_back(b);
		degree[a]++;
		adj[b].push_back(a);
		degree[b]++;
	}


	for(int k = 0; k < population; k++) {
		vi I(n+1, 0);
		for(int i = 0; i < n; i++) I[i] = rand() & 1;
		people.emplace_back(I);
		fitness.push_back(compute_fitness(I));
	}

	best = 1;
	inMIS[0] = 1;

	
	extract_best();

	for(int t = 0; t < 100; t++) {
		for(int q = 0; q < Q; q++) {
			int i = get_weighted(population);
			int j = get_weighted(population);
			i = ord[i];
			j = ord[j];
			people.emplace_back();
			fitness.emplace_back(0, 0);
			marry(people[i], people[j], people.back(), fitness.back());
		}

		for(int i = 0; i < (int)people.size(); i++)
			mutate(i);

		extract_best();
	}


	
	printf("%d\n", accumulate(inMIS.begin(), inMIS.end(), 0));
	for(int i = 0; i < n; i++) printf("%d%c", inMIS[i], " \n"[i==n]);

	return 0;
}

