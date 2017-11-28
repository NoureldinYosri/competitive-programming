vi G[MAX];
int depth[MAX],siz[MAX],pref_child[MAX],parent[MAX];
int euler[MAX],dfs_in[MAX],dfs_out[MAX],dfs_time;
int heavy_id[MAX],heavy_head[MAX],heavy_siz[MAX],heavy_name;



void dfs(int u,int p){
	siz[u] = 1;
	pref_child[u] = -1;
	parent[u] = p;
	depth[u] = depth[p] + 1;

	for(int v : G[u]) if(v != p) {
		dfs(v,u);
		siz[u] += siz[v];
		if(pref_child[u] == -1 || siz[pref_child[u]] < siz[v]) pref_child[u] = v;
	}
}


void hld(int u,int p){
	dfs_in[u] = dfs_time;
	euler[dfs_time] = u;
	dfs_time++;

	heavy_id[u] = heavy_name;
	if(heavy_siz[heavy_name] == 0) heavy_head[heavy_name] = u;
	heavy_siz[heavy_name]++;

	if(pref_child[u] != -1) hld(pref_child[u],u);


	for(int v : G[u]) if(v != p && v != pref_child[u]) {
		heavy_name++;
		hld(v,u);
	}
	dfs_out[u] = dfs_time - 1;
}

