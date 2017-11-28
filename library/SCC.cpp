const int MAXV = 100*1000 + 10,MAXE = 100*1000 + 10;
vi E[MAXE],ST;
int fr[MAXE],to[MAXE],weight[MAXE];
int dfs_in[MAXV],dfs_low[MAXV],dfs_time;
bool inStack[MAXV];
int SCC_id[MAXV],SCC_cnt,n;
vi SCC[MAXV],SCC_adj[MAXV];

void tarjanSCC(int u) {
	dfs_in[u] = dfs_low[u] = dfs_time++;
	ST.pb(u);
	inStack[u] = true;
	for(int e : E[u]){
		int v = to[e];
		if (dfs_in[v] == -1) {
			tarjanSCC(v);
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}
		else if (inStack[v]) {
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}
	}
	if (dfs_low[u] == dfs_in[u]) {
		bool done = 0;
		while(!done){
			int v = ST.back();
			SCC_id[v] = SCC_cnt;
			SCC[SCC_id[v]].pb(v);
			ST.pop_back();
			done = v == u;
			inStack[v] = 0;
		}
		SCC_cnt++;
	}
}

void compress(){
	vi aux;
	for(int i = 0;i < SCC_cnt;i++){
		for(int u : SCC[i]){
			for(int e : E[u])
				if(SCC_id[to[e]] != i)
					aux.pb(SCC_id[to[e]]);
		}
		sort(all(aux));
		aux.resize(unique(all(aux)) - aux.begin());
		SCC_adj[i].swap(aux);
	}
}

void clean(){
	fill(dfs_in,dfs_in + n + 1,-1);
	ST.clear();
	loop(i,n+1) E[i].clear();
	dfs_time = 0;
	fill(inStack,inStack + n + 1,0);
	loop(i,SCC_cnt) {
		SCC[i].clear();
		SCC_adj[i].clear();
	}
	SCC_cnt = 0;
}
